"""
Portfolio Tracker - ADVANCED Complexity Project
"""

import math

class Asset:
    def __init__(self, name: str, value: float):
        self.name = name
        self.value = value

class Portfolio:
    def __init__(self):
        self.assets = []

    def add_asset(self, asset: Asset):
        self.assets.append(asset)

    def remove_asset(self, asset_name: str):
        for asset in self.assets:
            if asset.name == asset_name:
                self.assets.remove(asset)
                return

    def get_total_value(self) -> float:
        total = 0
        for asset in self.assets:
            total += asset.value
        return total

    def generate_report(self) -> str:
        report = "Portfolio Report:\n"
        for asset in self.assets:
            report += f"{asset.name}: {asset.value:.2f}\n"
        report += f"Total Value: {self.get_total_value():.2f}"
        return report

class Tracker:
    def __init__(self):
        self.portfolio = Portfolio()

    def add_asset(self, name: str, value: float) -> None:
        asset = Asset(name, value)
        self.portfolio.add_asset(asset)

    def remove_asset(self, asset_name: str) -> None:
        self.portfolio.remove_asset(asset_name)

    def get_portfolio_value(self) -> float:
        return self.portfolio.get_total_value()

    def generate_report(self) -> str:
        return self.portfolio.generate_report()

def main():
    tracker = Tracker()

    # Add assets
    tracker.add_asset("Stock A", 100.0)
    tracker.add_asset("Stock B", 200.0)
    tracker.add_asset("Bond C", 50.0)

    # Remove asset
    tracker.remove_asset("Stock B")

    # Generate report
    print(tracker.generate_report())

if __name__ == '__main__':
    main()