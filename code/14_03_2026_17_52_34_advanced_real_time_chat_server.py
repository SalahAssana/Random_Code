import socket
import threading
import pickle

class ChatServer:
    def __init__(self):
        self.host = '127.0.0.1'
        self.port = 9090
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.bind((self.host, self.port))
        self.server.listen(5)

        self.clients = []
        self.lock = threading.Lock()

    def handle_client(self, client):
        while True:
            try:
                request = pickle.loads(client.recv(1024))
                if request == 'disconnect':
                    self.remove_client(client)
                    break
                for c in self.clients:
                    if c != client:
                        c.sendall(pickle.dumps(request))
            except:
                self.remove_client(client)
                break

    def remove_client(self, client):
        with self.lock:
            if client in self.clients:
                self.clients.remove(client)

    def run(self):
        while True:
            client, address = self.server.accept()
            print(f'New connection from {address}')
            with self.lock:
                self.clients.append(client)
            threading.Thread(target=self.handle_client, args=(client,)).start()

if __name__ == '__main__':
    server = ChatServer()
    server.run()