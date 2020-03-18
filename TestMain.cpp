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

// 解析带括号的指令字符串，存到 sub 中，第一行为 括号前，第二行括号内，第三行括号后，无内容填入 空字符串
// 返回是否有子项，1 有子项，0 没有，-1 格式错误
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
					sub.push_back(str.substr(0, j - 1));
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

// 递归调用 GetSubSeg ，将指令存入 KSCommand
void ParseStr2KSCmd(string str, KSCommand &cmd)
{
	vector<string> sub;
	int count = 0;
	int r = 0;
	r = GetSubSeg(str, sub, count);
	if (r == 0)
	{
		// no {
		cmd.Cmd = str;
	}
	else
	{
		cmd.HasSubCmds = true;
		if (sub[0].length() > 0)
		{
			KSCommand tmp;
			tmp.Cmd = sub[0];
			cmd.SubCmds.push_back(tmp);
		}

		KSCommand tmp1;
		tmp1.CycleTime = count;

		ParseStr2KSCmd(sub[1], tmp1);
		cmd.SubCmds.push_back(tmp1);
		if (sub[2].length() > 0)
		{
			KSCommand tmp;
			tmp.Cmd = sub[2];
			cmd.SubCmds.push_back(tmp);
		}
	}
}

typedef int(*cmd_callback)(KSCommand str);

int show_cmd(KSCommand cmd)
{
	cout << cmd.Cmd << " * " << cmd.CycleTime << endl;
	return 1;
}

// 带回调函数的遍历 KSCommand
void LoopCmd(KSCommand cmd, cmd_callback callback)
{
	if (cmd.HasSubCmds)
	{
		for (int j = 0; j < cmd.CycleTime; j++)
		{
			for (int i = 0; i < cmd.SubCmds.size(); i++) {
				LoopCmd(cmd.SubCmds[i], callback);
			}
		}
	}
	else
	{
		cout << cmd.Cmd << " * "<< cmd.CycleTime << endl;
	}
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
	ParseStr2KSCmd(str1,cmd);

	LoopCmd(cmd, show_cmd);

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

