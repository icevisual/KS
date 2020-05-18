#include "stdafx.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "stdio.h"
#include "math.h"
#include <stack>
#include <queue>

#include "KSCommand.h"



int show_cmd(KSCommand cmd)
{
	cout << cmd.Cmd << " * " << cmd.CycleTime << endl;
	return 1;
}


int main(int argc, CHAR * argv[])
{


	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	setlocale(LC_ALL, "chs");
     

	//string folder = "F:\\vlc\\ts\\down\\ff";
	//string ext = ".*";
	//vector<string> files;
	//ListFilesWithExt_NDP(folder, files, ext);

	//for (int i = 0; i < files.size(); i++)
	//{
	//	cout << files[i] << endl;
	//}

	KSMain(argc, argv);


	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}

