#include "stdafx.h"
//
#include <sstream>  
#include <iostream>  
#include <map> 
#include "SimulateCMDs.h"

using namespace std;


int SimulateCMDs::Run()
{
	for (int i = 0; i < CMDList.size(); i++)
	{
		char CMDKey = CMDList[i].at(0);
		string params = CMDList[i].substr(1);
		switch (CMDKey)
		{
		case 'K':
			Process_K(params);
			break;
		case 'S':
			Process_S(params);
			break;
		case 'F':
			Process_F(params);
			break;
		case 'E':
			Process_E(params);
			break;
		case 'M':
			Process_M(params);
			break;
		case 'D':
			Process_D(params);
			break;
		default:
			break;
		}
	}
	return 0;
}

int SimulateCMDs::ParseCMDs(string str)
{
	str = str.append(" ");
	const char * chrs = str.c_str();
	INT Length = str.length();
	INT i = 0;
	INT j = 0;
	while (i < Length)
	{
		while (chrs[i] == ' ') i++;
		j = i;
		if (j >= Length)
			break;

		while (chrs[j] != ' ') j++;
		string p = str.substr(i, j - i);
		// p = p.append('\0');
		CMDList.push_back(p);
		i = j;
		i++;
	}

	return 0;
}



int SimulateCMDs::Process_K(string params)
{
	printf("K = %s\n", params.c_str());
	WORD Keys[] = { VK_LMENU,VK_F4 };
	PressKeys(Keys);
	return 0;
}


int SimulateCMDs::Process_S(string params)
{
	printf("S = %s\n", params.c_str());
	INT r = ParseInt(params);

	if (r > 0)
		Sleep(r * 1000);
	return 0;
}


int SimulateCMDs::Process_F(string params)
{
	printf("F = %s\n", params.c_str());
	INT Fn = ParseInt(params);
	WORD FnKeys[] = {
				0,VK_F1,VK_F2,VK_F3,VK_F4,VK_F5 ,
				VK_F6,VK_F7,VK_F8,VK_F9,VK_F10 ,
				VK_F11,VK_F12,VK_F13,VK_F14,VK_F15
	};
	PressKey(FnKeys[Fn]);
	return 0;
}


int SimulateCMDs::Process_E(string params)
{
	printf("E = %s\n", params.c_str());
	PressKey(VK_RETURN);
	return 0;
}


int SimulateCMDs::Process_M(string params)
{
	printf("M = %s\n", params.c_str());



	return 0;
}


int SimulateCMDs::Process_D(string params)
{
	printf("D = %s\n", params.c_str());
	PressKey(VK_DELETE);
	return 0;
}

int SimulateCMDs::PressKey(WORD KeyCode)
{
	WORD Keys[] = { KeyCode };
	SimulateKeyArrayInput(Keys, sizeof(Keys) / sizeof(WORD));
	return 0;
}
int SimulateCMDs::PressKeys(WORD KeyCode[])
{
	SimulateKeyArrayInput(KeyCode, sizeof(KeyCode) / sizeof(WORD));
	return 0;
}
