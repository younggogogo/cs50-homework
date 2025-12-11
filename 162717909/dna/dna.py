import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("command-line argument not right")
        sys.exit()

    # TODO: Read database file into a variable

    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        rows = []
        name = []
        for row in reader:
            rows.append(row)
        for n in reader.fieldnames:
            name.append(n)
    name = name[1:]
    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as file:
        tmp = file.read()
    # TODO: Find longest match of each STR in DNA sequence
    adict = {}
    for i in name:
        tmpkey = str(longest_match(tmp, i))
        adict[i] = tmpkey
    # TODO: Check database for matching profiles
    sign2 = False
    for i in rows:
        sign1 = True
        for n in adict:
            if i[n] != adict[n]:
                sign1 = False
        if sign1 == True:
            print(i['name'])
            sign2 = True

    if sign2 == False:
        print("No match")
    return


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
