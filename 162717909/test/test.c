#include <stdio.h>
#include <cs50.h>
int main(int argc,string argv[])
{
    if(argc!=5)
    {
        return 1;
    }
    printf("%d\n",argc);
    for(int i=0;i<argc;i++)
    {
        printf("%s\n",argv[i]);
    }
}
