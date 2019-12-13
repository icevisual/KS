#pragma once
#include <iostream>  
#include <map> 
#include <vector> 
using namespace std;

class SimulateCMDs {

private:
	vector<string> CMDList;

public:
	int ParseCMDs(string str);
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
