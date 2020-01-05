#include "stdafx.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "stdio.h"
#include "math.h"
#include <stack>

template <typename T> class CQueue
{
public:
	//CQueue(void);
	//~CQueue(void);
	void appendTail(const T& node);
	T deleteHead();
private:
	stack<T> stack1;
	stack<T> stack2;
};


template<typename T>
void CQueue<T>::appendTail(const T & node)
{
	stack1.push(node);
}

template<typename T>
T CQueue<T>::deleteHead()
{
	if (stack2.size() <= 0)
	{
		while (stack1.size() > 0)
		{
			T& data = stack1.top();
			stack1.pop();
			stack2.push(data);
		}
	}

	if (stack2.size() <= 0)
		throw std::exception("queue is empty");

	T& head = stack2.top();
	stack2.pop();

	return head;
}



static int test()
{
	clock_t t = clock();
	int * A = new int[8]{ 1,2,4,7,3,5,6,8 };
	int * B = new int[8]{ 4,7,2,1,5,3,8,6 };

	CQueue<int> q;

	q.appendTail(1);
	q.appendTail(2);
	q.appendTail(3);

	for (int i = 0; i < 3; i++)
	{
		printf("%d\n", q.deleteHead());
	}


	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}
