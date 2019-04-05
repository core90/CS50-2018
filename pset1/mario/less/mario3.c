#include <cs50.h>
#include <stdio.h>

int main (void)
{
    //prompt user for height
    int n;
    do
    {
        n = get_int("Height: ");
    }

    while (n <= 0 || n > 23);


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
