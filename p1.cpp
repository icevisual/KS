#include "stdafx.h"

#include "stdio.h"
#include "math.h"
#include "string.h"
#define MAX_SIZE 100

void print_8(char* t1, int len1)
{
	int line = ceil(len1 / 8.0);

	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int t = 8 * i + j;
			if (t >= len1)
				printf("0");
			else
				printf("%c", t1[t]);
		}

		printf("\n");
	}
}

int mainppp()
{

	char t1[MAX_SIZE] = { 0 };
	char t2[MAX_SIZE] = { 0 };

	scanf_s("%s",t1,MAX_SIZE);
	scanf_s("%s",t2,MAX_SIZE);

	int len1 = strlen(t1);
	int len2 = strlen(t2);
	
	int line = ceil(len1 / 8.0);

	print_8(t1, len1);


	print_8(t2, len2);



	return 0;
}



