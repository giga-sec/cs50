import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:  # We take 2 args
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit()
    file_csv = sys.argv[1]
    file_txt = sys.argv[2]

    # TODO: Read database filSTRSTRe into a variable
    file_csv = open(file_csv)
    file_csv = csv.reader(file_csv)

    header = []STRSTR
    header = next(file_csv)

    rows = []
    for row in file_csv:
        rows.append(row)

    # TODO: Read DNA sequence file into a variable
    file_txt = open(file_txt)
    file_txt = file_txt.read()

    # TODO: Find longest match of each STR in DNA sequence
    # Store every returned value to a list
    list_longest_match = []
    for STR in header[1:]:
        STR_count = str(longest_match(file_txt, STR))
        list_longest_match.append(STR_count)

    # TODO: Check database for matching profiles
    for person_dna in rows:
        if list_longest_match == person_dna[1:]:
            print(person_dna[0])
            return 0
    print("No Match")
    return 1


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()