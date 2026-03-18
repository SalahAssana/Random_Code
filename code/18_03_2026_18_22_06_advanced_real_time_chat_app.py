import threading
import socket
import select
import queue
import time

class ChatApp:
    def __init__(self):
        self.users = {}
        self.lock = threading.Lock()
        self.server_socket = None

    def start_server(self):
        # Initialize server socket
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.bind(('localhost', 8080))
        self.server_socket.listen(5)

        print("Server started. Waiting for connections...")

        while True:
            # Accept incoming connection
            client_socket, _ = self.server_socket.accept()
            print(f"New connection from {client_socket.getpeername()}")

            # Handle client communication in separate thread
            client_thread = threading.Thread(target=self.handle_client, args=(client_socket,))
            client_thread.start()

    def handle_client(self, client_socket):
        with self.lock:
            user_id = str(time.time())
            self.users[user_id] = client_socket

        while True:
            # Handle incoming message from client
            data = client_socket.recv(1024).decode('utf-8')
            if not data:
                break

            print(f"Received message from {user_id}: {data}")

            # Broadcast message to all connected clients
            for user_socket in self.users.values():
                if user_socket != client_socket:
                    try:
                        user_socket.sendall(data.encode('utf-8'))
                    except ConnectionResetError:
                        with self.lock:
                            del self.users[user_id]
                            print(f"Client {user_id} disconnected.")
                        return

    def run(self):
        threading.Thread(target=self.start_server).start()

if __name__ == '__main__':
    app = ChatApp()
    app.run()