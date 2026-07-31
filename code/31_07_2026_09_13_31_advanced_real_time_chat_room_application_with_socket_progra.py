#!/usr/bin/env python3
import socket
import threading
import queue
from datetime import datetime

class ChatRoom:
    def __init__(self):
        self.users = {}
        self.message_queue = queue.Queue()

    def add_user(self, username, connection):
        self.users[username] = connection

    def remove_user(self, username):
        if username in self.users:
            del self.users[username]

    def broadcast_message(self, message):
        for user in list(self.users.keys()):
            try:
                self.users[user].sendall(message.encode())
            except:
                self.remove_user(user)

    def receive_messages(self):
        while True:
            message = self.message_queue.get()
            if message is None:
                break
            self.broadcast_message(message)

    def start(self):
        receive_thread = threading.Thread(target=self.receive_messages)
        receive_thread.start()

class User:
    def __init__(self, username, connection):
        self.username = username
        self.connection = connection

    def send_message(self, message):
        try:
            self.connection.sendall(message.encode())
        except:
            ChatRoom.remove_user(ChatRoom, self.username)

    def receive_messages(self):
        while True:
            message = self.connection.recv(1024)
            if not message:
                break
            print(f"[{datetime.now().strftime('%H:%M:%S')} {self.username}]: {message.decode()}")

class Server:
    def __init__(self, host='127.0.0.1', port=12345):
        self.host = host
        self.port = port
        self.chat_room = ChatRoom()

    def start(self):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.bind((self.host, self.port))
            s.listen()
            print(f"Server started on {self.host}:{self.port}")

            while True:
                connection, address = s.accept()
                user = User(address[0], connection)
                self.chat_room.add_user(user.username, user.connection)

                receive_thread = threading.Thread(target=user.receive_messages)
                receive_thread.start()

    def handle_request(self):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((self.host, self.port))
            user = User('Client', s)
            self.chat_room.add_user(user.username, user.connection)

            send_thread = threading.Thread(target=user.send_message, args=('Hello from client!',))
            send_thread.start()

if __name__ == '__main__':
    server = Server()
    server.start()