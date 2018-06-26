import socket
import pickle
import time
import datetime
from _thread import *

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

IP_address = '127.0.0.1'
Port = 8888
server.bind((IP_address, Port))
server.listen(50)
list_of_clients = []

print("Group chat server is running at port " + str(Port))


def savelog(log):
    f = open("GroupChat.log", 'a')
    f.write((datetime.datetime.now()).strftime("%Y-%m-%d %H:%M:%S ") + log)
    print(log)
    f.close()


def clientthread(conn, addr):
    # Login confirmation
    LoginInfo = pickle.loads(conn.recv(2048))
    list_of_clients.append([conn, LoginInfo[0], LoginInfo[1]])
    savelog(str(addr[0]) + ':' + str(addr[1]) + ' UserID: ' + str(LoginInfo[0]) + ' GroupID: ' + str(
        LoginInfo[1]) + " connected")
    # Send welcome info
    conn.send(pickle.dumps(['Server', LoginInfo[1], 'You are connected to this group chat', 'Message']))

    while True:
        try:
            message = (pickle.loads(conn.recv(2048)))
            if message:
                SendToChat(message[0], message[1], message[2], message[3])
                if message[3] == "[LOGOUT]":
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


def SendToChat(fromID, GroupID, message, type):
    for connection, id, groupID in list_of_clients:
        if groupID == GroupID:
            try:
                savelog("From: " + fromID + " To: " + GroupID + ' ' + "Message: " + message)
                connection.send(pickle.dumps([fromID, GroupID, message, type]))
            except:
                connection.close()
                removeList(connection)
        else:
            continue


def removeList(connection):
    for con, id, groupID in list_of_clients:
        if con == connection:
            del con
            del id
            del groupID
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
