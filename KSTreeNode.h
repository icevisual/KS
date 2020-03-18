#pragma once

#include <iostream>  
#include <map> 
#include <vector> 
#include <string>
using namespace std;



class KSCommand
{
public:
	// 指令内容
	string Cmd;
	// 循环次数
	int CycleTime;
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

