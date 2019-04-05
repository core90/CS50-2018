#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float n;
    int x;
    int y = 0;

    //prompt user for amount of change
    do
    {
        n = get_float("Amount of change: ");
    }

    while (n < 0);

    //convert float(dollars) into int(cents)
    x = round(n * 100);

    while (x >= 25)
    {
        x -= 25;
        y++;
    }

    while (x >= 10)
    {
        x -= 10;
        y++;
    }

    while (x >= 5)
    {
        x -= 5;
        y++;
    }

    while (x >= 1)
    {
        x -= 1;
        y++;
    }

    printf("change owed %i \n", y);

}