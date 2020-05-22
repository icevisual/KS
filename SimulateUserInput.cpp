#include "stdafx.h"
#include<sstream>
#include <map>

#include "SimulateCMDs.h"
#include "stdafx.h"
#include <vector>
#include <sstream>  
#include <iostream>  
#include <map>
#include <io.h>
#include <direct.h>
#include <regex>
#include <thread>
#include <future>
#include<math.h>
#include<windows.h>
using namespace std;
using std::vector;
using std::string;

using namespace std;

static FileConfig g_argv;
string OutputFile = "";
DWORD WINAPI ThreadFunction(LPVOID lpParam)
{
	
	INT SleepMilliSeconds = g_argv.GetArgv_INT("t", 2000);
	string SimulateString = g_argv.GetArgv_string("s", "");
	if (SimulateString.length() > 0)
	{
		Sleep(SleepMilliSeconds);
		ConvertChar2KeyWordAndSimulate(SimulateString);
		WORD Keys[] = { VK_RETURN };
		SimulateKeyArrayInput(Keys, sizeof(Keys) / sizeof(WORD));
	}
	return 0;
}

void MLD()
{
	INPUT Input = { 0 };
	// left down
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &Input, sizeof(INPUT));
}
void MLU()
{
	INPUT Input = { 0 };
	// left down
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &Input, sizeof(INPUT));
}

void MRD()
{
	INPUT Input = { 0 };
	// left down
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
	SendInput(1, &Input, sizeof(INPUT));
}
void MRU()
{
	INPUT Input = { 0 };
	// left down
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
	SendInput(1, &Input, sizeof(INPUT));
}

void MV(int dx,int dy)
{
	INPUT  Input = { 0 };
	ZeroMemory(&Input, sizeof(INPUT));
	int cx_screen = ::GetSystemMetrics(SM_CXSCREEN);  // 屏幕 宽
	int cy_screen = ::GetSystemMetrics(SM_CYSCREEN);  //      高

	Input.type = INPUT_MOUSE;
	Input.mi.dx = (dx) * 65535 / cx_screen;
	Input.mi.dy = (dy) * 65535 / cy_screen;

	Input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE ;
	Input.mi.mouseData = 0;

	SendInput(1, &Input, sizeof(INPUT));
}

void MV2(int x, int y)
{
	SetCursorPos(x, y);
}

void MLC()
{
	MLD();
	MLU();
}

void MLC(int x,int y)
{
	SetCursorPos(x,y);
	MLD();
	MLU();
}

void GetMousePosition()
{
	int x = 0;
	POINT  last = {0,0};
	while (x < 1500)
	{
		POINT  m_mouse;

		GetCursorPos(&m_mouse);
		if(!(last.x == m_mouse.x && last.y == m_mouse.y))
			printf("%d,%d\n", m_mouse.x, m_mouse.y);
		
		x = m_mouse.x;
		last = m_mouse;
		Sleep(100);
	}
}

void CalcColorPoint(vector<POINT> &R)
{
	POINT LeftTop = {764,57};
	int W = 16;
	int Gap = 6;
	int Count = 10;
	int Line = 2;
	for (int i = 0; i < Line; i++)
	{
		for (int j = 0; j < Count; j++)
		{
			POINT p = { LeftTop.x + W / 2 + j * (Gap + W),LeftTop.y + W / 2 + i * (Gap + W) };
			R.push_back(p);
		}
	}
}

void ResetCanvas()
{
	POINT SelectButton = { 122 ,68 };
	POINT BrushButton = { 345 ,73 };
	POINT LeftUp = { 5 ,164 };
	POINT RightButtom = { 946 ,782 };

	MV(SelectButton.x, SelectButton.y);
	MLC();

	MV(LeftUp.x, LeftUp.y);
	MLD();
	MV(RightButtom.x, RightButtom.y);
	MLU();

	WORD Keys[] = { VK_DELETE };
	SimulateKeyArrayInput(Keys, sizeof(Keys) / sizeof(WORD));

	MV(BrushButton.x, BrushButton.y);
	MLC();

}

VOID DrawLine(int x0, int y0, int x1, int y1)
{
	MV2(x0,y0);
	MLD();
	MV(x1, y1);
	MLU();
}

VOID DrawFFF()
{
	vector<POINT> R;
	CalcColorPoint(R);
	int rsize = R.size();
	POINT Start = {200,200};
	for (int i = 0; i < 100; i++)
	{
		MLC(R[(i) % rsize].x, R[(i) % rsize].y);
		DrawLine(Start.x, Start.y + i, Start.x + 300, Start.y + i);
		Sleep(1);
	}
	
}


