#include <cs50.h>
#include <stdio.h>
int main()
{
    long cardnum = 0;
    do
    {
		cardnum = get_long("Number: ");
	}
	while (cardnum <= 0);
	// printf("%ld\n",cardnum);
	int sum = 0;
	int flag = 0;
	int num = 0;
	while (cardnum > 0)
	{
		if (cardnum < 100 && cardnum > 10)
		{
			flag = cardnum % 10;
		}
		if (cardnum < 10)
		{
			flag = flag + cardnum % 10 * 10;
		}
		sum = sum + cardnum % 10;
		cardnum = cardnum / 10;
		num++;
		// printf("cardnum=%ld,flag=%d\n",cardnum,flag);
		if (cardnum > 0)
		{
				if (cardnum < 100 && cardnum > 10)
			{
				flag = cardnum % 10;
			}
			if (cardnum < 10)
			{
				flag = flag + cardnum % 10 * 10;
			}
			int split = 0;
			split = cardnum % 10;
			split = split * 2;
			while (split > 0)
			{
				sum = sum + split % 10;
				split = split / 10;
			}
			cardnum = cardnum / 10;
			num++;
			// printf("cardnum=%ld,flag=%d\n",cardnum,flag);
		}
	}
	if (sum % 10 == 0 && (13 <= num && num <= 16))
	{
		if ((flag == 34 || flag == 37) && num == 15)
		{
			printf("AMEX\n");
		}
		else if (40 <= flag && flag < 50 && (num == 13 || num == 16))
		{
			printf("VISA\n");
		}
		else if (50 <= flag && flag < 56 && num == 16)
		{
			printf("MASTERCARD\n");
		}
		else
		{
			printf("INVALID\n");
		}
	}
	else
	{
		printf("INVALID\n");
	}
	//printf("sum = %d, num = %d, flag=%d", sum, num, flag);
	return 0;
 }
