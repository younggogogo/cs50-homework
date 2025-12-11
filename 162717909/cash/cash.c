#include <stdio.h>
void greedy(int *a, int *b, int g);
int main()
{
    int owed;
    do
    {
        printf("Change owed: ");
        scanf("%d", &owed);
    }
    while (owed <= 0);

    int num = 0;
    int *a = &owed;
    int *b = &num;
    greedy(a, b, 25);
    greedy(a, b, 10);
    greedy(a, b, 5);
    greedy(a, b, 1);
    printf("%d\n", num);
    return 0;
}
void greedy(int *a, int *b, int g)
{
    if (*a >= g)
    {
        while (*a >= g)
        {
            *a -= g;
            (*b)++;
        }
    }
}
