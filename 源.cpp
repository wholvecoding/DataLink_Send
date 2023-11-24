#pragma once
#define _CRT_SECURE_NO_WARNINGS
#pragma  comment(lib,"ws2_32.lib")
// ARQ_s.cpp : Defines the entry point for the application.
//VC 6.0   add  WSOCK32.LIB in Project -> Settings... ->  Link
#include <winsock.h>
#include<iostream>
using namespace std;
//--------------------------------------------------------------
// Global Variables:
HINSTANCE hInst;						// current instance

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
//--------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lp, int nC)
{
	MSG msg;
	HWND hWnd;
	hInst = hI; // Store instance handle in our global variable
	WNDCLASS wc;

	memset(&wc, 0, sizeof(WNDCLASS));

	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.hInstance = hI;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "W1";
	RegisterClass(&wc);

	hWnd = CreateWindow("W1", "发送端[6666]－理想信道",
		WS_DLGFRAME | WS_SYSMENU,
		100, 300, 700, 500,
		NULL, NULL, hI, NULL);

	if (!hWnd)   return FALSE;

	ShowWindow(hWnd, nC);
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
//--------------------------------------------------------------
//按钮
HWND CreateButton(char* Titel, int x0, int y0, int w, int h, int ID, HWND hW, HINSTANCE hInst)
{
	return CreateWindowEx(WS_EX_PALETTEWINDOW, "BUTTON", Titel,
		WS_VISIBLE | WS_CHILD,
		x0, y0, w, h, hW, (HMENU)ID, hInst, NULL);
}
//--------------------------------------------------------------
//单行编辑框
HWND CreateEdit(char* Titel, int x0, int y0, int w, int h, int ID, HWND hW, HINSTANCE hInst)
{
	return CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", Titel,
		WS_VISIBLE | WS_CHILD |
		ES_LEFT | ES_MULTILINE | WS_HSCROLL,
		x0, y0, w, h, hW,
		(HMENU)ID, hInst, NULL);
}
//--------------------------------------------------------------
//多行文本框
HWND CreateMemo(char* Titel, int x0, int y0, int w, int h, int ID, HWND hW, HINSTANCE hInst)
{
	return CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", Titel,
		WS_VISIBLE | WS_CHILD |
		ES_LEFT | ES_MULTILINE | ES_READONLY |
		WS_HSCROLL | WS_VSCROLL,
		x0, y0, w, h,
		hW, (HMENU)ID, hInst, NULL);
}
//---------------------------------------------------------------------------
//添加控件文本
void Puts(HWND hW, int ID_EDIT, char* str)
{
	char b[8888];
	GetDlgItemText(hW, ID_EDIT, b, sizeof(b));

	strcat(b, "\r\n");
	strcat(b, str);
	SetDlgItemText(hW, ID_EDIT, (LPSTR)b);
	SendMessage(GetDlgItem(hW, ID_EDIT), WM_VSCROLL, SB_THUMBPOSITION + 1000 * 0x10000, 0);
}

//uint8_t crc(uint8_t* str, size_t length) {
//	uint8_t data = 0;  //定义一个8位无符号整形，用于处理单个字符串
//	uint8_t crc = 0;  //用于形成循环冗余校验码
//	uint8_t poly = 0x07;  // 使用CRC-8的生成多项式
//
//	while (length--) { //获得单独的字符串
//		data = *(str++);
//		crc = crc ^ data;  //最开始初始化crc=data，之后
//
//		for (int i = 0; i < 8; i++) {
//			if (crc & 0x80) { //如果当前crc的最高位1，因为生成多项式最高位为1，因此可以左移后与生成多项式异或，计算下一步
//				crc = (crc << 1) ^ poly;
//			}
//			else {
//				crc = crc << 1;  //当crc最高位为0，直接左移
//			}
//		}
//	}
//
//	return crc;
//}
//void getsCrc(HWND hW, int ID_EDIT, char* str)
//{
//	uint8_t b[8888];
//	GetDlgItemText(hW, ID_EDIT, reinterpret_cast<char*>(b), sizeof(b));
//	//crc(b,sizeof(b));
//	
//	SetDlgItemText(hW, ID_EDIT, (LPSTR)(crc(b,sizeof(b))));
//}
//---------------------------------------------------------------------------
//按钮
#define BUTTON1 501
#define BUTTON2 502
#define BUTTON3 503
//单行编辑框
#define EDIT1 601
#define ANSWER 602
//多行文本框
#define MEMO1 801  //接收的
#define MEMO2 802  //发送的

