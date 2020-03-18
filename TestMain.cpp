#include "stdafx.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "stdio.h"
#include "math.h"
#include <stack>
#include <queue>

#include "KSTreeNode.h"


int GetSub(string str,string &sub,int &count)
{
	INT Length = str.length();
	INT i = 0;
	INT j = 0;
	INT p = 0;
	bool hasSub = false;
	int s = 0;
	while (i < Length)
	{
		if (str.at(i) == '{')
		{
			if(j ==0)
			j = i;
			p++;
		}
		if (str.at(i) == '}')
		{
			p--;
			if (p == 0)
			{
				hasSub = true;
				sub = str.substr(j + 1, i - j - 1);

				i++;
				
				while (i < Length && str.at(i) >= '0' && str.at(i) <= '9')
				{
					s = s * 10 + str.at(i) - '0';
					i++;
				}

				break;
			}
		}

		i++;
	}

	if (p != 0)
		return -1;

	count = s;
	return hasSub ? 1:0;
}




int GetSubSeg(string str, vector<string> &sub, int &count)
{
	INT Length = str.length();
	INT i = 0;
	INT j = -1;
	INT p = 0;
	bool hasSub = false;
	int s = 0;
	string str1;
	while (i < Length)
	{
		if (str.at(i) == '{')
		{
			if (j == -1)
				j = i;
			p++;
		}
		if (str.at(i) == '}')
		{
			p--;
			if (p == 0)
			{
				hasSub = true;

				if (j > 0) {
					sub.push_back(str.substr(0, j));
				}
				else {
					sub.push_back("");
				}

				sub.push_back(str.substr(j + 1, i - j - 1));
		
				i++;

				while (i < Length && str.at(i) >= '0' && str.at(i) <= '9')
				{
					s = s * 10 + str.at(i) - '0';
					i++;
				}
				while (i < Length && str.at(i ++ )== ' ');
				if (i < Length)
				{
					sub.push_back(str.substr(i - 1, Length - i + 1));
				}
				else
				{
					sub.push_back("");
				}
				break;
			}
		}
		i++;
	}
	if (p != 0)
		return -1;
	count = s;
	return hasSub ? 1 : 0;
}
int ParseCMDs1(string str)
{
	string str = "  {S1000 B S500 JW {E}20 JB S100 GW S400 MM+0,20 S100}10  ";
	vector<string> sub;
	int count = 0;
	int r = 0;
	r = GetSubSeg(str, sub, count);

	if (r == 0)
	{
		// no {
	}
	else
	{

	}


	for (int i = 0; i < sub.size(); i++)
	{
		cout << sub[i] << endl;
	}
	cout << count << endl;
}

int ParseCMDs(string str)
{
	str = str.append(" ");
	const char * chrs = str.c_str();
	INT Length = str.length();
	INT i = 0;
	INT j = 0;

	vector<KSCommand> CMD;

	while (i < Length)
	{
		KSCommand c;
		while (chrs[i] == ' ') i++;
		j = i;
		if (j >= Length)
			break;

		if (chrs[j] == '{')
		{

		}

		while (chrs[j] != ' ') j++;
		string p = str.substr(i, j - i);
		// p = p.append('\0');
		
		c.Cmd = p;
		CMD.push_back(c);
		i = j;
		i++;
	}

	return 0;
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


	GetSubSeg(str, sub, count);


	for (int i = 0; i < sub.size(); i++)
	{
		cout << sub[i] << endl;
	}
	cout << count << endl;

	//KSMain(argc, argv);

	/*KSTreeNode root;
	KSCommand cmd;
	cmd.Cmd = "G";
	cmd.CycleTime = 10;
	root.AddSub(&cmd);

*/


	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}

