#include "stdafx.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "stdio.h"
#include "math.h"
#include <stack>
#include <queue>

template <typename T> class CStack
{
public:
	//CQueue(void);
	//~CQueue(void);
	void push(const T& node);
	T pop();
private:
	queue<T> queue1;
	queue<T> queue2;
};


template<typename T>
void CStack<T>::push(const T & node)
{
	if(queue1.empty() && queue2.empty())
		queue1.push(node);
	else if(queue1.empty())
	{
		queue2.push(node);
	}
	else
	{
		queue1.push(node);
	}
}

template<typename T>
T CStack<T>::pop()
{
	queue<T> *  queue3 = queue1.empty() ? &queue2 : &queue1;
	queue<T> *  queue4 = queue1.empty() ? &queue1 : &queue2;
	if (queue3->empty())
		return NULL;

	while (queue3->size() > 1)
	{
		T& data = queue3->front();
		queue4->push(data);
		queue3->pop();
	}

	T& head = queue3->front();
	queue3->pop();

	return head;
}


void qsort(int * data, int start, int end)
{
	if (start >= end)
		return;

	
	int i = start;
	int j = end;
	int kIndex = (int)floor((start + end) / 2);
	int key = data[kIndex];
	while (i < j)
	{
		while (i < j && data[j] > key)
		{
			j--;
		}
		if (data[j] < key)
		{
			int temp = data[kIndex];
			data[kIndex] = data[j];
			data[j] = temp;
			kIndex = j;
		}
		

		while (i < j && data[i] <= key)
		{
			i++;
		}
		if (data[i] >= key)
		{
			int temp = data[kIndex];
			data[kIndex] = data[i];
			data[i] = temp;
			kIndex = i;
		}

	}

	qsort(data,start,i -1);
	qsort(data, i + 1, end);
}


void qsort1(int * data, int start, int end)
{
	if (start >= end)
		return;


	int i = start;
	int j = end;
	int key = data[start];
	while (i < j)
	{
		while (i < j && data[j] > key)
		{
			j--;
		}
		data[i] = data[j];

		while (i < j && data[i] <= key)
		{
			i++;
		}
		data[j] = data[i];

	}
	data[i] = key;
	qsort1(data, start, i - 1);
	qsort1(data, i + 1, end);
}



void print_r(int * data, int length)
{
	for (int i = 0; i < length; i++)
	{
		printf("%d ",data[i]);
	}
	printf("\n");
}


void(*VoidNoParamDele)();

typedef void(*pVoidNoParamDele)();

void TestDDDD(int count, pVoidNoParamDele handle)
{
	clock_t t = clock();


	for(int i = 0 ; i < count ; i ++)
		handle();

	clock_t t1 = clock();

	printf("Run %d Tiems ,Time Usage %d ms\n Avg = %.10f \n", count, t1 - t, (t1 - t)*1.0/count);

}

void TestQsort()
{
	int * A = new int[8]{ 4,7,2,1,5,3,8,6 };
	
	qsort(A, 0, 7);
	delete[] A;
}

void TestQsort1()
{
	// int * A = new int[8]{ 4,7,2,1,5,3,8,6 };
	int * A = new int[8]{ 1,2,3,4,5,6,7,8 };
	qsort(A, 0, 7);
	delete[] A;
}


void TestQsort2()
{
	int * A = new int[8]{ 4,7,2,1,5,3,8,6 };
	qsort1(A, 0, 7);
	delete[] A;
}

void TestQsort3()
{
	// int * A = new int[8]{ 4,7,2,1,5,3,8,6 };
	int * A = new int[8]{ 1,2,3,4,5,6,7,8 };
	qsort1(A, 0, 7);
	delete[] A;
}


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	setlocale(LC_ALL, "chs");
     
	int testCount = 1000000;

	TestDDDD(testCount, TestQsort);
	TestDDDD(testCount, TestQsort1);
	TestDDDD(testCount, TestQsort2);
	TestDDDD(testCount, TestQsort3);




	_CrtDumpMemoryLeaks();
	system("pause");
}

int mainfff()
{

	clock_t t = clock();
	int * A = new int[8]{ 1,2,4,7,3,5,6,8 };
	int * B = new int[8]{ 4,7,2,1,5,3,8,6 };
	print_r(A, 8);
	qsort(A,0,7);
	print_r(A,8);
	CStack<int> q;

	q.push(1);
	q.push(2);
	q.push(3);

	for (int i = 0; i < 3; i++)
	{
		printf("%d\n",q.pop());
	}

	delete[] A;
	delete[] B;
	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}
