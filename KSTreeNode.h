#pragma once

#include <iostream>  
#include <map> 
#include <vector> 
#include <string>
using namespace std;

typedef int(*cmd_callback)(KSCommand str);


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

public:
	static int GetSubSeg(string str, vector<string> &sub, int &count);
	static void ParseStr2KSCmd(string str, KSCommand &cmd);
	void LoopCmd(KSCommand cmd, cmd_callback callback)
};



