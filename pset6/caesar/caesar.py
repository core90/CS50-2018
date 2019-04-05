import sys


def main():

    # check if user enters valid key, convert str into an int and chek if it is a positive number
    while True:
        key = int(sys.argv[1])
        if key < 0:
            print("invalid input!")
            sys.exit(1)
        else:
            break

    # prompt user for plaintext
    Plaintext = str(input("plaintext: "))
    print("ciphertext: ", end='')

    # check every letter in plaintext and turn them into ciphercode
    for c in Plaintext:

        # uppercase letters
        if c.isupper():
            x = (((ord(c) - 65 + key) % 26) + 65)
            z = chr(x)
            print(z, end='')

        # lowercase letters
        elif c.islower():
            x = (((ord(c) - 97 + key) % 26) + 97)
            z = chr(x)
            print(z, end='')

        # non-alphatecial
        else:
            print(c, end='')

    print()


if __name__ == "__main__":
    main()