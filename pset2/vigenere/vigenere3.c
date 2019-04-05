#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{

    string key = argv[1];

    int keylength = strlen(argv[1]);

    //check if user enters valid input
    if (argc != 2)
    {
        printf("invalid input!\n");
        return -1;
    }

        //check if user only enters alphabetical letters
        for (int i = 0, n = strlen(argv[1]); i < n; i++)

        {
            if (!isalpha(key[i]))
            {
                printf("only alphabetical letters!\n");
                return -1;
            }
        }


        //prompt user for plaintext
        string plaintext = get_string("plaintext: ");

        int plainlength = strlen(plaintext);

        //apply cipher
        for(int j = 0, j < strlen(plaintext); j++)
        {
            //check if uppercase letters
            if(isupper (plaintext[j]))
            {
                printf("%c", (((plaintext[j] - 'A') + (key[i] - 'A')) % 26) + 'A');
            }

            //check if lowercase letters
            else if(islower (plaintext[j])
            {
                printf("%c", (((plaintext[j] - 'a') + (key[i] - 'a')) % 26) + 'a');
            }

            else
            {
                printf("%c", (plaintext[j]));
            }
        }


    printf("\n");
    return 0;


}