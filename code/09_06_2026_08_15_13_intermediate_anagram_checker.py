# Anagram Checker in Python
import re
from collections import Counter

def clean_string(s):
    # Remove special characters and convert to lowercase
    s = re.sub(r'[^a-zA-Z]', '', s).lower()
    return s

def is_anagram(str1, str2, ignore_case=True, ignore_special_chars=True):
    # Clean the strings if required
    if ignore_case:
        str1 = clean_string(str1)
        str2 = clean_string(str2)

    # Count the frequency of characters in each string
    count1 = Counter(str1)
    count2 = Counter(str2)

    # Check if the counts are equal
    return count1 == count2

def main():
    print("Anagram Checker")
    while True:
        str1 = input("Enter first string: ")
        str2 = input("Enter second string: ")
        ignore_case = input("Ignore case? (y/n): ").lower() == 'y'
        ignore_special_chars = input("Ignore special characters? (y/n): ").lower() == 'y'
        
        if is_anagram(str1, str2, ignore_case, ignore_special_chars):
            print(f"{str1} and {str2} are anagrams.")
        else:
            print(f"{str1} and {str2} are not anagrams.")

if __name__ == '__main__':
    main()