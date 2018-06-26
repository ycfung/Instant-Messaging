import socket
import pickle
import time
import datetime
from _thread import *

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

IP_address = '127.0.0.1'
Port = 9999
server.bind((IP_address, Port))
server.listen(10)
list_of_clients = []

print("Private chat server is running at port " + str(Port))


def savelog(log):
    f = open("PrivateChat.log", 'a')
    f.write((datetime.datetime.now()).strftime("%Y-%m-%d %H:%M:%S ") + log)
    f.close()


def clientthread(conn, addr):
    # Login confirmation
    type, id = (pickle.loads(conn.recv(2048)))
    list_of_clients.append([conn, id])
    print(str(addr[0]) + ':' + str(addr[1]) + '  ID:' + str(id) + " connected")
    savelog(str(addr[0]) + ':' + str(addr[1]) + '  ID:' + str(id) + " connected\n")
    conn.send(pickle.dumps(['Your ID is ' + str(id), '[SERVER INFO]', "Welcome to this chat! (Ctrl + C to EXIT)"]))

    while True:
        try:
            message = (pickle.loads(conn.recv(2048)))
            if message[2]:
                if message[2] != "__EXIT__":
                    # format to send: from, to
                    SendToChat(message[0], message[1], message[2])
                else:
                    print(str("\n<" + addr[0] + addr[1] + "> " + "Left!"))
                    savelog(str("\n<" + addr[0] + addr[1] + "> " + "Left!"))
                    SendToChat(message[0], message[1], "[SERVER INFO] " + "Left!")
                    removeList(conn)
            else:
                time.sleep(0.5)
        except KeyboardInterrupt:
            conn.close()
            server.close()
            exit()
        except:
            time.sleep(0.5)
            continue


def SendToChat(fromID, toID, message):
    for connection, id in list_of_clients:
        if id == fromID or id == toID:
            try:
                print([fromID, toID, message])
                savelog("From: " + fromID + " To: " + toID + ' ' + "Message: " + message)
                connection.send(pickle.dumps([fromID, toID, message]))
            except:
                connection.close()
                removeList(connection)
        else:
            continue


def removeList(connection):
    for con, id in list_of_clients:
        if con == connection:
            del con
            del id
        else:
            continue


while True:
    try:
        conn, addr = server.accept()
        start_new_thread(clientthread, (conn, addr))
        time.sleep(0.2)
    except:
        conn.close()
        server.close()