VOID DrawC(int x0,int y0,int r)
{
	vector<POINT> R;
	CalcColorPoint(R);
	int rsize = R.size();

	//int x0 = 500, y0 = 500;
	int x = 0, y = 0;
	// x*x + y*y = r*r

	//int r = 100;
	int sl = 5;

	MV(x0 + r, y0);
	Sleep(sl);
	MLD();
	for (int i = r; i >= 0; i--)
	{
		y = y0 - (int)round(sqrt(r * r - i * i));
		x = x0 + i;
		MV(x, y);
		MLU();
		MLC(R[(x ) % rsize].x, R[(x) % rsize].y);
		MV2(x, y);
		MLD();
		Sleep(sl);
	}

	for (int i = 0; i <= r; i++)
	{
		y = y0 - (int)round(sqrt(r * r - i * i));
		x = x0 - i;
		MV(x, y);
		Sleep(sl);
	}

	for (int i = r; i >= 0; i--)
	{
		y = y0 + (int)round(sqrt(r * r - i * i));
		x = x0 - i;
		MV(x, y);
		Sleep(sl);
	}

	for (int i = 0; i <= r; i++)
	{
		y = y0 + (int)round(sqrt(r * r - i * i));
		x = x0 + i;
		MV(x, y);
		Sleep(sl);
	}

	MLU();
}


void helloworld1(string SimulateString)
{
	SimulateCMDs scl;
	scl.ParseCMDs(SimulateString);
	scl.Run();
}


void helloworld(string SimulateString)
{
	for (int i = 0; i < 1000; i++)
	{
		SimulateCMDs scl;
		scl.ParseCMDs(SimulateString);
		scl.Run();
		Sleep(200);
		// this_thread::sleep_for(chrono::milliseconds(200));
	}
}
bool G_Stop_HotKey = false;
bool G_Cycle_Stop = false;



bool SaveClipboard2File2()
{
	BOOL b1 = IsClipboardFormatAvailable(CF_TEXT);
	BOOL b2 = OpenClipboard(NULL);
	
	printf("IsClipboardFormatAvailable = %d,OpenClipboard = %d\n", b1, b2);
	if (b1 && b2)//打开剪贴板  
	{
		string str;
		HANDLE hClip;
		char* pBuf;
		LPTSTR    lptstr;
		HGLOBAL   hglb;
		hglb = GetClipboardData(CF_TEXT);
		if (hglb != NULL)
		{
			//lptstr = (LPTSTR) GlobalLock(hglb);
			pBuf = (char*)GlobalLock(hglb);
			if (pBuf != NULL)
			{
				printf("pBuf = %s\n", pBuf);

				FILE* fp;
				errno_t error = fopen_s(&fp, "C:\\Users\\Administrator\\Desktop\\link.txt", "a+");
				if (error == 0) {
					string str(pBuf);
					str += "\n";

					regex reg("(https?|ftp|file)://[-A-Za-z0-9+&@#/%?=~_|!:,.;]+[-A-Za-z0-9+&@#/%=~_|]");

					if (regex_match(str, reg)) {
						
					}

					fwrite(str.c_str(), sizeof(char), str.length(), fp);
					fclose(fp);
				}
				else {
					printf("Open File Failed\n");
				}

				GlobalUnlock(hglb);
				//EmptyClipboard();
			}
			else
			{
				printf("pBuf is NULL\n");
			}
		}
		else
		{
			printf("hglb is NULL\n");
		}

	}
	CloseClipboard();
	return b1 && b2;
}




bool SaveClipboard2File()
{
	BOOL b1 = IsClipboardFormatAvailable(CF_TEXT);
	BOOL b2 = OpenClipboard(NULL);

	printf("IsClipboardFormatAvailable = %d,OpenClipboard = %d\n", b1, b2);
	if (b1 && b2)//打开剪贴板  
	{
		string str;
		HANDLE hClip;
		char* pBuf;
		LPTSTR    lptstr;
		HGLOBAL   hglb;
		hglb = GetClipboardData(CF_TEXT);
		if (hglb != NULL)
		{
			//lptstr = (LPTSTR) GlobalLock(hglb);
			pBuf = (char*)GlobalLock(hglb);
			if (pBuf != NULL)
			{
				printf("pBuf = %s\n", pBuf);
				string str(pBuf);
				
				if (is_url(str)) {
					str += "\n";
					errno_t error = file_append_content("C:\\Users\\Administrator\\Desktop\\link.txt",str);
					if (error != 0) {
						printf("Open File Failed\n");
					}
				}
				else {
					printf("pBuf is not url\n");
				}
				GlobalUnlock(hglb);
				//EmptyClipboard();
				EmptyClipboard();
			}
			else
			{
				printf("pBuf is NULL\n");
			}
		}
		else
		{
			printf("hglb is NULL\n");
		}
	}
	CloseClipboard();
	return b1 && b2;
}


