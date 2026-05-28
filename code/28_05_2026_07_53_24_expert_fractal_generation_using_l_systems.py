import turtle
import math

class LSystem:
    def __init__(self, axiom, production_rules):
        self.axiom = axiom
        self.production_rules = production_rules
        self.current_string = axiom

    def generate(self, iterations):
        for _ in range(iterations):
            new_string = ""
            for char in self.current_string:
                if char in self.production_rules:
                    new_string += self.production_rule(char)
                else:
                    new_string += char
            self.current_string = new_string

    def production_rule(self, char):
        return self.production_rules[char]

def draw_fractal(turtle, string, angle, distance):
    turtle.speed(0)
    for char in string:
        if char == 'F':
            turtle.forward(distance)
            turtle.right(angle)
        elif char == '+':
            turtle.right(angle)
        elif char == '-':
            turtle.left(angle)

def main():
    axiom = "FX"
    production_rules = {"X": "F-[[X]+X]+F", "F": "FF"}
    iterations = 10

    l_system = LSystem(axiom, production_rules)
    l_system.generate(iterations)

    window = turtle.Screen()
    window.setup(800, 600)
    window.title("Sierpinski Triangle")

    t = turtle.Turtle()
    draw_fractal(t, l_system.current_string, 25, 5)

    window.mainloop()

if __name__ == '__main__':
    main()