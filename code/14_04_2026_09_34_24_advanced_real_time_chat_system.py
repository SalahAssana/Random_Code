import socket
import threading
from queue import Queue

class ChatSystem:
    def __init__(self):
        self.users = {}
        self.messages = {}
        self.lock = threading.Lock()
        self.server_socket = None

    def start_server(self, host='127.0.0.1', port=8080):
        try:
            self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.server_socket.bind((host, port))
            self.server_socket.listen(5)
            print(f"Server started at {host}:{port}")
            self.accept_connections()
        except Exception as e:
            print(f"Error starting server: {e}")

    def accept_connections(self):
        while True:
            client_socket, address = self.server_socket.accept()
            client_thread = threading.Thread(target=self.handle_client, args=(client_socket,))
            client_thread.start()

    def handle_client(self, client_socket):
        try:
            data = client_socket.recv(1024).decode('utf-8')
            if not data:
                return
            username = data.split(':')[0]
            message = data.split(':')[1]
            self.lock.acquire()
            try:
                if username in self.users:
                    self.users[username].put(message)
                else:
                    self.users[username] = Queue()
                    self.users[username].put(message)
                for user, queue in self.users.items():
                    client_socket.sendall(f"{user}:{queue.get()}. ".encode('utf-8'))
            finally:
                self.lock.release()
        except Exception as e:
            print(f"Error handling client: {e}")
        finally:
            client_socket.close()

    def broadcast_message(self, message):
        for user, queue in self.users.items():
            if user != "Server":
                client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                client_socket.connect(("localhost", 8080))
                client_socket.sendall(message.encode('utf-8'))
                client_socket.close()

    def run(self):
        if __name__ == '__main__':
            chat_system = ChatSystem()
            chat_system.start_server()
            while True:
                user_input = input("Enter a message (or 'exit' to quit): ")
                if user_input.lower() == "exit":
                    break
                chat_system.broadcast_message(f"Server:{user_input}.")

if __name__ == '__main__':
    chat_system = ChatSystem()
    chat_system.run()