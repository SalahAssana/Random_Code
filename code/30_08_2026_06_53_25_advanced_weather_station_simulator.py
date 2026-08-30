import tkinter as tk
from random import randint, uniform

class WeatherStation:
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("Weather Station Simulator")
        self.sensors = {"Temperature": 0, "Humidity": 0, "Pressure": 0, "Wind Speed": 0}
        self.data_points = []
        self.chart = None

    def simulate(self):
        for sensor in self.sensors:
            self.sensors[sensor] += uniform(-1, 1)
            if self.sensors[sensor] < -50 or self.sensors[sensor] > 50:
                self.sensors[sensor] = randint(-50, 50)

    def update_chart(self):
        if not self.chart:
            self.chart = tk.Canvas(self.root, width=400, height=200)
            self.chart.pack()
        else:
            self.chart.delete("all")
        for sensor, value in self.sensors.items():
            x1 = 10
            y1 = int((value + 50) / 100 * 180)
            x2 = 30
            y2 = int((self.sensors[sensor] + 50) / 100 * 180)
            self.chart.create_line(x1, 200 - y1, x2, 200 - y2)

    def run(self):
        while True:
            self.simulate()
            self.update_chart()
            self.root.update_idletasks()
            self.root.after(5000)  # Update every 5 seconds

    def start(self):
        self.run()
        self.root.mainloop()

if __name__ == "__main__":
    station = WeatherStation()
    station.start()