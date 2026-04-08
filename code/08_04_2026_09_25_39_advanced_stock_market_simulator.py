import random
import pandas as pd
from collections import deque
from typing import List, Dict, Tuple

class Stock:
    def __init__(self, symbol: str):
        self.symbol = symbol
        self.historical_data = []

    def add_historical_data(self, date: str, open_price: float, high_price: float, low_price: float, close_price: float):
        self.historical_data.append((date, open_price, high_price, low_price, close_price))

class MarketSimulator:
    def __init__(self):
        self.stocks = {}

    def add_stock(self, symbol: str):
        if symbol not in self.stocks:
            self.stocks[symbol] = Stock(symbol)

    def get_historical_data(self, symbol: str) -> List[Tuple]:
        return self.stocks.get(symbol, None).historical_data

    def simulate_market(self, num_days: int) -> Dict[str, Tuple]:
        if not self.stocks:
            raise ValueError("No stocks added to the simulator")

        simulated_data = {}
        for symbol, stock in self.stools.items():
            data = [(f"2022-01-{i+1}", round(random.uniform(50.0, 100.0), 2), 
                    round(random.uniform(55.0, 105.0), 2), 
                    round(random.uniform(45.0, 95.0), 2), 
                    round(random.uniform(48.0, 102.0), 2)) for _ in range(num_days)]
            simulated_data[symbol] = data
        return simulated_data

    def analyze_market(self) -> Dict[str, Tuple]:
        if not self.stocks:
            raise ValueError("No stocks added to the simulator")

        analyzed_data = {}
        for symbol, stock in self.stools.items():
            data = [(date, open_price, high_price, low_price, close_price) 
                    for (date, open_price, high_price, low_price, close_price) in self.get_historical_data(symbol)]
            moving_averages = [sum(data[i:i+3])/3.0 for i in range(len(data)-2)]
            analyzed_data[symbol] = moving_averages
        return analyzed_data

    def make_investment_decision(self, symbol: str) -> Tuple:
        if symbol not in self.stocks:
            raise ValueError("Stock not found")

        data = self.get_historical_data(symbol)
        moving_average = sum([float(row[4]) for row in data[:20]])/20
        return (symbol, "Buy" if float(data[-1][4]) > moving_average else "Sell")

def main():
    simulator = MarketSimulator()
    simulator.add_stock("AAPL")
    simulator.add_stock("MSFT")

    # Add historical data for AAPL and MSFT
    aapl_data = [("2022-01-01", 50.0, 55.0, 45.0, 48.0), 
                 ("2022-01-02", 51.0, 56.0, 46.0, 49.0), 
                 # ... 
                ]
    msft_data = [("2022-01-01", 100.0, 105.0, 95.0, 102.0), 
                 ("2022-01-02", 101.0, 106.0, 96.0, 103.0), 
                 # ... 
                ]
    simulator.stocks["AAPL"].add_historical_data(*zip(*aapl_data))
    simulator.stocks["MSFT"].add_historical_data(*zip(*msft_data))

    simulated_data = simulator.simulate_market(30)
    analyzed_data = simulator.analyze_market()
    investment_decision = simulator.make_investment_decision("AAPL")

    print(simulated_data)
    print(analyzed_data)
    print(investment_decision)

if __name__ == "__main__":
    main()