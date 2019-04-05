#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    //checks if user enters valid input
    if (argc != 2)
    {
        printf("Invalid input!\n");
        return 1;
    }

    //convert string "key" to an int
    int k = atoi(argv[1]);

    //check if key is positive number
    if (k < 0)
    {
        printf("Enter positive key!\n");
        return 1;
    }

    else
    {

    // prompt user for plaintext
    string plaintext = get_string("plaintext: ");

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isupper (plaintext[i]))
        {
            printf("%c", (((plaintext[i] + k) - 65) % 26) +65);
        }

        else if (islower(plaintext[i]))
        {
            printf("%c", (((plaintext[i] + k) - 97) % 26) +97);
        }

        else
        {
            printf("%c", (plaintext[i]));
        }
    }

    printf("\n");
    return 0;
}
}