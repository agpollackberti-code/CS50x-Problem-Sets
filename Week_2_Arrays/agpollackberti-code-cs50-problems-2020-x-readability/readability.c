#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int evaluation(string input);

int main(void)
{
    //get user input in string format with get_string
    string s = get_string("Text: ");

    //evaluate for the index
    int index = evaluation(s);

    //shape output
    if (index > 16)
    {
        printf("Grade 16+\n");
    }

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    if (index > 1 && index <= 16)
    {
        printf("Grade %i\n", index);
    }

}

int evaluation(string input)
{
    string s = input;
    int Len = strlen(s);

    //ANALYSIS
    float letters = 0;
    float words = 1;
    float sentences = 0;

    for (int i = 0; i < Len; i++)
    {
        if isalpha(s[i])
        {
            letters++;
        }

        if isblank(s[i])
        {
            words++;
        }

        if (s[i] == '!' || s[i] == '.' || s[i] == '?')
        {
            sentences++;
        }

    }

    //feed above variables into the Coleman-Liau index calculation, return X
    //L = average number of letters per 100 words
    float L = ((letters / words) * 100);
    //S = average number of sentences per 100 words
    float S = ((sentences / words) * 100);
    //index = 0.0588 * L - 0.296 * S - 15.8
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    return index;
}