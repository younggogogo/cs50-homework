#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int wordscore(string word);

int point[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main()
{
    string p1 = get_string("Player 1:");
    string p2 = get_string("Player 2:");
    int score1 = wordscore(p1);
    int score2 = wordscore(p2);
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int wordscore(string word)
{
    int score = 0;
    for (int i = 0, j = strlen(word); i < j; i++)
    {
        if (isupper(word[i]))
        {
            score += point[word[i] - 'A'];
        }
        else if (islower(word[i]))
        {
            score += point[word[i] - 'a'];
        }
    }
    return score;
}
