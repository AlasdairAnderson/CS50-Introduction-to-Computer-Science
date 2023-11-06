# TODO
def main():
    height = 0

    # get user input and reject if not within 1 to 8
    while True:
        try:
            height = int(input("Height: "))
            if height <= 8 and height >= 1:
                break
        except ValueError:
            pass

    # print pramid
    printPiramid(height)


def printPiramid(height):
    whitespace = height - 1
    # Loop height amount of times
    for i in range(0, height):
        whitespace = (height - 1) - i
        # Print left priamid
        for j in range(0, height):
            if whitespace > 0:
                print(" ", end="")
                whitespace = whitespace - 1
            else:
                print("#", end="")
        print("  ", end="")
        # print right piramid
        for j in range(0, height):
            if j < i + 1:
                print("#", end="")

        print()


main()
