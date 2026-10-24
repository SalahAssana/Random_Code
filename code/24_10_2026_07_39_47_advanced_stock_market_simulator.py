import random
from collections import defaultdict

class Stock:
    def __init__(self, name):
        self.name = name
        self.price = 100.0
        self.trades = []

class Agent:
    def __init__(self, id, budget):
        self.id = id
        self.budget = budget
        self.holdings = defaultdict(int)
        self.portfolio_value = 0

    def trade(self, stock, shares, price):
        if stock.name in self.holdings:
            current_shares = self.holdings[stock.name]
            self.holdings[stock.name] += shares
            self.portfolio_value -= current_shares * stock.price + shares * price
        else:
            self.holdings[stock.name] = shares
            self.portfolio_value -= shares * price

    def get_portfolio_value(self):
        return self.portfolio_value

class MarketSimulator:
    def __init__(self, stocks, agents):
        self.stocks = stocks
        self.agents = agents
        self.time_step = 0.1

    def simulate(self, steps):
        for _ in range(steps):
            for agent in self.agents:
                for stock in self.stocks:
                    shares_to_buy = int((agent.budget / stock.price) * (random.random() + 0.5))
                    if random.random() < 0.8:  # 80% chance of buying
                        if shares_to_buy > 0 and agent.portfolio_value >= stock.price * shares_to_buy:
                            self.stocks[stock.name].trades.append((agent.id, "buy", shares_to_buy, stock.price))
                            agent.trade(stock, shares_to_buy, stock.price)
                    else:  # 20% chance of selling
                        if shares_to_buy < 0 and agent.holdings.get(stock.name, 0) > abs(shares_to_buy):
                            self.stocks[stock.name].trades.append((agent.id, "sell", -shares_to_buy, stock.price))
                            agent.trade(stock, -shares_to_buy, stock.price)
            for stock in self.stocks:
                stock.price += (random.random() * 0.1) - 0.05
        return [stock.trades for stock in self.stocks]

if __name__ == '__main__':
    stocks = [Stock("AAPL"), Stock("GOOGL")]
    agents = [Agent(1, 10000), Agent(2, 5000)]
    simulator = MarketSimulator(stocks, agents)
    print(simulator.simulate(100))