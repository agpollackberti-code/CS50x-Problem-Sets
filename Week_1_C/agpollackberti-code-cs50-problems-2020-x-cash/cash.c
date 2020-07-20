#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //get and shape user input from float to int
    float changeOwed;
    do
    {
        changeOwed = get_float("Change owed: ");
    }
    while (changeOwed <= 0 || changeOwed > 99);    
    
    int intOwed = round(changeOwed * 100);

    //initialize counters
    int remainingAmount = intOwed; 
    int coinCounter = 0;

    //now start getting greedy!
    //can I use quarters?
    if (remainingAmount >= 25)
    {
        do
        {
            remainingAmount = (remainingAmount - 25);
            coinCounter++;
        }   
        while (remainingAmount >= 25);
    }
    //can I use dimes?
    if (remainingAmount >= 10)
    {
        do
        {
            remainingAmount = (remainingAmount - 10);
            coinCounter++;
        }
        while (remainingAmount >= 10);
    }
    //can I use nickels?
    if (remainingAmount >= 5)
    {
        do
        {
            remainingAmount = (remainingAmount - 5);
            coinCounter++;
        }
        while (remainingAmount >= 5);
    }
    //can I use pennies?
    if (remainingAmount >= 1)
    {
        do
        {
            remainingAmount = (remainingAmount - 1);
            coinCounter++;
        }
        while (remainingAmount >= 1);
    }

    //once we've exhausted remainingAmount, then return the count
    printf("%i \n", coinCounter);

}
