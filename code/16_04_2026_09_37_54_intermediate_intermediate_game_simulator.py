class Game:
    def __init__(self):
        self.players = []
        self.board_size = (10, 10)

    def add_player(self, player):
        self.players.append(player)

    def update_game(self):
        for player in self.players:
            if player.position[0] >= self.board_size[0] or player.position[0] < 0:
                player.move(-player.speed)
            if player.position[1] >= self.board_size[1] or player.position[1] < 0:
                player.move(-player.speed)

    def check_collisions(self):
        for i in range(len(self.players)):
            for j in range(i+1, len(self.players)):
                if self.players[i].position == self.players[j].position:
                    return True
        return False


class Player:
    def __init__(self, name, speed=1):
        self.name = name
        self.speed = speed
        self.position = [0, 0]

    def move(self, direction):
        if direction > 0:
            self.position[0] += direction
        elif direction < 0:
            self.position[0] -= direction


if __name__ == '__main__':
    game = Game()
    player1 = Player("Player1", speed=2)
    player2 = Player("Player2")
    game.add_player(player1)
    game.add_player(player2)

    while True:
        for player in game.players:
            print(f"{player.name} is at {player.position}")
        if game.check_collisions():
            print("Collision detected! Game over.")
            break
        game.update_game()