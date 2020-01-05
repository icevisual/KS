#include "stdafx.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "stdio.h"
#include "math.h"




int main()
{
	clock_t t = clock();
	int * A = new int[16]{ 12,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7 };

	clock_t t1 = clock();
	printf("R = %d\n", (t1 - t));


	clock_t t2 = clock();
	printf("R = %d\n", (t2 - t1));

	
	delete[] A;
	
	
	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}