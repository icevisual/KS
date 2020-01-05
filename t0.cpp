#include "stdafx.h"
#include <stdlib.h>

#include <crtdbg.h>



#include "stdio.h"
#include "math.h"

int* FIND_MAX_CROSSing_SUBARRAY(int * A, int low, int mid, int high)
{
	int left_sum = -99999;
	int sum = 0;
	int max_left_i = -1;
	for (int i = mid; i >= low; i--)
	{
		sum += A[i];
		if (sum > left_sum)
		{
			left_sum = sum;
			max_left_i = i;
		}
	}

	int right_sum = -99999;
	int max_right_i = -1;
	sum = 0;
	for (int i = mid + 1; i <= high; i++)
	{
		sum += A[i];
		if (sum > right_sum)
		{
			right_sum = sum;
			max_right_i = i;
		}
	}

	return new int[3]{ max_left_i ,max_right_i, left_sum + right_sum };
}

int * FIND_MAX_SUBARRAY(int * A, int low, int high)
{
	if (low == high)
	{
		return new int[3]{ low,high,A[low] };
	}
	else
	{
		int mid = (int)floor((low + high) / 2.0);
		int * left_low_high_sum = FIND_MAX_SUBARRAY(A, low, mid);
		int * right_low_high_sum = FIND_MAX_SUBARRAY(A, mid + 1, high);
		int * mid_low_high_sum = FIND_MAX_CROSSing_SUBARRAY(A, low, mid, high);

		if (left_low_high_sum[2] >= right_low_high_sum[2] && left_low_high_sum[2] >= mid_low_high_sum[2])
		{
			delete[] right_low_high_sum;
			delete[] mid_low_high_sum;
			return left_low_high_sum;
		}
		else if (right_low_high_sum[2] >= left_low_high_sum[2] && right_low_high_sum[2] >= mid_low_high_sum[2])
		{
			delete[] left_low_high_sum;
			delete[] mid_low_high_sum;
			return right_low_high_sum;
		}
		else
		{
			delete[] left_low_high_sum;
			delete[] right_low_high_sum;
			return mid_low_high_sum;
		}
	}
}

int * FIND_MAX(int * A, int length)
{
	int sum = 0;
	int max_sum = -99999;
	int low = 0, high = 0;
	for (int i = 0; i <= length; i++)
	{
		sum = 0;
		for (int j = i; j <= length; j++)
		{
			sum += A[j];
			if (sum > max_sum)
			{
				max_sum = sum;
				low = i;
				high = j;
			}
		}
	}
	return new int[3]{ low,high,max_sum };
	// printf("R = (%d, %d, %d) %d\n", low,high,max_sum, (t1 - t));
}
