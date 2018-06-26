# Python program to implement client side in a chat
import socket
import select
import sys
import pickle

def main(argv):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    IP_address = '127.0.0.1'
    Port = 9999
    server.connect((IP_address, Port))
    server.send(pickle.dumps(['[LOGIN]', argv[1]]))

    while True:
        try:
            # maintains a list of possible input streams
            sockets_list = [sys.stdin, server]
            read_sockets, write_socket, error_socket = select.select(sockets_list, [], [])
            for socks in read_sockets:
                if socks == server:
                    # Receive a message here
                    message = socks.recv(2048)
                    message = (pickle.loads(message))
                    print('<' + message[0] + '> ' + message[2])
                else:
                    # Send a message here
                    message = sys.stdin.readline()
                    server.send(pickle.dumps([argv[1], argv[2], message]))
                    sys.stdout.flush()
        except:
            server.send(pickle.dumps([argv[1], argv[2], "__EXIT__"]))
            server.close()
            exit(0)

if __name__ == '__main__':
    main(sys.argv)