bool SaveClipboardContent2File(string filename)
{
	BOOL b1 = IsClipboardFormatAvailable(CF_TEXT);
	BOOL b2 = OpenClipboard(NULL);

	printf("IsClipboardFormatAvailable = %d,OpenClipboard = %d\n", b1, b2);
	if (b1 && b2)//打开剪贴板  
	{
		string str;
		HANDLE hClip;
		char* pBuf;
		LPTSTR    lptstr;
		HGLOBAL   hglb;
		hglb = GetClipboardData(CF_TEXT);
		if (hglb != NULL)
		{
			//lptstr = (LPTSTR) GlobalLock(hglb);
			pBuf = (char*)GlobalLock(hglb);
			if (pBuf != NULL)
			{
				printf("pBuf = %s\n", pBuf);
				string str(pBuf);

				str += "\n\n";
				size_t pos;

				while ((pos = str.find("\r\n")) != str.npos)
				{
					str = str.replace(str.find("\r\n"), 2, "\n");
				}

				errno_t error = file_append_content(filename, str);
				if (error != 0) {
					printf("Open File Failed\n");
				}

				GlobalUnlock(hglb);
				EmptyClipboard();
			}
			else
			{
				printf("pBuf is NULL\n");
			}
		}
		else
		{
			printf("hglb is NULL\n");
		}
	}
	CloseClipboard();
	return b1 && b2;
}



int RegisterHotKeys_Image()
{
	HWND hWnd = NULL;		// 窗口句柄
	MSG msg = { 0 };		// 消息
	DWORD dwThreadId = 0;	// 线程 ID
	DWORD error = 0;
	ATOM m_HotKeyId1 = GlobalAddAtom(_T("KS-STOP")) - 0xc000;
	ATOM m_HotKeyId2 = GlobalAddAtom(_T("KS-StopScript")) - 0xc000;
	ATOM m_HotKeyId3 = GlobalAddAtom(_T("KS-Terminate")) - 0xc000;
	ATOM m_HotKeyId4 = GlobalAddAtom(_T("KS-Terminate222")) - 0xc000;
	_tprintf(L"Register HotKeys ...\n");
	LocalRegisterHotKey(hWnd, m_HotKeyId1, MOD_NOREPEAT, VK_NUMPAD1);
	LocalRegisterHotKey(hWnd, m_HotKeyId2, MOD_NOREPEAT, 0x30 + '1' - '0');
	LocalRegisterHotKey(hWnd, m_HotKeyId3, MOD_NOREPEAT, 0x30 + '2' - '0');
	LocalRegisterHotKey(hWnd, m_HotKeyId4, MOD_NOREPEAT, 0x30 + '3' - '0');

	ClearClipboard();

	_tprintf(L"Press Key `NumPad 1` To Stop Cycle\n");
	SimulateCMDs scl;
	while (GetMessage(&msg, NULL, 0, 0) != 0) {
		DispatchMessage(&msg);
		if (msg.message == WM_HOTKEY) {

			if (m_HotKeyId1 == msg.wParam) {
				cout << "User Stopped" << endl;
				goto END;
			}
			else if (m_HotKeyId2 == msg.wParam) {
				// For Image Right Click
			    scl.RunCMD("MCR S100 Io");

				bool r = SaveClipboard2File();
				if (!r) {
					scl.RunCMD("MCR S100 Io");
					printf("====>REDO\n");
					SaveClipboard2File();
				}
			}
			else if (m_HotKeyId3 == msg.wParam) {

				scl.RunCMD("W-3");
			}
			else if (m_HotKeyId4 == msg.wParam) {


				WORD wd[1] = { VK_RIGHT };
				SimulateKeyArrayInput(wd, 1);
			}
		}
	}

END:

	UnregisterHotKey(hWnd, m_HotKeyId1);
	UnregisterHotKey(hWnd, m_HotKeyId2);
	UnregisterHotKey(hWnd, m_HotKeyId3);
	GlobalDeleteAtom(m_HotKeyId1);
	GlobalDeleteAtom(m_HotKeyId2);
	GlobalDeleteAtom(m_HotKeyId3);

	//system("pause");

	return 0;
}



typedef void(*VoidMapStringIntDelegate)(map<string, int> returnMap);
typedef void(*VoidNoParamsDelegate)();