//--------------------------------------------------------------
WSADATA ws;
SOCKET Cs1, Cs2;
struct sockaddr_in Cs1A, Cs2A;
uint8_t x = 0x00;
char aa[200];
char mysend;
char bb[200];
char cc[200];
int d, i;
#define Cs2Port 7777		//远程端口
#define Cs1Port 6666		//本地端口
#define Cs1IP   "127.0.0.1"	//本地网址
#define Cs2IP   "127.0.0.1"	//远程网址
//以上不需改动!
//--------------------------------------------------------------
//你可以在这里定义变量
int SendBufLeng;			//报文长度
int Sendi;					//数据帧发送计数
BYTE mywlcSend(BYTE c);		//物理层：发送一个字节
BYTE wlcRev();				//物理层：接收一个字节
char SetCheck(char& c);     //偶校验：针对发送数据
//--------------------------------------------------------------
//消息处理
LRESULT CALLBACK WndProc(HWND hW, UINT msg, WPARAM wP, LPARAM lP)
{
	const char* p = "请输入你想发送的消息";

	switch (msg)
	{
	case WM_DESTROY:
		WSAAsyncSelect(Cs1, hW, 0, 0);
		closesocket(Cs1);
		WSACleanup();
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		WSAStartup(0x0101, &::ws);
		Cs1 = socket(AF_INET, SOCK_DGRAM, 0);
		Cs1A.sin_family = AF_INET;
		Cs1A.sin_port = htons(Cs1Port);
		//		Cs1A.sin_addr.s_addr =INADDR_ANY;//在本机设置的网址(可能多个)中，都有效。
		Cs1A.sin_addr.s_addr = inet_addr(Cs1IP);
		d = bind(Cs1, (struct sockaddr*)&Cs1A, sizeof(Cs1A));
		if (d == -1)
		{
			MessageBox(0, "端口发生冲突", "数字信道仿真", 0);
			PostQuitMessage(0);
		}
		Cs2A.sin_family = AF_INET;
		Cs2A.sin_port = htons(Cs2Port);
		Cs2A.sin_addr.s_addr = inet_addr(Cs2IP);
		WSAAsyncSelect(Cs1, hW, WM_USER + 1, FD_READ);
		Beep(2000, 100);
	
		//SendMessage(hW,WM_CREATE, wP, lP);
		CreateEdit(const_cast <char*>(p), 20, 20, 230, 70, EDIT1, hW, hInst);
		//CreateEdit(const_cast<char*>("1234567890"), 2, 2, 130, 20, EDIT1, hW, hInst);
		CreateButton(const_cast <char*>("send"), 250, 20, 50, 60, BUTTON1, hW, hInst);
		CreateButton(const_cast <char*>("Reset"), 350, 20, 50, 60, BUTTON2, hW, hInst);
		CreateButton(const_cast <char*>("生成校验码"), 450, 20, 100, 60, BUTTON3, hW, hInst);
		//物理层发送的消息提示
		CreateWindow("STATIC", "发送端物理层发送的信息",
			WS_VISIBLE | WS_CHILD,
			50, 100, 200, 20, hW, NULL, hInst, NULL);
		CreateMemo(const_cast <char*>(""), 50, 150, 200, 220, MEMO2, hW, hInst);
		CreateMemo(const_cast <char*>("校验码"),500 , 90, 100, 220, ANSWER, hW, hInst);
		CreateWindow("STATIC", "发送端物理层接收的消息",
			WS_VISIBLE | WS_CHILD,
			260, 100, 200, 20, hW, NULL, hInst, NULL);
		CreateMemo(const_cast<char*>(""), 260, 150, 200, 220, MEMO1, hW, hInst);
		
		
		break;
		//============================================================================
		//接收事件触发：
		//你可以在这里编写代码：
	case WM_USER + 1:
		switch (LOWORD(lP))
		{
		case FD_READ:
			bb[0] = wlcRev();					//物理层：接收一个字节
			bb[1] = 0;
			char buf[22];
			
			wsprintf(buf, "%02XH,%c", (unsigned char)bb[0], bb[0]);
			Puts(hW, MEMO1, buf);				//显示，物理层收到的信息
			//getsCrc(hW, ANSWER, buf1);
			//MessageBox(0,bb,"(FD_READ)",0);
			break;
		}
		break;
	case WM_COMMAND:
		switch (wP)
		{
		case BUTTON1:		
			
			
			// "Send" 按钮事件触发	
			GetDlgItemText(hW, EDIT1, aa, sizeof(aa));		//从单行编辑框得到报文
			
			char xx[20];
			
			SendBufLeng = strlen(aa);						//求出报文长度
			for (Sendi = 0; Sendi < SendBufLeng; Sendi++)		//发送报文
			{  
				
				aa[Sendi] = (aa[Sendi] & 0x0F) + x;			//将发送序号加入
				if (x != 0x70)x += 0x10;                    //控制序号变化
				else x = 0x00;								//序号只能有8种，超过后重置
				mysend = SetCheck(aa[Sendi]);               //将待发送的数据进行偶校验，并在最左位补校验位
				mywlcSend(mysend);					//物理层：发送一个字节
				wsprintf(xx, "%02XH", (unsigned char)mysend); //将发送的消息(ascii码)转变为十六进制，存放到xx.消息目前只能是单字节（）
				Puts(hW, MEMO2, xx);						//将xx定向到MEMO2中，在文本框显示出
			}
			break;

		case BUTTON2:									//清除信息框内容
			SetDlgItemText(hW, MEMO1, (LPSTR)"");
			SetDlgItemText(hW, MEMO2, (LPSTR)" ");
			x = 0x00;
			break;
		/*case BUTTON3:
			SetDlgItemText(hW, ANSWER, (LPSTR)"");
			
			break;*/
		}
	}
	return DefWindowProc(hW, msg, wP, lP);
}
//--------------------------------------------------------------
BYTE mywlcSend(BYTE c)	//物理层：发送一个字节
{
	char a[2];
	a[0] = c; a[1] = 0;
	d = sizeof(Cs2A);
	sendto(Cs1, a, 1, 0, (struct sockaddr*)&Cs2A, d);
	return  c;
}
//--------------------------------------------------------------
BYTE wlcRev()			//物理层：接收一个字节
{
	char b[1];
	d = sizeof(Cs2A);
	d = recvfrom(Cs1, b, 1, 0, (struct sockaddr*)&Cs2A, &d);
	return b[0];
}
char SetCheck(char& c) //C为一个字节
{
	int i, sum = 0;
	BYTE x = 0x01;
	for (i = 0; i < 7; i++)
	{
		if (c & x) sum++;
		x = x << 1;
	}
	if (sum % 2) c = c | 0x80;
	else c = c & 0x7F;
	return c;
}


//--------------------------------------------------------------
