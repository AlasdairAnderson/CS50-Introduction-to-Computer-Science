#Get user input
greeting = str(input("Greeting: "))

# Convert user input into lower case and remove white space
greeting = greeting.lower()
greeting = greeting.lstrip()

reward = 0

# Compair user input agist "hello" and "h"
if greeting[0] == "h":
    reward = reward + 20
    if greeting.startswith("hello"):
        reward = 0
else:
    reward = reward + 100

print(f"${reward}")
