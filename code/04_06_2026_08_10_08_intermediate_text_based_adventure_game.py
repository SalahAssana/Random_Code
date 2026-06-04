# Text-Based Adventure Game
import os

class Room:
    def __init__(self, description, exits):
        self.description = description
        self.exits = exits

class Player:
    def __init__(self, current_room):
        self.current_room = current_room
        self.inventory = []

    def move(self, direction):
        if direction in self.current_room.exits:
            self.current_room = [room for room in self.rooms if room.name == direction][0]
        else:
            print("You can't go that way!")

    def take(self, item):
        if item in self.current_room.items:
            self.inventory.append(item)
            self.current_room.items.remove(item)
        else:
            print("There is no such item here.")

class Game:
    def __init__(self):
        self.rooms = []
        self.players = []

    def load_data(self):
        with open('game_data.txt', 'r') as f:
            data = f.read().splitlines()
            for line in data:
                if line.startswith('ROOM'):
                    room_name, description, exits = line.split(':')
                    room_description = description[1:]
                    room_exits = [exit.strip() for exit in exits[1:].split(',')]
                    self.rooms.append(Room(room_description, room_exits))
                elif line.startswith('PLAYER'):
                    player_name, current_room = line.split(':')
                    current_room = [room.name for room in self.rooms if room.name == current_room][0]
                    self.players.append(Player(current_room))

    def start_game(self):
        print("Welcome to the adventure game!")
        for player in self.players:
            player.move('north')

if __name__ == '__main__':
    game = Game()
    game.load_data()
    game.start_game()