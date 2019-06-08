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
	int cx_screen = ::GetSystemMetrics(SM_CXSCREEN);  // фад╩ ©М
	int cy_screen = ::GetSystemMetrics(SM_CYSCREEN);  //      ╦ъ

	Input.type = INPUT_MOUSE;
	Input.mi.dx = (dx) * 65535 / cx_screen;
	Input.mi.dy = (dy) * 65535 / cy_screen;

	Input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE ;
	Input.mi.mouseData = 0;

	SendInput(1, &Input, sizeof(INPUT));
}

void MLC()
{
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

VOID DrawC(int x0,int y0,int r)
{


	//int x0 = 500, y0 = 500;
	int x = 0, y = 0;
	// x*x + y*y = r*r

	//int r = 100;
	int sl = 1;

	MV(x0 + r, y0);
	Sleep(sl);
	MLD();
	for (int i = r; i >= 0; i--)
	{
		y = y0 - (int)round(sqrt(r * r - i * i));
		x = x0 + i;
		MV(x, y);
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


INT main(int argc, CHAR * argv[])
{
	//GetMousePosition();
	//return 0;
	Sleep(7000);

	ResetCanvas();
	Sleep(100);



	for (int i = 0; i < 35; i++)
	{
		DrawC(200 + i * 6, 500, 30 + i * 5);

	}


	return 0;
	

	g_argv.ParseArgvs(argc, argv);

	INT SleepMilliSeconds = g_argv.GetArgv_INT("t", 2000);
	string SimulateString = g_argv.GetArgv_string("s", "");
	INT Fn = g_argv.GetArgv_INT("f", 0);
	INT Kill = g_argv.GetArgv_INT("kill", 0);

	INT UsingCMD = g_argv.GetArgv_INT("uc", 0);

	if (UsingCMD > 0)
	{
		SimulateCMDs scl;
		scl.ParseCMDs(SimulateString);
		scl.Run();
	}

	// CMD List 
	// K=kill(Alt + F4) F11=fn S2000=Sleep 2000 E=Hit Enter M=Mouse Click(L1|R1|M1,100,100)
	//
	if (SimulateString.length() > 0)
	{
		if(SleepMilliSeconds > 0 )
			Sleep(SleepMilliSeconds);
		if (Fn > 0 && Fn <=15 )
		{
			WORD FnKeys[] = { 
				0,VK_F1,VK_F2,VK_F3,VK_F4,VK_F5 ,
				VK_F6,VK_F7,VK_F8,VK_F9,VK_F10 ,
				VK_F11,VK_F12,VK_F13,VK_F14,VK_F15 
			};
			WORD Keys[] = { FnKeys[Fn] };
			SimulateKeyArrayInput(Keys, sizeof(Keys) / sizeof(WORD));
		}
		else if (Kill > 0)
		{
			WORD Keys[] = { VK_LMENU,VK_F4 };
			SimulateKeyArrayInput(Keys, sizeof(Keys) / sizeof(WORD));
		}
		else
		{
			ConvertChar2KeyWordAndSimulate(SimulateString);
			WORD Keys[] = { VK_RETURN };
			SimulateKeyArrayInput(Keys, sizeof(Keys) / sizeof(WORD));
		}

	}
	return 0;
}

