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
	int Process_K(string params);
	int Process_S(string params);
	int Process_F(string params);
	int Process_E(string params);
	int Process_M(string params);
	int Process_D(string params);
	int PressKey(WORD KeyCode);
	int PressKeys(WORD KeyCode[]);
};