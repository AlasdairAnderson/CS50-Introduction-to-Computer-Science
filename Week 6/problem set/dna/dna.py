import csv
import sys


def main():
    # TODO: Check for command-line usage
    if commandLine(sys.argv) == False:
        sys.exit("Command Line Error Usage: python dna.py file.csv file.txt")
    # TODO: Read database file into a variable
    subsequence = readCSV(sys.argv[1])
    # TODO: Read DNA sequence file into a variable
    sequence = readtxt(sys.argv[2])
    # TODO: Find longest match of each STR in DNA sequence
    subsequenceLength = {}
    for fieldnames in subsequence.fieldnames[1:]:
        subsequenceLength.update({fieldnames: longest_match(sequence, fieldnames)})
    # TODO: Check database for matching profiles
    return databaseCheck(subsequenceLength, subsequence)


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


def commandLine(argv):
    """Checks to see if correct command line arguments where given"""
    if len(argv) != 3:
        return False

    # Get file type
    CSV = argv[1].split(".")
    TXT = argv[2].split(".")

    if "csv" not in CSV:
        return False
    if "txt" not in TXT:
        return False

    return True


def readCSV(CSVfile):
    inputFile = csv.DictReader(open(CSVfile))
    return inputFile


def readtxt(TXTfile):
    reader = open(TXTfile)

    return reader.read()


def databaseCheck(subsequenceLength, subsequence):
    # TODO: Check database for matching profiles
    strMatch = 0
    # Loop through subsequence rows
    for row in subsequence:
        strMatch = 0
        for element in list(row)[1:]:
            if int(subsequenceLength[element]) == int(row[element]):
                strMatch += 1
        if strMatch == len(list(row)) - 1:
            return print(row["name"])
    # Compair subsequenceLength.key to subsequence.feildname
    return print("No match")


main()
