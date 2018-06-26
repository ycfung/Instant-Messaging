import socket
import pickle
import time
from _thread import *

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

IP_address = '127.0.0.1'
Port = 6666
server.bind((IP_address, Port))
server.listen(50)
set_of_clients = set()

print("Login server is running at port " + str(Port))


def clientthread(conn, addr):

    LoginInfo = pickle.loads(conn.recv(2048))
    print(LoginInfo[0] + " " + LoginInfo[1])

    if (LoginInfo[1] == 'Online'):
        set_of_clients.add(LoginInfo[0])
    elif (LoginInfo[1] == 'Offline'):
        set_of_clients.discard(LoginInfo[0])
    conn.close()


def saveData():
    while True:
        f = open("OnlineList.txt", 'w')
        for line in set_of_clients:
            f.write(line)
        f.close()
        time.sleep(5)


start_new_thread(saveData, ())

while True:
    try:
        conn, addr = server.accept()
        start_new_thread(clientthread, (conn, addr))
    except:
        conn.close()
        server.close()
