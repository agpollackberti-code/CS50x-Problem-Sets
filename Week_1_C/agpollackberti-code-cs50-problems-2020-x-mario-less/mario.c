#include <cs50.h>
#include <stdio.h>

void pyramidPrint();

int main(void)
{
    int x;
    do 
    {
        x = get_int("How big a pyramid do you want?");
    }
    while (x <= 0 || x > 8);

    pyramidPrint(x);

}

void pyramidPrint(int n)
{
    //this first loop controls the height
    for (int i = 1; i <= n; i++)
    {
        //this loop controls blank spacing
        for (int j = (n - i); j > 0; j--)
        {
            printf(" ");
        }
        //this loop controls # spacing
        for (int k = i; k > 0; k--)
        {
            printf("#");
        }
        //and start the next line!
        printf("\n");
    }
}

