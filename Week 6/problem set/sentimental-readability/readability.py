# TODO


def main():
    text = userInput()

    grade = ColemanLiau(text)

    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


def userInput():
    text = str(input("Text: "))
    return text


def ColemanLiau(text):
    textLower = text.lower()
    textLength = len(textLower)
    letters = 0
    words = 0
    sentences = 0

    # Get number of letters
    for i in range(0, textLength):
        if textLower[i].isalpha():
            letters += 1

    # Get number of words
    for i in range(0, textLength):
        if textLower[i].isspace() or i == (textLength - 1):
            words += 1

    # Get number of sentences
    for i in range(0, textLength):
        if textLower[i] == "." or textLower[i] == "!" or textLower[i] == "?":
            sentences += 1

    # Get average number of letters per 100 words
    L = letters / words * 100
    # Get average number of sentences per 100 words
    S = sentences / words * 100

    grade = round(0.0588 * L - 0.296 * S - 15.8)

    return grade


main()
