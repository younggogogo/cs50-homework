#include <stdio.h>
int main()
{
    int height = 0;
    do
    {
        printf("Height: ");
        scanf("%d", &height);
    }
    while (height <= 0);
    
    for (int i = 0; i < height; i++)
    {
        for (int k = height - i; k > 1; k--)
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}
