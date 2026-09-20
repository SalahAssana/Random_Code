# Temperature Conversion
# BEGINNER project

def celsius_to_fahrenheit(celsius):
    # Convert Celsius to Fahrenheit (1:33.8)
    return (celsius * 9/5) + 32

def fahrenheit_to_celsius(fahrenheit):
    # Convert Fahrenheit to Celsius (0:32 = 0°C, 100:36 = 38°C)
    return (fahrenheit - 32) * 5/9

if __name__ == '__main__':
    print("Temperature Conversion")
    while True:
        print("\nChoose an option:")
        print("1. Celsius to Fahrenheit")
        print("2. Fahrenheit to Celsius")
        print("3. Quit")
        
        choice = input("Enter your choice (1, 2 or 3): ")
        
        if choice == '1':
            celsius = float(input("Enter temperature in Celsius: "))
            fahrenheit = celsius_to_fahrenheit(celsius)
            print(f"{celsius}°C is equal to {fahrenheit}°F")
        elif choice == '2':
            fahrenheit = float(input("Enter temperature in Fahrenheit: "))
            celsius = fahrenheit_to_celsius(fahrenheit)
            print(f"{fahrenheit}°F is equal to {celsius}°C")
        elif choice == '3':
            break
        else:
            print("Invalid option. Please choose 1, 2 or 3.")