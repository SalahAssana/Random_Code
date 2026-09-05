# Phonebook Search Algorithm Using Binary Search in Python

phonebook = [
    {"name": "Alice", "phone": 1234567890},
    {"name": "Bob", "phone": 9876543210},
    {"name": "Charlie", "phone": 1112223333},
    {"name": "David", "phone": 4445556666},
    {"name": "Eve", "phone": 7778889999}
]

def binary_search(phonebook, target_name):
    """
    Binary search function to find a name in the phonebook.
    
    Args:
        phonebook (list): A list of dictionaries containing names and phone numbers.
        target_name (str): The name to be searched for.

    Returns:
        int: The phone number if found, -1 otherwise.
    """
    low = 0
    high = len(phonebook) - 1

    while low <= high:
        mid = (low + high) // 2
        if phonebook[mid]["name"] == target_name:
            return phonebook[mid]["phone"]
        elif phonebook[mid]["name"] < target_name:
            low = mid + 1
        else:
            high = mid - 1

    return -1

def main():
    """
    Main function to interact with the user.
    """
    while True:
        print("Phonebook Search Algorithm")
        print("1. Search for a name")
        print("2. Exit")

        choice = input("Enter your choice: ")

        if choice == "1":
            target_name = input("Enter the name to search for: ")
            phone_number = binary_search(phonebook, target_name)
            if phone_number != -1:
                print(f"Phone number found: {phone_number}")
            else:
                print("Name not found in the phonebook.")
        elif choice == "2":
            break
        else:
            print("Invalid choice. Please choose 1 or 2.")

if __name__ == '__main__':
    main()