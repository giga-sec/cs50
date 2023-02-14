from sys import exit

sentence_detect = ['.', '!', '?']
word_detect = ' '
full_detection = [' ', ',', '.', '!', '?', ';', "'", '-']
sentence = input("Text: ")


# Counts letters, words and sentences
letter_count = 0
word_count = 1  # To include the last word in countiging
sentence_count = 0
for i in sentence:
    if i not in full_detection:
        # Assumes i is a letter
        letter_count += 1
    elif i in word_detect:
        word_count += 1
    elif i in sentence_detect:
        sentence_count += 1


# Get the average
average_letters = (letter_count / word_count) * 100
average_words = (sentence_count / word_count) * 100

# print(f"{letter_count}, {word_count}, {sentence_count}")
# print(f"{average_letters}, {average_words}")

# Coleman Formula
index = round(0.0588 * average_letters - 0.296 * average_words - 15.8)
if (index <= 1):
    print(f"Before Grade 1")
    exit()
elif (index >= 16):
    index = "16+"
print(f"Grade {index}")