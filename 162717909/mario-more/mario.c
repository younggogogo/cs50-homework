#include <stdio.h>
void punch(int length);
int main()
{
    int height;
    do
    {
        printf("Height: ");
        scanf("%d", &height);
    }
    while (height <= 0);
    for (int i = 0; i < height; i++)
    {
        for (int j = height - i; j > 1; j--)
        {
            printf(" ");
        }
        punch(i);
        for (int l = 0; l < 2; l++)
        {
            printf(" ");
        }
        punch(i);
        printf("\n");
    }
    return 0;
}
void punch(int length)
{
    for (int g = 0; g <= length; g++)
    {
        printf("#");
    }
}
