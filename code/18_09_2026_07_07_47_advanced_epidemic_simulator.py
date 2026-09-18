import random
from collections import deque
from typing import List, Tuple

class Person:
    def __init__(self, name: str, is_infected: bool):
        self.name = name
        self.is_infected = is_infected
        self.neighbors: List['Person'] = []

    def infect(self) -> None:
        if not self.is_infected:
            self.is_infected = True

    def recover(self) -> None:
        if self.is_infected:
            self.is_infected = False

class Epidemic:
    def __init__(self, population_size: int, vaccination_rate: float):
        self.population: List[Person] = [Person(f"Person {i}", random.random() < 0.1) for i in range(population_size)]
        self.vaccination_rate = vaccination_rate
        self.quarantine_rate = 0.5

    def simulate(self, days: int) -> None:
        quarantine_queue: deque[Person] = deque()
        for _ in range(days):
            for person in self.population:
                if person.is_infected and random.random() < self.vaccination_rate:
                    person.recover()
                elif person.is_infected:
                    for neighbor in person.neighbors:
                        if not neighbor.is_infected and random.random() < 0.1:
                            neighbor.infect()
                    person.infect()
                elif person.is_quarantined():
                    quarantine_queue.append(person)
            while quarantine_queue:
                infected_person = quarantine_queue.popleft()
                for neighbor in infected_person.neighbors:
                    if not neighbor.is_infected and random.random() < self.quarantine_rate:
                        neighbor.infect()
                        quarantine_queue.append(neighbor)

    def print_status(self) -> None:
        for person in self.population:
            if person.is_infected:
                print(f"{person.name} is infected")
            else:
                print(f"{person.name} is not infected")

if __name__ == '__main__':
    epidemic = Epidemic(100, 0.2)
    epidemic.simulate(30)
    epidemic.print_status()