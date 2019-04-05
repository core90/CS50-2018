import sys

# prompt user for input
while True:
    try:

        n = int(input("Height: "))
    except ValueError:
        print("No Valid input, only values between 0 and 23")
        continue
    else:
        if (n < 0 or n > 23) == False:
            break

# draw half pyramide

# iterate over every row
for r in range(n):

    # print spaces
    print(" " * (n - (r + 1)), end='')

    # print hashes
    print("#" * (r + 2), end='')

    # newline
    print()