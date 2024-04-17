

def main():

    choice = []

    #User place order
    while True:
        try:
            choice.append(str.title(input("Input: ")))
        except EOFError:
            print()
            break

    #calcualte total of user choice
    total = calcualte_total(choice)

    print(f"Total: ${total:.2f}")


def calcualte_total(choice):

    menu = {
        "Baja Taco": 4.00,
        "Burrito": 7.50,
        "Bowl": 8.50,
        "Nachos": 11.00,
        "Quesadilla": 8.50,
        "Super Burrito": 8.50,
        "Super Quesadilla": 9.50,
        "Taco": 3.00,
        "Tortilla Salad": 8.00
    }

    total = 0.00

    for i in choice:
        if i in menu:
            try:
                total += menu[i]
            except KeyError:
                pass

    return total


main()
