#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int pass(int argc, string argv[]);
void handle(string argv);
string ciper(string x);
char a[27];
char b[27];

int main(int argc, string argv[])
{
    // 检验密钥
    if (pass(argc, argv))
    {
        return 1;
    }
    // 处理密钥
    handle(argv[1]);
    // 输入密文
    string x = get_string("plaintext: ");
    printf("ciphertext: %s\n", ciper(x));
    return 0;
}

int pass(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // 检验字符串是否为26个且每个不重样且都为字母
    int j = strlen(argv[1]);
    if (j != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        for (int i = 0; i < j; i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
        }
        for (int i = 0; i < j; i++)
        {
            int n = 0;
            for (int k = 0; k < j; k++)
            {
                if (argv[1][i] == argv[1][k])
                {
                    n++;
                    if (n == 2)
                    {
                        printf("Key must contain 26 characters.\n");
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
void handle(string argv)
{
    strcpy(a, argv);
    strcpy(b, argv);
    for (int i = 0, j = strlen(a); i < j; i++)
    {
        a[i] = toupper(a[i]);
        b[i] = tolower(b[i]);
    }
}

string ciper(string x)
{
    for (int i = 0, j = strlen(x); i < j; i++)
    {
        if (isupper(x[i]))
        {
            x[i] = a[x[i] - 'A'];
        }
        else if (islower(x[i]))
        {
            x[i] = b[x[i] - 'a'];
        }
    }
    return x;
}
