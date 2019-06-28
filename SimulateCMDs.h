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
	int PressKey(WORD KeyCode);
	int PressKeys(WORD KeyCode[]);
	int ShowHelp();

	void MLD();
	void MLU();
	void MRD();
	void MRU();
	void MMD();
	void MMU();

	void MLC();
	void MRC();
	void MMC();

	void MV(int dx, int dy);
	void MV2(int dx, int dy);
};
