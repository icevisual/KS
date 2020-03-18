#include "stdafx.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "stdio.h"
#include "math.h"
#include <stack>
#include <queue>

#include "KSTreeNode.h"



int show_cmd(KSCommand cmd)
{
	cout << cmd.Cmd << " * " << cmd.CycleTime << endl;
	return 1;
}


int main(int argc, CHAR * argv[])
{


	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	setlocale(LC_ALL, "chs");
     
	vector<string> sub;
	int count = 0;
	int r = 0;
	string str1 = "MM425,300 MCL MDL {S1000 B S500 JW {E}20 JB S100 GW S400 MM+0,20 S100}10  W-1";

	string str = "  {S1000 B S500 JW {E}20 JB S100 GW S400 MM+0,20 S100}10  ";

	KSCommand cmd;
	KSCommand::ParseStr2KSCmd(str1,cmd);

	KSCommand::LoopCmd(cmd, show_cmd);

	//KSMain(argc, argv);




	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}

