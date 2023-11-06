# TODO
# Amex start with: 34 or 37| 15 digits long
# MasterCard start with: 51, 52, 53, 54, 55| 16 digits long
# Visa start with: 4| 13 and 16 digits long
Card = {
    "AMEX": {"cardStart": [34, 37], "cardLength": [15]},
    "MASTERCARD": {"cardStart": [51, 52, 53, 54, 55], "cardLength": [16]},
    "VISA": {"cardStart": [4], "cardLength": [13, 16]},
}


def main():
    # Get user input
    cardNumber = userInput()
    # Is it a valid card
    card_type = cardType(cardNumber)
    if card_type in Card:
        sum_checked = checkSum(cardNumber)
    else:
        return print("INVALID")

    # Check Sum
    if sum_checked == True:
        # Print Card Name
        print(card_type)
    else:
        print("INVALID")


def userInput():
    while True:
        try:
            cardNumber = int(input("Number: "))
            return cardNumber
        except ValueError:
            pass


def cardType(cardNumber):
    # if card number is in card start true
    cardNumb1 = int(str(cardNumber)[:1])
    cardNumb2 = int(str(cardNumber)[:2])

    for i in Card:
        if (
            len(str(cardNumber)) in Card[i]["cardLength"]
            and cardNumb1 in Card[i]["cardStart"]
            or len(str(cardNumber)) in Card[i]["cardLength"]
            and cardNumb2 in Card[i]["cardStart"]
        ):
            # loop through Card and check fist 2 numbers of cardNumber against cardStart
            return i
    return False


def checkSum(cardNumber):
    sum = 0
    otherdigit = int(cardNumber / 10)

    for i in range(0, len(str(cardNumber)), 2):
        # Multiply every other digit by 2
        buffer = otherdigit % 10
        buffer *= 2
        otherdigit = int(otherdigit / 100)
        # Add the products together
        for j in range(0, len(str(buffer))):
            sum = sum + buffer % 10
            buffer = int(buffer / 10)

    # Add the sum to all digits that weren't multiplied by 2
    digit = cardNumber
    for i in range(0, len(str(cardNumber)), 2):
        buffer = digit % 10
        sum = sum + buffer
        digit = int(digit / 100)

    # If total's last diget was 0 then vaild card
    if sum % 10 == 0:
        return True
    else:
        return False


main()
