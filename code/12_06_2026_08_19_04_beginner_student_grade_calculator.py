# Student Grade Calculator

def calculate_grade(score, weight):
    # Calculate grade based on score and weight
    return (score / 100) * weight

if __name__ == '__main__':
    scores = [85, 90, 78, 92, 88]
    weights = [0.2, 0.3, 0.1, 0.2, 0.2]

    for i in range(len(scores)):
        grade = calculate_grade(scores[i], weights[i])
        print(f"Student {i+1} score: {scores[i]}, weight: {weights[i]} -> Grade: {grade:.2f}")