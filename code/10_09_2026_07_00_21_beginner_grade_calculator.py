# Grade Calculator

def calculate_grade(score):
    # Define grade boundaries for A-F
    if score >= 90:
        return "A"
    elif score >= 80:
        return "B"
    elif score >= 70:
        return "C"
    elif score >= 60:
        return "D"
    else:
        return "F"

def main():
    # Set up the test scores
    scores = [85, 95, 78, 92, 56]

    # Calculate and print grades for each score
    for score in scores:
        grade = calculate_grade(score)
        print(f"Grade for {score} is {grade}")

if __name__ == '__main__':
    main()