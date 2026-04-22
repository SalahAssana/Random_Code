# Temperature Converter
# BEGINNER complexity project

def celsius_to_fahrenheit(celsius):
    """Convert Celsius to Fahrenheit"""
    return (celsius * 9/5) + 32

def fahrenheit_to_celsius(fahrenheit):
    """Convert Fahrenheit to Celsius"""
    return (fahrenheit - 32) * 5/9

if __name__ == '__main__':
    print("Temperature Converter")
    
    while True:
        try:
            temperature = float(input("Enter a temperature in Celsius or Fahrenheit: "))
            if temperature < -273.15:  # absolute zero
                print("Invalid temperature. Please enter a temperature above absolute zero.")
            elif temperature >= -273.15:
                break
        except ValueError:
            print("Invalid input. Please enter a number.")

    choice = input("Do you want to convert Celsius to Fahrenheit (C) or Fahrenheit to Celsius (F)? ")
    
    if choice.upper() == 'C':
        result = celsius_to_fahrenheit(temperature)
        print(f"{temperature}°C is equal to {result:.2f}°F")
    elif choice.upper() == 'F':
        result = fahrenheit_to_celsius(temperature)
        print(f"{temperature}°F is equal to {result:.2f}°C")