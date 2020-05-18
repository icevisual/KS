#include "stdafx.h"

#include "stdio.h"


void sort(int* data, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (data[j] > data[j + 1])
			{
				int tmp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = tmp;
			}
		}
	}
}

void qsort(int* data, int start,int end)
{
	int key = data[start];
	if (start >= end)
		return;
	int l = start, r = end;

	while (l < r)
	{
		while (l < r && data[r] >= key) r--;
		data[l] = data[r];
		while (l < r && data[l] <= key) l ++;
		data[r] = data[l];
	}
	data[l] = key;
	qsort(data, start, l -1);
	qsort(data, l + 1, end);
}


int mainp0()
{
	int n = 0;
	int data[1000] = {0};
	int flags[1000] = { 0 };

	while (~scanf_s("%d", &n))
	{
		memset(flags,0,sizeof(int) * 1000);
		int i = 0;
		int c = 0;
		while (n --)
		{
			scanf_s("%d", &c);

			if (flags[c] == 0)
			{
				data[i++] = c;
				flags[c] = 1;
			}
		}

		c = i;
		qsort(data,0,c-1);
		for ( i = 0; i < c; i++)
		{
			printf("%d\n",data[i]);
		}
	}

	return 0;
}



