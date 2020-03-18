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
	// 将一行指令分割 {} ，转为 前中后 三个部分 
	static int GetSubSeg(string str, vector<string> &sub, int &count);
	// 递归调用 GetSubSeg 去除指令 存入 KSCommand 中
	static void ParseStr2KSCmd(string str, KSCommand &cmd);
	// 
	static void LoopCmd(KSCommand cmd, cmd_callback callback);
	// 避免循环引用头文件，使用 void *
	static void LoopCmdS(KSCommand cmd, void *  s);
};






