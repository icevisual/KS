#include "stdafx.h"
//
#include "KSCommand.h"  
#include "SimulateCMDs.h"  
// 解析带括号的指令字符串，存到 sub 中，第一行为 括号前，第二行括号内，第三行括号后，无内容填入 空字符串
// 返回是否有子项，1 有子项，0 没有，-1 格式错误
int KSCommand::GetSubSeg(string str, vector<string> &sub, int &count)
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
				while (i < Length && str.at(i++) == ' ');
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
void KSCommand::ParseStr2KSCmd(string str, KSCommand &cmd)
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


// SimulateCMDs


// 带回调函数的遍历 KSCommand
void KSCommand::LoopCmdS(KSCommand cmd, void *  s)
{
	if (cmd.HasSubCmds)
	{
		for (int j = 0; j < cmd.CycleTime; j++)
		{
			for (int i = 0; i < cmd.SubCmds.size(); i++) {
				LoopCmdS(cmd.SubCmds[i], s);
			}
		}
	}
	else
	{
		((SimulateCMDs*)s)->ProcessKSCommand(&cmd);
	}
}


// 带回调函数的遍历 KSCommand
void KSCommand::LoopCmd(KSCommand cmd, cmd_callback callback)
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
		cout << cmd.Cmd << " * " << cmd.CycleTime << endl;
	}
}