int RegisterHotKeys_Common(VoidNoParamsDelegate Handle1, VoidNoParamsDelegate Handle2, VoidNoParamsDelegate Handle3)
{
	HWND hWnd = NULL;		// 窗口句柄
	MSG msg = { 0 };		// 消息
	DWORD dwThreadId = 0;	// 线程 ID
	DWORD error = 0;
	ATOM m_HotKeyId1 = GlobalAddAtom(_T("KS-STOP")) - 0xc000;
	ATOM m_HotKeyId2 = GlobalAddAtom(_T("KS-StopScript")) - 0xc000;
	ATOM m_HotKeyId3 = GlobalAddAtom(_T("KS-Terminate")) - 0xc000;
	ATOM m_HotKeyId4 = GlobalAddAtom(_T("KS-Terminate222")) - 0xc000;
	_tprintf(L"Register HotKeys ...\n");
	LocalRegisterHotKey(hWnd, m_HotKeyId1, MOD_NOREPEAT, VK_NUMPAD1);
	LocalRegisterHotKey(hWnd, m_HotKeyId2, MOD_NOREPEAT, 0x30 + '1' - '0');
	LocalRegisterHotKey(hWnd, m_HotKeyId3, MOD_NOREPEAT, 0x30 + '2' - '0');
	LocalRegisterHotKey(hWnd, m_HotKeyId4, MOD_NOREPEAT, 0x30 + '3' - '0');

	ClearClipboard();

	_tprintf(L"Press Key `NumPad 1` To Stop Cycle\n");
	SimulateCMDs scl;
	while (GetMessage(&msg, NULL, 0, 0) != 0) {
		DispatchMessage(&msg);
		if (msg.message == WM_HOTKEY) {

			if (m_HotKeyId1 == msg.wParam) {
				cout << "User Stopped" << endl;
				goto END;
			}
			else if (m_HotKeyId2 == msg.wParam) {
				if (Handle1)
					Handle1();
			}
			else if (m_HotKeyId3 == msg.wParam) {

				if (Handle2)
					Handle2();
			}
			else if (m_HotKeyId4 == msg.wParam) {

				if (Handle3)
					Handle3();
			}
		}
	}

END:

	UnregisterHotKey(hWnd, m_HotKeyId1);
	UnregisterHotKey(hWnd, m_HotKeyId2);
	UnregisterHotKey(hWnd, m_HotKeyId3);
	GlobalDeleteAtom(m_HotKeyId1);
	GlobalDeleteAtom(m_HotKeyId2);
	GlobalDeleteAtom(m_HotKeyId3);

	//system("pause");

	return 0;
}




int RegisterHotKeys_Image1()
{
	RegisterHotKeys_Common(
		[]() { 
			SimulateCMDs scl;
			// For Image Right Click
			scl.RunCMD("MCR S100 Io");

			bool r = SaveClipboard2File();
			if (!r) {
				scl.RunCMD("MCR S100 Io");
				printf("====>REDO\n");
				SaveClipboard2File();
			}
		},
		[]() {
			SimulateCMDs scl;
			scl.RunCMD("W-3");
		},
		[]() {
			WORD wd[1] = { VK_RIGHT };
			SimulateKeyArrayInput(wd, 1);
		}
	);

	return 0;
}


int RegisterHotKeys_Copy()
{
	RegisterHotKeys_Common(
		[]() {
		string cmd = "C";
		//scl.RunCMD(cmd);
		SaveClipboardContent2File(OutputFile);
	},
		[]() {
		SimulateCMDs scl;
		scl.RunCMD("W-3");
	},
		[]() {
		WORD wd[1] = { VK_RIGHT };
		SimulateKeyArrayInput(wd, 1);
	}
	);

	return 0;
}



