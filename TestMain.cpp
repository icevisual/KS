#include "stdafx.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "stdio.h"
#include "math.h"
#include <stack>
#include <queue>

#include "KSTreeNode.h"


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	setlocale(LC_ALL, "chs");
     
	KSTreeNode root;

	KSCommand cmd;
	cmd.Cmd = "G";
	cmd.CycleTime = 10;
	root.AddSub(&cmd);




	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}

