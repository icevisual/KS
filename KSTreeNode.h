#pragma once

#include <iostream>  
#include <map> 
#include <vector> 
#include <string>
using namespace std;



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
};



class KSTreeNode {

public:
	KSCommand * DataNode;
	KSTreeNode * Next;
	KSTreeNode * Sub;

public:
	void AddSub(KSCommand * Data);
};

