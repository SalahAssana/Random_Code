import random

class Card:
    def __init__(self, suit, value):
        self.suit = suit
        self.value = value

    def __str__(self):
        return f"{self.value} of {self.suit}"

class Deck:
    def __init__(self):
        self.cards = [Card(s, v) for s in ["Spades", "Hearts", "Diamonds", "Clubs"] for v in ["Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"]]

    def shuffle(self):
        random.shuffle(self.cards)

    def deal(self, n):
        if len(self.cards) < n:
            raise ValueError("Not enough cards in the deck!")
        return [self.cards.pop() for _ in range(n)]

def main():
    deck = Deck()
    print("Initial deck:")
    for card in deck.cards:
        print(card)

    deck.shuffle()
    print("\nShuffled deck:")
    for card in deck.cards:
        print(card)

    hand = deck.deal(5)
    print(f"\nDealt 5 cards: {hand}")

if __name__ == '__main__':
    main()