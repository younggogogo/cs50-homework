#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// char* 是一个地址，*才可以访问，%s可以输出是因为默认其为一个地址
// isdigit 每次只能检查一位

string caesar(string x, int key);

int main(int argc, string argv[])
{
    if (argc != 2 )
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    for (int i = 0,j =strlen(argv[1]); i < j; i++)
    {
        if(!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    if (atoi(argv[1]) < 0)
    {
            printf("Usage: ./caesar key\n");
            return 1;
    }
    int n = atoi(argv[1]);
    string a = get_string("plaintext: ");
    printf("ciphertext: %s\n", caesar(a, n));
    return 0;
}
string caesar(string x, int key)
{
    for (int i = 0, j = strlen(x); i < j; i++)
    {
        if (isupper(x[i]))
        {
            x[i] = 'A' + (x[i] - 'A' + key) % 26;
        }
        else if (islower(x[i]))
        {
            x[i] = 'a' + (x[i] - 'a' + key) % 26;
        }
    }
    return x;
}
