#include <cs50.h>
#include <stdio.h>

int main (void)
{
    int n;
    do
    {
        n = get_int("positive Number: ");
    }

    while (n <= 0);

    // print out that many lines
    for (int i = 0; i < n; i++)
    {

        //print out that many columns
        for (int j = 0; j < n; j++)
        {
            printf("#");

        }
        printf("\n");
    }

}
