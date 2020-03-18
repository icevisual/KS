#pragma once

#include <iostream>  
#include <map> 
#include <vector> 
#include <string>
#include "SimulateCMDs.h"
using namespace std;


class KSCommand;
typedef int(*cmd_callback)(KSCommand str);

class KSCommand
{
public:
	string Cmd;
	// 指令内容
	vector<KSCommand> SubCmds;

	bool HasSubCmds = false;
	// 循环次数
	int CycleTime = 1;
	// 触发条件
	string Condition;
	
public:
	static int GetSubSeg(string str, vector<string> &sub, int &count);
	static void ParseStr2KSCmd(string str, KSCommand &cmd);
	static void LoopCmd(KSCommand cmd, cmd_callback callback);
	static void LoopCmdS(KSCommand cmd, void *  s);
};






