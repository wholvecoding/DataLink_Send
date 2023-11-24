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

	hWnd = CreateWindow("W1", "���Ͷ�[6666]�������ŵ�",
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
//��ť
HWND CreateButton(char* Titel, int x0, int y0, int w, int h, int ID, HWND hW, HINSTANCE hInst)
{
	return CreateWindowEx(WS_EX_PALETTEWINDOW, "BUTTON", Titel,
		WS_VISIBLE | WS_CHILD,
		x0, y0, w, h, hW, (HMENU)ID, hInst, NULL);
}
//--------------------------------------------------------------
//���б༭��
HWND CreateEdit(char* Titel, int x0, int y0, int w, int h, int ID, HWND hW, HINSTANCE hInst)
{
	return CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", Titel,
		WS_VISIBLE | WS_CHILD |
		ES_LEFT | ES_MULTILINE | WS_HSCROLL,
		x0, y0, w, h, hW,
		(HMENU)ID, hInst, NULL);
}
//--------------------------------------------------------------
//�����ı���
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
//��ӿؼ��ı�
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
//	uint8_t data = 0;  //����һ��8λ�޷������Σ����ڴ������ַ���
//	uint8_t crc = 0;  //�����γ�ѭ������У����
//	uint8_t poly = 0x07;  // ʹ��CRC-8�����ɶ���ʽ
//
//	while (length--) { //��õ������ַ���
//		data = *(str++);
//		crc = crc ^ data;  //�ʼ��ʼ��crc=data��֮��
//
//		for (int i = 0; i < 8; i++) {
//			if (crc & 0x80) { //�����ǰcrc�����λ1����Ϊ���ɶ���ʽ���λΪ1����˿������ƺ������ɶ���ʽ��򣬼�����һ��
//				crc = (crc << 1) ^ poly;
//			}
//			else {
//				crc = crc << 1;  //��crc���λΪ0��ֱ������
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
//��ť
#define BUTTON1 501
#define BUTTON2 502
#define BUTTON3 503
//���б༭��
#define EDIT1 601
#define ANSWER 602
//�����ı���
#define MEMO1 801  //���յ�
#define MEMO2 802  //���͵�

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
#define Cs2Port 7777		//Զ�̶˿�
#define Cs1Port 6666		//���ض˿�
#define Cs1IP   "127.0.0.1"	//������ַ
#define Cs2IP   "127.0.0.1"	//Զ����ַ
//���ϲ���Ķ�!
//--------------------------------------------------------------
//����������ﶨ�����
int SendBufLeng;			//���ĳ���
int Sendi;					//����֡���ͼ���
BYTE mywlcSend(BYTE c);		//����㣺����һ���ֽ�
BYTE wlcRev();				//����㣺����һ���ֽ�
char SetCheck(char& c);     //żУ�飺��Է�������
//--------------------------------------------------------------
//��Ϣ����
LRESULT CALLBACK WndProc(HWND hW, UINT msg, WPARAM wP, LPARAM lP)
{
	const char* p = "���������뷢�͵���Ϣ";

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
		//		Cs1A.sin_addr.s_addr =INADDR_ANY;//�ڱ������õ���ַ(���ܶ��)�У�����Ч��
		Cs1A.sin_addr.s_addr = inet_addr(Cs1IP);
		d = bind(Cs1, (struct sockaddr*)&Cs1A, sizeof(Cs1A));
		if (d == -1)
		{
			MessageBox(0, "�˿ڷ�����ͻ", "�����ŵ�����", 0);
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
		CreateButton(const_cast <char*>("����У����"), 450, 20, 100, 60, BUTTON3, hW, hInst);
		//����㷢�͵���Ϣ��ʾ
		CreateWindow("STATIC", "���Ͷ�����㷢�͵���Ϣ",
			WS_VISIBLE | WS_CHILD,
			50, 100, 200, 20, hW, NULL, hInst, NULL);
		CreateMemo(const_cast <char*>(""), 50, 150, 200, 220, MEMO2, hW, hInst);
		CreateMemo(const_cast <char*>("У����"),500 , 90, 100, 220, ANSWER, hW, hInst);
		CreateWindow("STATIC", "���Ͷ��������յ���Ϣ",
			WS_VISIBLE | WS_CHILD,
			260, 100, 200, 20, hW, NULL, hInst, NULL);
		CreateMemo(const_cast<char*>(""), 260, 150, 200, 220, MEMO1, hW, hInst);
		
		
		break;
		//============================================================================
		//�����¼�������
		//������������д���룺
	case WM_USER + 1:
		switch (LOWORD(lP))
		{
		case FD_READ:
			bb[0] = wlcRev();					//����㣺����һ���ֽ�
			bb[1] = 0;
			char buf[22];
			
			wsprintf(buf, "%02XH,%c", (unsigned char)bb[0], bb[0]);
			Puts(hW, MEMO1, buf);				//��ʾ��������յ�����Ϣ
			//getsCrc(hW, ANSWER, buf1);
			//MessageBox(0,bb,"(FD_READ)",0);
			break;
		}
		break;
	case WM_COMMAND:
		switch (wP)
		{
		case BUTTON1:		
			
			
			// "Send" ��ť�¼�����	
			GetDlgItemText(hW, EDIT1, aa, sizeof(aa));		//�ӵ��б༭��õ�����
			
			char xx[20];
			
			SendBufLeng = strlen(aa);						//������ĳ���
			for (Sendi = 0; Sendi < SendBufLeng; Sendi++)		//���ͱ���
			{  
				
				aa[Sendi] = (aa[Sendi] & 0x0F) + x;			//��������ż���
				if (x != 0x70)x += 0x10;                    //������ű仯
				else x = 0x00;								//���ֻ����8�֣�����������
				mysend = SetCheck(aa[Sendi]);               //�������͵����ݽ���żУ�飬��������λ��У��λ
				mywlcSend(mysend);					//����㣺����һ���ֽ�
				wsprintf(xx, "%02XH", (unsigned char)mysend); //�����͵���Ϣ(ascii��)ת��Ϊʮ�����ƣ���ŵ�xx.��ϢĿǰֻ���ǵ��ֽڣ���
				Puts(hW, MEMO2, xx);						//��xx����MEMO2�У����ı�����ʾ��
			}
			break;

		case BUTTON2:									//�����Ϣ������
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
BYTE mywlcSend(BYTE c)	//����㣺����һ���ֽ�
{
	char a[2];
	a[0] = c; a[1] = 0;
	d = sizeof(Cs2A);
	sendto(Cs1, a, 1, 0, (struct sockaddr*)&Cs2A, d);
	return  c;
}
//--------------------------------------------------------------
BYTE wlcRev()			//����㣺����һ���ֽ�
{
	char b[1];
	d = sizeof(Cs2A);
	d = recvfrom(Cs1, b, 1, 0, (struct sockaddr*)&Cs2A, &d);
	return b[0];
}
char SetCheck(char& c) //CΪһ���ֽ�
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
