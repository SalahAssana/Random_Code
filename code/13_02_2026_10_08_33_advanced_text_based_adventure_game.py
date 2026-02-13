# text_game.py

class Player:
    def __init__(self):
        self.position = "start"
        self.inventory = ["key", "sword"]

    def move(self, direction):
        if direction == "north" and self.position == "start":
            self.position = "forest"
        elif direction == "south" and self.position == "forest":
            self.position = "start"
        elif direction == "east" and self.position == "forest":
            self.position = "cave"
        elif direction == "west" and self.position == "cave":
            self.position = "forest"
        else:
            print("You can't go that way!")

    def take(self, item):
        if item in ["key", "sword"]:
            self.inventory.append(item)
            print(f"You took the {item}!")
        else:
            print("You don't need that!")

def display_player_info(player):
    print(f"Your position is: {player.position}")
    print(f"Your inventory: {', '.join(player.inventory)}")

class Game:
    def __init__(self):
        self.player = Player()

    def start_game(self):
        while True:
            player_position = self.player.position
            print("You are in the " + player_position)
            command = input("> ").lower()
            if command == "quit":
                break
            elif command.startswith("go"):
                direction = command[3:]
                self.player.move(direction)
                display_player_info(self.player)
            elif command.startswith("take"):
                item = command[5:]
                self.player.take(item)
                display_player_info(self.player)

if __name__ == '__main__':
    game = Game()
    game.start_game()