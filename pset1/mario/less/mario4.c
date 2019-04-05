#include <cs50.h>
#include <stdio.h>

int main (void)
{
    //prompt user for height
    int h;
    do
    {
        h = get_int("Height: ");
    }

    while (h <= 0 || h > 23);


    // print out that many lines
    for (int l = 0; l < h; l++)
    {


                printf("#");


            printf("\n");
    }

}
