#pragma once
#include <iostream>  
#include <map> 
#include <vector> 
#include "KSCommand.h"
using namespace std;

class SimulateCMDs {

private:
	vector<string> CMDList;

public:
	// 将指令行 分解成 单个指令
	int ParseCMDs(string str);

	// 遍历 KSCommand 的回调函数 ,避免循环引用头文件，使用 void *
	int ProcessKSCommand(void * cmd);
	// 用 KSCommand 分解遍历 指令
	int RunCMD(string str);

	// 运行 分解的指令
	int Run();

	// Kill Win + F4
	int Process_K(string params);
	// Sleep
	int Process_S(string params);
	// F1 - Fn
	int Process_F(string params);
	// Enter
	int Process_E(string params);
	// Mouse Action
	int Process_M(string params);
	// Delete
	int Process_D(string params);
	// Win + L (Can't)
	int Process_L(string params);
	// Input
	int Process_I(string params);

	/* Paste */
	int Process_P(string params);
	/* Copy */
	int Process_C(string params);

	int Process_MouseSelectArea() {}

	int PressKey(WORD KeyCode);
	int EnterWords(string words);
	int EnterWord(char word) {}
	int PressKeys(WORD KeyCode[]);
	int ShowHelp();

	/* Mouse Left Down */
	void MLD();
	/* Mouse Left Up */
	void MLU();
	/* Mouse Right Down */
	void MRD();
	/* Mouse Left Up */
	void MRU();
	/* Mouse Middle Down */
	void MMD();
	/* Mouse Middle Up */
	void MMU();
	/* Mouse Left Click */
	void MLC();
	/* Mouse Right Click */
	void MRC();
	/* Mouse Middle Click */
	void MMC();
	/* Mouse Move To Position */
	void MV(int dx, int dy);
	/* Mouse Change Position */
	void MV2(int dx, int dy);
};
