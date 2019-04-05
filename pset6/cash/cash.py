import sys

# prompt user for amount of change
while True:
    try:

        n = float(input("Amount of change: "))
    except ValueError:
        print("Enter positive number!")
        continue
    else:
        if (n < 0) == False:
            break

# convert float(dollars into int(cents)
x = round(n * 100)

coins = 0

while True:
    if (x >= 25):
        x -= 25
        coins += 1

    elif (x >= 10):
        x -= 10
        coins += 1

    elif (x >= 5):
        x -= 5
        coins += 1

    elif (x >= 1):
        x -= 1
        coins += 1

    else:
        (x == 0)
        break

# print out number of coins
print("change owed", coins)