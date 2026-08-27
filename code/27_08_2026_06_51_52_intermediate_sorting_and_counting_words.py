def count_words(text):
    word_count = {}
    words = text.split()
    for word in words:
        word = word.lower().strip(".,;:")
        if word not in word_count:
            word_count[word] = 1
        else:
            word_count[word] += 1
    return word_count

def sort_words(word_count):
    sorted_word_count = sorted(word_count.items(), key=lambda x: (-x[1], x[0]))
    return sorted_word_count

def print_sorted_word_count(sorted_word_count):
    for word, count in sorted_word_count:
        print(f"{word}: {count}")

if __name__ == '__main__':
    text = "This is a test text. This text is used to test the program."
    word_count = count_words(text)
    sorted_word_count = sort_words(word_count)
    print_sorted_word_count(sorted_word_count)