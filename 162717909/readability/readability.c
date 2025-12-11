#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

float cindex(string a);

int main()
{
    // get the sentence
    string input = get_string("Text: ");
    // know the index
    int grade = round(cindex(input));
    // printf("grade = %d\n", grade);
    //  give the grade
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", (int) grade);
    }

    return 0;
}

// know the index
float cindex(string a)
{
    int wordnumber = 1;
    float letter = 0;
    float sentense = 0;
    for (int i = 0, j = strlen(a); i < j; i++)
    {
        if (isalpha(a[i]))
        {
            letter++;
        }
        else if (a[i] == '?' || a[i] == '!' || a[i] == '.')
        {
            sentense++;
        }
        else if (a[i] == ' ')
        {
            wordnumber++;
        }
    }
    // printf("wordnumber = %d\n", wordnumber);
    // printf("letter = %f\n", letter);
    // printf("sentence = %f\n", sentense);
    // printf("%f\n", 0.0588 * (letter/wordnumber*100) - 0.296 * (sentense/wordnumber*100) -15.8);
    return 0.0588 * (letter / wordnumber * 100) - 0.296 * (sentense / wordnumber * 100) - 15.8;
}
