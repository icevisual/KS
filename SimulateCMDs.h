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
	/* kill / VK_LMENU,VK_F4 */
	int Process_K(string params);
	/* Sleep ms */
	int Process_S(string params);
	/* Fn */
	int Process_F(string params);
	/* Enter */
	int Process_E(string params);
	/* Mouse Move (Unfinished) */
	int Process_M(string params);
	/* Delete */
	int Process_D(string params);
	/* Paste */
	int Process_P(string params);
	/* Copy */
	int Process_C(string params);

	int Process_MouseSelectArea() {}
	int PressKey(WORD KeyCode);
	int EnterWords(string words);
	int EnterWord(char word) {}
	int PressKeys(WORD KeyCode[]);
};