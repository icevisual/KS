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
	// ָ������
	vector<KSCommand> SubCmds;

	bool HasSubCmds = false;
	// ѭ������
	int CycleTime = 1;
	// ��������
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

