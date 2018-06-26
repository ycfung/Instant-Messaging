import socket
import select
import sys
import pickle


# The package format is [YourID, argv[2], MessageToSend, Type],

def main(argv):
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    IP_address = '127.0.0.1'
    Port = 8888
    try:
        server.connect((IP_address, Port))
    except:
        print("Cannot connect to server")
    server.send(pickle.dumps([argv[1], argv[2], str(argv[1] + ' is in!') + '[LOGIN]']))

    while True:
        try:
            # maintains a list of possible input streams
            sockets_list = [sys.stdin, server]
            read_sockets, write_socket, error_socket = select.select(sockets_list, [], [])
            for socks in read_sockets:
                if socks == server:

                    message = socks.recv(2048)
                    message = (pickle.loads(message))
                    print('<' + message[0] + '> ' + message[2])
                else:
                    # Send a message here
                    message = sys.stdin.readline()
                    server.send(pickle.dumps([argv[1], argv[2], message, 'message']))
                    sys.stdout.flush()
        except:
            server.send(pickle.dumps([argv[1], argv[2], str(argv[1] + ' is Left'), "[LOGOUT]"]))
            server.close()
            exit(0)

if __name__ == '__main__':
    main(sys.argv)