int RegisterHotKeys()
{
	HWND hWnd = NULL;		// 窗口句柄
	MSG msg = { 0 };		// 消息
	DWORD dwThreadId = 0;	// 线程 ID
	DWORD error = 0;
	ATOM m_HotKeyId1 = GlobalAddAtom(_T("KS-STOP")) - 0xc000;
	ATOM m_HotKeyId2 = GlobalAddAtom(_T("KS-StopScript")) - 0xc000;
	ATOM m_HotKeyId3 = GlobalAddAtom(_T("KS-Terminate")) - 0xc000;
	ATOM m_HotKeyId4 = GlobalAddAtom(_T("KS-Terminate222")) - 0xc000;
	_tprintf(L"Register HotKeys ...\n");
	LocalRegisterHotKey(hWnd, m_HotKeyId1, MOD_NOREPEAT, VK_NUMPAD1);
	LocalRegisterHotKey(hWnd, m_HotKeyId2, MOD_NOREPEAT, 0x30 + '1' - '0');
	LocalRegisterHotKey(hWnd, m_HotKeyId3, MOD_NOREPEAT, 0x30 + '2' - '0');
	LocalRegisterHotKey(hWnd, m_HotKeyId4, MOD_NOREPEAT, 0x30 + '3' - '0');

	ClearClipboard();

	_tprintf(L"Press Key `NumPad 1` To Stop Cycle\n");
	SimulateCMDs scl;
	while (GetMessage(&msg, NULL, 0, 0) != 0) {
		DispatchMessage(&msg);
		if (msg.message == WM_HOTKEY) {

			if (m_HotKeyId1 == msg.wParam) {
				cout << "User Stopped" << endl;
				goto END;
			}
			else if (m_HotKeyId2 == msg.wParam) {
				


				// For Image Right Click
		/*		scl.RunCMD("MCR S100 Io");

				bool r = SaveClipboard2File();
				if (!r) {
					scl.RunCMD("MCR S100 Io");
					printf("====>REDO\n");
					SaveClipboard2File();
				}*/

				string cmd = "C";
				//scl.RunCMD(cmd);
				SaveClipboardContent2File(OutputFile);


				/*
				string cmd = "MCR S200 G MM+10,10 MCL";
				scl.RunCMD(cmd);

				bool r = SaveClipboardContent2File(OutputFile);
				if (!r) {
					scl.RunCMD(cmd);
					printf("====>REDO\n");
					SaveClipboardContent2File(OutputFile);
				}*/
			}
			else if (m_HotKeyId3 == msg.wParam) {

				scl.RunCMD("W-3");
			}
			else if (m_HotKeyId4 == msg.wParam) {
				

				WORD wd[1] = {VK_RIGHT};
				SimulateKeyArrayInput(wd,1);
			}
		}
	}

END:

	UnregisterHotKey(hWnd, m_HotKeyId1);
	UnregisterHotKey(hWnd, m_HotKeyId2);
	UnregisterHotKey(hWnd, m_HotKeyId3);
	GlobalDeleteAtom(m_HotKeyId1);
	GlobalDeleteAtom(m_HotKeyId2);
	GlobalDeleteAtom(m_HotKeyId3);

	//system("pause");

	return 0;
}

INT KSMain(int argc, CHAR * argv[])
{

	thread t1(RegisterHotKeys_Copy);


	// 582 443 + 20
	// Elona Wish Ctrl + V
	// ./WinGHotKey.exe -t=5000 -s="IZ S500 Id S300 P E" -c=1000 -i=300
	// ./WinGHotKey.exe -t=5000 -s="{IZ S500 Id S300 P {E}2}2" -c=1000 -i=300
	// ./WinGHotKey.exe -t=5000 -s="MCM" quest  
	// 需要授权的确认界面，无法用程序模拟点击
	g_argv.ParseArgvs(argc, argv);
	// 准备时间 ms
	INT SleepMilliSeconds = g_argv.GetArgv_INT("t", 0);
	// 循环次数
	INT Cycle = g_argv.GetArgv_INT("c", 1);
	// 循环间隔 ms
	INT Interval = g_argv.GetArgv_INT("i", 200);
	// 循环间隔 ms
	INT Listen = g_argv.GetArgv_INT("l", 0);
	// 指令
	string SimulateString = g_argv.GetArgv_string("s", "");

	// 指令
	OutputFile = g_argv.GetArgv_string("o", "");

	if (SleepMilliSeconds > 0)
		Sleep(SleepMilliSeconds);
	if (SimulateString.length() > 0)
	{
		for (int i = 0; i < Cycle; i++)
		{
			SimulateCMDs scl;
			scl.RunCMD(SimulateString);
			Sleep(Interval);
		}
		
		if (Listen == 0)
		{
			SimulateCMDs sc2;
			sc2.PressKey(VK_NUMPAD1);
		}
		//HWND cmd = GetConsoleWindow();

		//auto pwnd = FindWindow(L"ExploreWClass", NULL); //希望找到资源管理器
	

		//
		//SendMessage(NULL, WM_HOTKEY, m_HotKeyId1, 0);
		//
	}
	else
	{
		SimulateCMDs scl;
		scl.ShowHelp();
		return 0;
	}
	t1.join();
	
	return 0;
	// CMD List 
	// K=kill(Alt + F4) F11=fn S2=Sleep 2000ms E=Hit Enter 
	// M=Mouse Click(L1|R1|M1,100,100)
	//  点击       MCL|MCR|MCM
	//  按下、弹起 MALD|MALU|MARD|MARU
	//  移动 到    MM100,200
	//  设置 坐标  MS100,200

}

