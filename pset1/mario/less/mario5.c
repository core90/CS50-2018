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

    int x = n-2;
    int y = 2;

    do
    {
        printf(x*" ", y*"#");
        printf("\n");
        x = x - 1;
        y = y + 1;

    }
    while (y <= n);

}
