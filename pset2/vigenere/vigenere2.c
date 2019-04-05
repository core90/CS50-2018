#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc !=2)
    {
        //check if user enters valid input
        printf("invalid output!\n");
        return 1;
    }

    string key = argv[1];

    //check key if all letters alpha
    for(int i = 0, j = strlen(key); i < j; i++)
    {
        if(!isalpha(key[i]))
        {
            printf("only alphabetical letters!\n");
            return 1;
        }
    }

    string plaintext = get_string("plaintext: ");

    for (int i = 0, k = 0, j = strlen(plaintext); i < j; i++)
    {
        if (isalpha(plaintext[i]))  //check alpha letters
        {
            int keyindex = k++ % strlen(key);

            if (isupper(plaintext[i]))  //check uppercase letters
            {
                if(isupper(key[keyindex]))
                {
                    int cipher = ((plaintext[i] - 'A' + key[keyindex] - 'A') % 26 + 'A');
                    printf("%c", cipher);
                }

                else
                {
                    int cipher = ((plaintext[i] - 'A' + key[keyindex] - 'a') % 26 + 'A');
                    printf("%c", cipher);
                }
            }
            if (isupper(key[keyindex]))
            {
                int cipher = ((plaintext[i] - 'a' + key[keyindex] - 'A') % 26 + 'a');
                printf("%c", cipher);
            }

            else
            {
                int cipher = ((plaintext[i]) - 'a' + key[keyindex] - 'a') % 26 + 'a';
                printf("%c", cipher);
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }

    printf("\n");
}