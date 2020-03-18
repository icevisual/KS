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

#include <thread>
#include <future>

#include<math.h>
#include<windows.h>
using namespace std;
using std::vector;
using std::string;

using namespace std;

static FileConfig g_argv;

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


INT main(int argc, CHAR * argv[])
{
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
	// 指令
	string SimulateString = g_argv.GetArgv_string("s", "");
	if (SleepMilliSeconds > 0)
		Sleep(SleepMilliSeconds);
	if (SimulateString.length() > 0)
	{
		for (int i = 0; i < Cycle; i++)
		{
			SimulateCMDs scl;
			scl.ParseCMDs(SimulateString);
			scl.Run();
			Sleep(Interval);
		}

		////开启一个线程 
		//std::thread t(helloworld, SimulateString);


		////线程的终结
		//t.join();


	}
	else
	{
		SimulateCMDs scl;
		scl.ShowHelp();
		return 0;
	}
	
	
	return 0;
	// CMD List 
	// K=kill(Alt + F4) F11=fn S2=Sleep 2000ms E=Hit Enter 
	// M=Mouse Click(L1|R1|M1,100,100)
	//  点击       MCL|MCR|MCM
	//  按下、弹起 MALD|MALU|MARD|MARU
	//  移动 到    MM100,200
	//  设置 坐标  MS100,200

}

