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
	if (queue1.empty() && queue2.empty())
		queue1.push(node);
	else if (queue1.empty())
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


 
static int test()
{
	clock_t t = clock();
	int * A = new int[8]{ 1,2,4,7,3,5,6,8 };
	int * B = new int[8]{ 4,7,2,1,5,3,8,6 };

	CStack<int> q;

	q.push(1);
	q.push(2);
	q.push(3);

	for (int i = 0; i < 3; i++)
	{
		printf("%d\n", q.pop());
	}


	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}
