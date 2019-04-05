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

    //draw half pyramide

    //rows
    for(int r = 0; r < n; r++)
    {
        //print spaces
        for(int s = 1+r; s < n; s++)
        printf(" ");

        //print hashes
    {   for(int h = n-2-r; h < n; h++)
        printf("#");

    {   printf("\n");

    }
    }
    }
}