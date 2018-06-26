import socket
import select
import sys
import pickle


def main(argv):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    IP_address = '127.0.0.1'
    Port = 6666
    try:
        server.connect((IP_address, Port))
    except:
        print("Cannot connect to server")

    server.send(pickle.dumps([argv[1], argv[2]]))
    print("You are " + argv[2] + " !")
    server.close()


if __name__ == '__main__':
    main(sys.argv)
