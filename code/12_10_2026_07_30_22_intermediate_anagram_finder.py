def find_anagrams(input_string):
    """
    This function finds all possible anagrams in the input string.

    Args:
        input_string (str): The input string for which to find anagrams.

    Returns:
        list: A list of all possible anagrams.
    """
    # Convert the input string to lowercase and sort it
    sorted_input = sorted(input_string.lower())

    # Initialize a set to store unique anagrams
    anagrams = set()

    def generate_anagrams(sorted_string, current_anagram):
        """
        This recursive function generates all possible anagrams.

        Args:
            sorted_string (list): The remaining characters in the sorted input string.
            current_anagram (str): The current anagram being generated.

        Returns:
            None
        """
        if len(sorted_string) == 0:
            # If there are no more characters left, add the anagram to the set
            anagrams.add(current_anigram)
        else:
            for i in range(len(sorted_string)):
                # Recursively generate anagrams with the current character
                new_sorted_string = sorted_string[:i] + sorted_string[i+1:]
                generate_anagrams(new_sorted_string, current_anagram + sorted_string[i])

    generate_anagrams(sorted_input, "")

    return list(anagrams)


if __name__ == '__main__':
    input_string = "listen"
    print("Anagrams of '{}' are: {}".format(input_string, find_anagrams(input_string)))