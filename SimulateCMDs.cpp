#include "stdafx.h"
//
#include <sstream>  
#include <iostream>  
#include <map> 
#include "SimulateCMDs.h"
#include <iostream>  
#include "KSCommand.h"

using namespace std;

#include <opencv2/opencv.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include<opencv2/imgproc/imgproc.hpp>  


#include <cv.h>  
#include <highgui.h>  

using namespace cv;

Mat& ScanImageAndReduceIterator(Mat I)
{
	// accept only char type matrices
	CV_Assert(I.depth() == CV_8U);
	const int channels = I.channels();
	switch (channels)
	{
	case 1:
	{
		MatIterator_<uchar> it, end;
		for (it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
			printf("%d ", *it);
		break;
	}
	case 3:
	{
		//MatIterator_<Vec3b> it, end;
		//for (it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
		//{
		//	printf("%d,%d,%d\n", (*it)[0], (*it)[1], (*it)[2]);
		//}

		int nRows = I.rows;
		int nCols = I.cols * channels;
		int i = 0, j = 0;
		Vec3b * p;
		for (i = 0; i < nRows; ++i)
		{
			p = I.ptr<Vec3b>(i);
			for (j = 0; j < nCols; ++j)
			{
				printf("%d,%d,%d ", p[j][0], p[j][1], p[j][2]);
			}
			printf("\n");
		}

	}
	}
	return I;
}



int ScanImageCalcAvgColor(Mat I,bool show = false)
{
	// accept only char type matrices
	CV_Assert(I.depth() == CV_8U);
	const int channels = I.channels();
	if (channels != 1)
		return 0;
	int s = 0;
	int c = 0;
	int nRows = I.rows;
	int nCols = I.cols * channels;
	int i = 0, j = 0;
	uchar * p;
	for (i = 0; i < nRows; i += 2)
	{
		p = I.ptr<uchar>(i);
		for (j = 0; j < nCols; j += 2)
		{
			s += p[j];
			c++;
			if (show)
				printf("%d ", p[j]);
		}
		if (show)
			printf("\n");
	}
	if (c == 0)
		return 0;
	return s / c;
}


int CutScreenAndCalcAvgColor(int x,int y,int cx,int cy)
{
	LPRECT r = new RECT{ x,y,cx,cy };
	LPSTR addr = "CutScreenAndCalcAvgColor.png";
	CuteScreenRect(addr, r);

	Mat I = imread(string(addr), IMREAD_COLOR);
	Mat temp_gray;

	cvtColor(I, temp_gray, COLOR_BGR2GRAY);
	delete r;
	return ScanImageCalcAvgColor(temp_gray);
}

bool AreaBlack()
{
	return CutScreenAndCalcAvgColor(200, 400, 220, 420) < 10;
}
bool AreaWhite()
{
	return CutScreenAndCalcAvgColor(649, 606, 740, 640) > 200;
}

int SimulateCMDs::ProcessKSCommand(void * cmd)
{
	KSCommand * d = (KSCommand *)cmd;
	for (int i = 0; i < d->CycleTime; i++)
	{
		this->ParseCMDs(d->Cmd);
		this->Run();
	}
	return 1;
}

int SimulateCMDs::RunCMD(string SimulateString)
{
	//ParseCMDs(SimulateString);
	//Run();
	KSCommand cmd;
	KSCommand::ParseStr2KSCmd(SimulateString, cmd);
	KSCommand::LoopCmdS(cmd, this);
	return 1;
}
static int last_x = -1;
static int last_y = -1;

int SimulateCMDs::Run()
{
	// R0(S2 E )
	// K=kill(Alt + F4) F11=fn S2000=Sleep 2000 E=Hit Enter M=Mouse Click(L1|R1|M1,100,100)
	for (int i = 0; i < CMDList.size(); i++)
	{
		char CMDKey = CMDList[i].at(0);
		string params = CMDList[i].substr(1);
		switch (CMDKey)
		{
		case 'G':


			if (params.length() > 0 && params.at(0) == 'W') {
				// Ctrl + W : Close Page
				printf("Ctrl + w\n");
				WORD Keys[] = { VK_CONTROL,'w' - 'a' + 'A' };
				PressKeys(Keys);

				break;
			}

			// Get Mouse Position
			POINT p;
			GetCursorPos(&p);
			// printf("(%d,%d)\n", p.x, p.y);
			cout << "(" << p.x << "," << p.y << ")" << endl;
			last_x = p.x;
			last_y = p.y;
			break;
		case 'K':
			// Alt + F4
			Process_K(params);
			break;
		case 'I':
			// Input str
			Process_I(params);
			break;
		case 'C':
			// Ctrl + C
			Process_C(params);
			break;
		case 'P':
			// Ctrl + V
			Process_P(params);
			break;
		case 'S':
			// Sleep ms
			Process_S(params);
			break;
		case 'B':
			// Save Ctrl + S
		{
			printf("K = %s\n", params.c_str());
			WORD Keys[] = { VK_CONTROL,'s' - 'a' + 'A' };
			PressKeys(Keys);
		}
			break;
		case 'F':
			// FN
			Process_F(params);
			break;
		case 'E':
			// Enter
			Process_E(params);
			break;
		case 'M':
			// M=Mouse Click(L1|R1|M1,100,100)
			// Mouse Move
			// Mouse Double Click
			// MS set position
			Process_M(params);
			break;
		case 'D':
			// Delete
			Process_D(params);
		case 'L':
			// Win + Shift + L
			Process_L(params);
			break;
		case 'W':
		{
			// Whell W1 W-1
			printf("S = %s\n", params.c_str());
			INT r = ParseInt(params);
			printf("Wheel\n");
			INPUT Input = { 0 };
			Input.type = INPUT_MOUSE;
			Input.mi.dwFlags = MOUSEEVENTF_WHEEL;
			Input.mi.mouseData = WHEEL_DELTA * r;
			SendInput(1, &Input, sizeof(INPUT));
			break;
		}
		case 'J':
		{
			bool valid = false;
			int interval = 50;
			if (params.length() > 0)
			{
				int max_try = 100000;
				if (params.length() > 1)
					max_try = ParseInt(params.substr(1));

				if (params.at(0) == 'W') {
					
					do {
						valid = AreaWhite();
						cout << "AreaWhite valid=" << valid << " Left=" << max_try << endl;
						max_try--;
						Sleep(interval);

					} while (!valid && max_try > 0);
				}
				if (params.at(0) == 'B') {
					do {
						valid = AreaBlack();
						cout << "AreaWhite valid=" << valid << " Left=" << max_try << endl;
						max_try--;
						Sleep(interval);
					} while (!valid && max_try > 0);
				}
			}
			break;
		}
		break;
		default:
			break;
		}
	}
	return 0;
}

int SimulateCMDs::ParseCMDs(string str)
{
	CMDList.clear();
	str = str.append(" ");
	const char * chrs = str.c_str();
	INT Length = str.length();
	INT i = 0;
	INT j = 0;
	while (i < Length)
	{
		while (chrs[i] == ' ') i++;
		j = i;
		if (j >= Length)
			break;

		while (chrs[j] != ' ') j++;
		string p = str.substr(i, j - i);
		// p = p.append('\0');
		CMDList.push_back(p);
		i = j;
		i++;
	}
	
	return 0;
}


int SimulateCMDs::Process_I(string params)
{
	printf("I = %s\n", params.c_str());
	ConvertChar2KeyWordAndSimulate(params);
	return 0;
}



int  SimulateCMDs::Process_L(string params)
{
	printf("L = %s\n", params.c_str());
//	WORD Keys[] = { VK_LMENU,0x4C };
	WORD Keys[] = { VK_LMENU,VK_LSHIFT,'L' };
	PressKeys(Keys);
	return 0;
}

int SimulateCMDs::ShowHelp()
{
	printf("\n\
Usage:  \n\
  WinHotKeyA [options] -s=\"Commands[options] Commands[options] ...\"\n\
\n\
  Options\n\
    -t=<n>        Wait n ms Before Start\n\
    -c=<n>        Cycle n Times\n\
    -i=<n>        Cycle Wait Interval (ms)\n\
    -s=<str>      Commands\n\
    -l=[ic]       Register HotKeys For Copy & Image\
    -o=<filename> Set Output File\
\n\
  Commands:\n\
    K              Win + F4\n\
    I(string)      Input\n\
    S(int)         Sleep Seconds\n\
    F(int)         Fn\n\
    E              Enter\n\
    M(CAMS)        Mouse Action\n\
    D              Delete\n\
    C              Copy\n\
    P              Paste\n\
\n\
  Parameters for M:\n\
    MC[LMR]          Left|Right|Middle Click\n\
    MA[LMR][DU]      Left|Right|Middle Key Down\\Up\n\
    MM[+-](x),(y)        Move To Point(x,y)\n\
    MS(x),(y)        Set Position Point(x,y)\n\n");

	return 0;
}

int SimulateCMDs::Process_K(string params)
{
	printf("K = %s\n", params.c_str());
	WORD Keys[] = { VK_LMENU,VK_F4 };
	PressKeys(Keys);
	return 0;
}


int SimulateCMDs::Process_S(string params)
{
	printf("S = %s\n", params.c_str());
	INT r = ParseInt(params);

	if (r > 0)
		Sleep(r);
	return 0;
}


int SimulateCMDs::Process_F(string params)
{
	printf("F = %s\n", params.c_str());
	INT Fn = ParseInt(params);
	//WORD FnKeys[] = {
	//			0,VK_F1,VK_F2,VK_F3,VK_F4,VK_F5 ,
	//			VK_F6,VK_F7,VK_F8,VK_F9,VK_F10 ,
	//			VK_F11,VK_F12,VK_F13,VK_F14,VK_F15
	//};
	PressKey(VK_F1 + Fn - 1);
	return 0;
}


int SimulateCMDs::Process_E(string params)
{
	printf("E = %s\n", params.c_str());
	PressKey(VK_RETURN);
	return 0;
}


void ParseIntPair(string str,int * a,int * b)
{
	int va = 0;
	int vb = 0;
	int * vv = &va;
	for (int i = 0; i < str.length(); i++)
	{
		if (str.at(i) >= '0' && str.at(i) <= '9')
		{
			*vv = *vv * 10 + str.at(i) - '0';
		}
		else {
			vv = &vb;
		}
	}
	*a = va;
	*b = vb;
}

int SimulateCMDs::Process_M(string params)
{	
	// M=Mouse Click(L1|R1|M1,100,100)
	//  ���       MCL|MCR|MCM
	//  ���¡����� MALD|MALU|MARD|MARU
	//  �ƶ� ��    MM100,200
	//  ���� ����  MS100,200




	printf("M = %s\n", params.c_str());
	int x = 0, y = 0;
	auto p1 = params.at(0);
	switch (p1)
	{
	case 'C':
			switch (params.at(1))
			{
			case 'L':
				MLC();
				break;
			case 'R':
				MRC();
				break;
			case 'M':
				MMC();
				break;

			default:
				break;
			}
		break;
	case 'D':
		switch (params.at(1))
		{
		case 'L':
			MLC(); 
			Sleep(30);
			MLC();
			break;
		case 'R':
			MRC(); MRC();
			break;
		case 'M':
			MMC(); MMC();
			break;

		default:
			break;
		}
		break;
	case 'A':
		switch (params.at(1))
		{
		case 'L':
			params.at(2) == 'D'? MLD(): MLU();
			break;
		case 'R':
			params.at(2) == 'D' ? MRD() : MRU();
			break;
		case 'M':
			params.at(2) == 'D' ? MMD() : MMU();
			break;
		default:
			break;
		}
		break;
	case 'M':
		x = 0;
		y = 0;
		if (params.at(1) == '+' || params.at(1) == '-' ) {
			int f = params.at(1) == '-' ? -1 :1;
			int new_x = last_x;
			int new_y = last_y;
			ParseIntPair(params.substr(2), &x, &y);
			if (last_x < 0 || last_y < 0)
			{
				POINT p;
				GetCursorPos(&p);
				ParseIntPair(params.substr(2), &x, &y);
				last_x = p.x;
				last_y = p.y;
			}
			new_x = last_x + f * x;
			new_y = last_y + f * y;
			MV(new_x, new_y);
			cout << "(" << new_x << "," << new_y << ")" << endl;
			last_x = new_x;
			last_y = new_y;
		}
		else {
			ParseIntPair(params.substr(1), &x, &y);
			MV(x, y);
			last_x = x;
			last_y = y;
		}
		break;
	case 'S':
		x = 0;
		y = 0;
		ParseIntPair(params.substr(1), &x, &y);
		MV2(x, y);
		break;

	default:
		break;
	}

	return 0;
}


int SimulateCMDs::Process_D(string params)
{
	printf("D = %s\n", params.c_str());
	PressKey(VK_DELETE);
	return 0;
}

int SimulateCMDs::Process_C(string params)
{
	printf("C = %s\n", params.c_str());
	WORD Keys[] = { VK_CONTROL, 'c' - 'a' + 'A' };
	PressKeys(Keys);
	return 0;
}
int SimulateCMDs::Process_P(string params)
{
	printf("P = %s\n", params.c_str());
	WORD Keys[] = { VK_CONTROL, 'v' - 'a' + 'A' };
	PressKeys(Keys);
	return 0;
}
int SimulateCMDs::EnterWords(string words)
{
	ConvertChar2KeyWordAndSimulate(words);
	return 0;
}
int SimulateCMDs::PressKey(WORD KeyCode)
{
	WORD Keys[] = { KeyCode };
	SimulateKeyArrayInput(Keys, sizeof(Keys) / sizeof(WORD));
	return 0;
}
int SimulateCMDs::PressKeys(WORD KeyCode[])
{
	SimulateKeyArrayInput(KeyCode, sizeof(KeyCode) / sizeof(WORD));
	return 0;
}

void SingleKeyDown(DWORD KeyCode)
{
	INPUT Input = { 0 };
	// left down
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = KeyCode;
	SendInput(1, &Input, sizeof(INPUT));
}

void SimulateCMDs::MLD()
{
	SingleKeyDown(MOUSEEVENTF_LEFTDOWN);
}
void SimulateCMDs::MLU()
{
	SingleKeyDown(MOUSEEVENTF_LEFTUP);
}

void SimulateCMDs::MRD()
{
	SingleKeyDown(MOUSEEVENTF_RIGHTDOWN);
}
void SimulateCMDs::MRU()
{
	SingleKeyDown(MOUSEEVENTF_RIGHTUP);
}

void SimulateCMDs::MMD()
{
	SingleKeyDown(MOUSEEVENTF_MIDDLEDOWN);
}
void SimulateCMDs::MMU()
{
	SingleKeyDown(MOUSEEVENTF_MIDDLEUP);


	// MOUSEEVENTF_WHEEL
}

void SimulateCMDs::MV(int dx, int dy)
{
	INPUT  Input = { 0 };
	ZeroMemory(&Input, sizeof(INPUT));
	int cx_screen = ::GetSystemMetrics(SM_CXSCREEN);  // ��Ļ ��
	int cy_screen = ::GetSystemMetrics(SM_CYSCREEN);  //      ��

	Input.type = INPUT_MOUSE;
	Input.mi.dx = (dx) * 65535 / cx_screen;
	Input.mi.dy = (dy) * 65535 / cy_screen;

	Input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	Input.mi.mouseData = 0;

	SendInput(1, &Input, sizeof(INPUT));
}

void SimulateCMDs::MV2(int x, int y)
{
	SetCursorPos(x, y);
}

void SimulateCMDs::MLC()
{
	MLD();
	MLU();
}

void SimulateCMDs::MRC()
{
	MRD();
	MRU();
}

void SimulateCMDs::MMC()
{
	//WORD Keys[] = { MOUSEEVENTF_MIDDLEDOWN,MOUSEEVENTF_MIDDLEUP };
	//SimulateKeyArrayInput(Keys, sizeof(Keys) / sizeof(WORD));

	MMD();
	MMU();
}

