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
	static void LoopCmd(KSCommand cmd, cmd_callback callback);
	static void LoopCmdS(KSCommand cmd, void *  s);
};






