	/*
	��� ����� ���� ���۸� ����� �̿��Ͽ� ����ϸ�,
	�����, ����Ʈ���� PNG�������� ������ ����Ͽ� �۾����� ���̰�,
	�̿��� ��, ������ bmp�������� ����Ѵ�.
	*/
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <gdiplus.h> 
#include "resource.h"
#include "Mmsystem.h"
#include "Digitalv.h"
#include <string>

#pragma comment(lib,"User32.lib")
#pragma comment(lib, "gdiplus")
#pragma comment(lib,"msimg32.lib")
#pragma comment (lib,"winmm")
	using namespace std;
using namespace Gdiplus;

//Gdi+ ����� ���� �ʱ�ȭ
ULONG_PTR gpToken;  // �������� GdiplusShutdown���� ����ϹǷ� �����ʼ�.
GdiplusStartupInput gpsi;

#define random(n) (rand()%n); //���� ����
#define JUMPINGSEC 40
#define SLEEPTIME 200
#define UP 72
#define ESC 27
#define FIXWID 800 //����
#define FIXHID 750 //���� 
#define WIDTH 16
#define HIDTH 22
#define StartX 260
#define StartY 570
#define DASHTIME 50
#define SCTimer 100

DWORD wDeviceID = 0;
DWORD m_dwDeviceID;
MCI_OPEN_PARMS m_mciOpenParms;
MCI_PLAY_PARMS m_mciPlayParms;
MCI_OPEN_PARMS mciOpen;
MCI_PLAY_PARMS mciPlay;

int MinusScore; //���� ��
int PlusScore; //���� �� 
int Fy ; //���� ����
int score; //�⺻ ����
int Time2; //ĳ���� �̵��ӵ�
int Time1; //�� �������� �ӵ� (ms)
int Laser; //������ �ֱ�

int _Coin = 00001;

int COUNT = 0;
int ScoreSave;
int dwID;
int IsJump = 0;
int Chapter = 1, DashCount=  0;
int MaxClear = 24,Plusa=0,isDash=0;
int PointXY[48] = { 39,24 , 247,28 , 173,171 , 130,329 , 302,300 , 431,171 , 566,65 , 688,165 , 724,316  , 864, 203,  //1~10
884, 38, 1046, 100, 1093, 235, 1223, 326,  1372, 270, 1332, 120, 1473, 22, 1630, 78, 1644, 220, 1785, 318, //11~20
1908, 168, 2000, 40, 2149, 154, 2202, 319 }; //21~24
				   //�� ���������� �߾� ��ǥ���� ������ ���콺 Ŀ���� ��ġ�� �����Ͽ� ���Ѵ�. 
int ScoreArray[24] = { 10000,10000, };
int pat[7][32] = { //�� ����
	{ 0,0, 1,0, 2,0, -1,0, 0,0, 0,1, 0,-1, 0,-2, }, //|
	{ 0,0, 1,0, 0,1, 1,1, }, //��
	{ 0,0, -1,0, 0,-1, 1,-1,   -1,-1,0,0, 0,1, -1,0, }, // ����
	{ 0,0, -1,-1, 0,-1, 1,0,   0,0, -1,0, -1,1, 0,-1, }, //������
	{ 0,0, 0,-1, 1,0, 2,0,   0,0, -1,0 , 0,-1, 0,-2,   0,0, -1,0, -2,0, 0,1,   0,0, 1,0, 0,1, 0,2 },//|--
	{ 0,0, -1,0, -2,0, 0,-1,   0,0, -1,0, 0,1, 0,2,   0,0, 0,1, 1,0, 2,0,   0,0, 1,0, 0,-1, 0,-2 }, //--|
	{ 0,0, -1,0, 1,0, 0,1,   0,0 ,0,-1 ,0,1, 1,0,   0,0, -1,0, 1,0, 0,-1,   0,0 ,-1,0, 0,-1, 0,1 } // ��
};
int Sx = 0, Sy = 0, Inform = 0, _Option = 0, WL = 0, SendMsg = 0;
int status = 0, s = 16, SEC = 0, NowStg, SelectStg;
int Pix = 2 , Ex = 1 , Sec = 1, CantMove = 0;
int Second = 0, DownSecond = 0;
int L = 0, R = 0, Down = 0;
int brickpatnum[7] = { 2,1,2,2,4,4,4 };
int Rand = 0, MaxArray = 8;
int NRand = 0, NMaxArray = 0;
int IsRanded = 1, isWin = 0;
int islose = 0;

int Map[HIDTH][WIDTH];
//int x = 180 + 50, y = 60 + 50 ���� == 230, y = 110
int x = 260, y = 110, XOrig = x, YOrig = y;
int cx = 260, cy = 570; //ĳ���� ��ǥ
int Nx = 520, Ny = 50;
int NextColor = 0, NowColor = 0;
int IsFirst = 0;
int IsKeyDown = 0;
int DeleteLine;

LPCTSTR Win = TEXT("Ŭ����");
LPCTSTR End = TEXT("�й�");
POINT mouse;
HDC hdc, MemDC, NextBDC, hMemDC, BMemDC, OLMemDC, BackBufDC,OldDC, CopyDC, BlackDC, WhenRandDC,BUTDC, MultipleDC; //DC
HDC EffectDC, EffBlackDC, BGDC, MainDC, NextBackDC, CharDC, FinishDC, UiDC, StageMDC, ClearDC, TextDC, CopyClearDC;
HBITMAP MyBitmap, OldBitmap, BackBitmap, SaveBitmap, CopyBitMap, BlackBitmap, hEffBlack, BGBitmap, MainBitmap, UIBmp,ButtonBmp; //��Ʈ�� ���� �ڵ�
HBITMAP hBlock, hNextBlock, hBlock2, BackGround, hOlMem,hWhenR, hEffect, NextBackBitmap, CharBitmap ,BUT2DC,StageMBmp , CopyClearBmp; //�� �̹��� ���� �ڵ�
HBITMAP STARTBmp, FinishBmp, TextBmp, MultipleBitmap;
HWND hWnd, Button1,Lb,Rb;
HINSTANCE g_hInst;
BOOL Game_Start; //Game_Start = 0 -> ���� ������, 1 -> ���� 
static RECT rt = { 0,0,FIXWID,FIXHID };
static RECT Brt = { 50,50,470,650 };
DWORD Sound1, Sound2;
Image* Boss;
Image* image;
Image* WBimage;
Image* imgEffect;
Image* Score;
Image* Char;
Image* ScoreUI;
Image* GameOver;
Image* OverBlock;
Image* Stage;
Image* Coin;
Image* StgInform;
Image* Option;
Image* StageCircle;
Image* StageNum;
Image* HPLine;
Image* ClrEff;
Image* Result;

void _KillTimer();
void OPtion();
int WhatAround(int x);
void IsLose();
void RightNowSelec();
void Draw_Score(int x, int y, int what);
void CleanLine();
void Draw_AlphaBlock(HDC DC);
void SelectBlock();
int CheckCols();
void CleanAry();
void InsertAry();
void ChAnime(); //ĳ���� �ִϸ��̼� ���� �Լ� 
void Draw_Glass();
int RandColor();
void InitBoard();
void Draw_Block(int flag);
void DrawNextBlock();
void DrawScreen();
void leftmove();
void rightmove();
void downmove();
void rotate();
int isfull();
void PrintStage();
void WhereBlock();
void IsWin();
void FallDown_Block(int a);
void Dash();
void WhenChaDie();
void ActiveSleep(int Pix);
void Over_Block(int i);
void StageInform();
int WhatCircle(int x, int y); 
void LoadStageInform(int StgNum);
void PlayBGM();
void ClearEffect();
void GameOverEf();

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LPCTSTR lpszClass = TEXT("Tesya Alpha ver 0.1");

Image* LoadPNG(HMODULE hModule, LPCWSTR ResourceName) //PNG ������ ���ҽ� ���Ͽ��� �ε� �ϴ� Gdi �Լ� 
{
	//http://m.blog.naver.com/totoru1219/220702210611 �ڼ��� ���� ���� ��α� ����.

	Image* image = NULL;
	IStream* pStream = NULL;

	HRSRC hResource = FindResource(hModule, ResourceName, L"PNG"); //"PNG" ������ ������ ���ҽ����Ͽ��� ã�� �� hResource�� ��ȯ
	if (CreateStreamOnHGlobal(NULL, TRUE, &pStream) == S_OK) {
		PVOID pResourceData = LockResource(LoadResource(hModule, hResource));
		DWORD imageSize = SizeofResource(hModule, hResource);
		DWORD dwReadWrite = 0;
		pStream->Write(pResourceData, imageSize, &dwReadWrite);
		image = Image::FromStream(pStream);
		pStream->Release();
	}
	return image;
}

DWORD LoadWAV(HWND hWnd, LPCWSTR FileName, int sel)
{
	DWORD Result;

	if(sel == 1) //1�̸� wav
		m_mciOpenParms.lpstrDeviceType = L"WaveAudio";
	else //0�̸� mp3
		m_mciOpenParms.lpstrDeviceType = L"MPEGVideo";
	//WaveAudio ��� MPEGVideo�� ����ϸ� mp3 ������ ����մϴ�.

	m_mciOpenParms.lpstrElementName = FileName;

	Result = mciSendCommand(wDeviceID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&m_mciOpenParms);

	if (Result)
		return Result;

	wDeviceID = m_mciOpenParms.wDeviceID;

	m_mciPlayParms.dwCallback = (DWORD)hWnd;

	if (Result)
		return Result;

	return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	/*
	Token���ڴ� �������� �ڵ�� ������ GDI+�� ���̺귯�� Token. �� ���� GdiplusShutdown()�Լ��� ���ڷ� �̿��.
	Input���ڴ� �Է� �ɼ��� �����ϴ� GdiPlusStartupInput����ü�� �ּ�, ������ �ɼ��� ���ٸ� Default���� ������.
	Ouput�� �ʱ�ȭ ��� ��ȯ. NULL�̶�� ������� ����.
	*/
	if (GdiplusStartup(&gpToken, &gpsi, NULL) != Ok) { //Gdi+ �ʱ�ȭ
		MessageBox(NULL, TEXT("GDI+ ���̺귯�� �ʱ�ȭ �Ұ�."),
			TEXT("�˸�"), MB_OK);
		return 0;
	}

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(g_hInst, MAKEINTRESOURCE(IDC_CURSOR1));
	WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(
		lpszClass,
		lpszClass,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		FIXWID, //����
		FIXHID, //����
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	GdiplusShutdown(gpToken);
	return (int)Message.wParam;
}

////////////////// �޽��� ó�� ��ƾ///////////////// 

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC HMDC;
	LPDRAWITEMSTRUCT lpdis; //��ư DC ������ ������

	switch (iMessage) {
	case WM_CREATE: //������ ������ �޼��� 
		/****************�ʱ� �ʼ� ���� �ʱ�ȭ****************/
		srand(time(NULL));
		Rand = random(7);
		MaxArray = 8 * (rand() % brickpatnum[Rand] + 1);
		NRand = random(7);
		NMaxArray = 8 * (rand() % brickpatnum[NRand] + 1); //1~ NRand - 1 
		NowColor = RandColor();
		NextColor = RandColor();

		//////// DC �ʱ�ȭ /////////////
		hdc = GetDC(hWnd);
		MemDC = CreateCompatibleDC(hdc); //CreateCompatibleDC(����DC): ���� DC�� ������.
		hMemDC = CreateCompatibleDC(hdc);
		BMemDC = CreateCompatibleDC(hdc);
		OLMemDC = CreateCompatibleDC(hdc);
		BackBufDC = CreateCompatibleDC(hdc);
		NextBDC = CreateCompatibleDC(hdc);
		OldDC = CreateCompatibleDC(hdc);
		BlackDC = CreateCompatibleDC(hdc);
		WhenRandDC = CreateCompatibleDC(hdc);
		EffectDC = CreateCompatibleDC(hdc);
		CopyDC = CreateCompatibleDC(hdc);
		CopyClearDC = CreateCompatibleDC(hdc);
		EffBlackDC = CreateCompatibleDC(hdc);
		BGDC = CreateCompatibleDC(hdc);
		MainDC = CreateCompatibleDC(hdc);
		NextBackDC = CreateCompatibleDC(hdc);
		CharDC = CreateCompatibleDC(hdc);
		FinishDC = CreateCompatibleDC(hdc);
		UiDC = CreateCompatibleDC(hdc);
		BUTDC = CreateCompatibleDC(hdc);
		StageMDC = CreateCompatibleDC(hdc);
		ClearDC = CreateCompatibleDC(hdc);
		TextDC = CreateCompatibleDC(hdc);
		MultipleDC = CreateCompatibleDC(hdc);

		TextBmp = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP24)); //Text��Ʈ�� 
		SelectObject(TextDC, TextBmp);

		StageMBmp = CreateCompatibleBitmap(hdc, 2334, 435); //Stage��Ʈ��
		SelectObject(StageMDC, StageMBmp);
	
		CharBitmap = CreateCompatibleBitmap(hdc, 420, 60); //ĳ���� ��Ʈ��
		SelectObject(CharDC, CharBitmap);

		hEffect = CreateCompatibleBitmap(hdc, 420, 70); //����Ʈ �׷��� ��Ʈ�� 
		SelectObject(EffectDC, hEffect);

		UIBmp = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP20));
		SelectObject(UiDC, UIBmp);

		CopyClearBmp = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP23));
		SelectObject(CopyClearDC, CopyClearBmp);

		CopyBitMap = CreateCompatibleBitmap(hdc, FIXWID, FIXHID);
		SelectObject(CopyDC, CopyBitMap);
		OldBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP23));
		SelectObject(ClearDC, OldBitmap);

		SaveBitmap = CreateCompatibleBitmap(hdc, FIXWID, FIXHID);
		BackBitmap = CreateCompatibleBitmap(hdc, FIXWID, FIXHID);
		SelectObject(BackBufDC, BackBitmap);

		SelectObject(OldDC, SaveBitmap);
		FillRect(OldDC, &Brt, (HBRUSH)GetStockObject(WHITE_BRUSH));
		FillRect(BackBufDC, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH)); //��ȭ�� �� ����
		/////////////////////////////////////////

		////////// DC�� �ʱ� ��Ʈ�� ����/////////
		FinishBmp = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP19)); //��ǥ ���� 
		SelectObject(FinishDC, FinishBmp);
		NextBackBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP17));
		SelectObject(NextBackDC, NextBackBitmap);

		BGBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP15));

		/////////////////// PNG //////////////////////
		image = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG1)); //����� ��� �̹��� ���� (Gdi)
		WBimage = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG2)); //������ ��
		imgEffect = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG3)); //����Ʈ 
		Score = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG4)); //���� 0~9
		Char = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG5)); //ĳ���� ��������Ʈ ���� 
		GameOver = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG6)); //GameOver ����
		ScoreUI = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG7)); //Score ���� 
		OverBlock = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG8)); //���� ��
		Stage = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG9)); //�������� �� 
		Coin = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG10)); //����
		StgInform = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG11)); //�������� ����
		StageCircle = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG12));
		Option = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG13)); //�ɼ� â 
		StageNum = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG14)); //�������� ��ȣ
		HPLine = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG15));
		Boss = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG16));
		ClrEff = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG17));
		Result = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG18));
		//////////////////////////////////////////////

		hEffBlack = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP14));
		SelectObject(EffBlackDC, hEffBlack);

		///////// ���� ���� ��� ��Ʈ�� �ʱ� ���� ////////
		hNextBlock = LoadBitmap(g_hInst, MAKEINTRESOURCE(NextColor));
		SelectObject(NextBDC, hNextBlock);
		////////////////////////////////////////////////

		////////�� ó�� ���� ��� ��Ʈ�� �ʱ� ���� ////////
		hBlock = LoadBitmap(g_hInst, MAKEINTRESOURCE(NowColor)); //���� �̹��� ����
		SelectObject(hMemDC, hBlock); //hMemDC�� hBlock ��Ʈ�� ����
		///////////////////////////////////////////////////
		ButtonBmp = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP21));
		SelectObject(BUTDC, ButtonBmp);
		MainBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP16));
		SelectObject(MainDC, MainBitmap);
		BlackBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP12));
		SelectObject(BGDC, BGBitmap);
		SelectObject(BlackDC, BlackBitmap);
		BackGround = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP22)); //��� �̹��� ����
		SelectObject(BMemDC, BackGround);
		hOlMem = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP9)); //�ܰ��� �̹��� ���� 
		SelectObject(OLMemDC, hOlMem);
		////////////////////////////////////////

		/*********************** ���� ******************************/
		/* ��� ������ ����θ� �����Ͽ� �ٸ� ��ǻ�Ϳ����� ������ �ǵ��� �Ѵ�..
		ȿ������ PlaySound�� �̿��Ͽ� ����� �Ѵ�. */
		 //
		Sound1 = LoadWAV(hWnd, L"..\\Project______Resource\\����\\MainTitle_BGM.wav", 1); //���� BGM
		Sound1 = mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
		/***********************************************************/

		/********************** ��ư *******************************/
		
		STARTBmp = LoadBitmap((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDB_BITMAP18)); //START �̹���
		//SendMessage(Button1, BM_SETIMAGE, 0, (LPARAM)hEffect);
		Button1 = CreateWindow(TEXT("button"), //START ��ư
			TEXT("START"), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW|
			BS_PUSHBUTTON, 300, 400, 200, 80, hWnd, (HMENU)0,
			g_hInst, NULL);
		//SendMessage(Button1, BM_SETIMAGE, 0, (LPARAM)STARTBmp); //��ư �̹����� ��ư�� ����
		/*Button1 = CreateWindowEx(WS_EX_TRANSPARENT,TEXT("button"), //START ��ư
			TEXT("START"), WS_CHILD | WS_VISIBLE | BS_ICON | 
			BS_PUSHBUTTON , 300, 400, 200, 80, hWnd, (HMENU)0,
			g_hInst, NULL);
		SendMessage(Button1, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_ICON1))); //��ư �̹����� ��ư�� ����*/
		/************************************************************/
		BitBlt(CopyDC, 50, 50, 420, 600, CopyClearDC, 0, 0, SRCCOPY);//�ش� ��Ʈ���� ����� ��������μ� ������ ������
		TransparentBlt(CopyDC, 50, 50, 420, 600, CopyDC, 50, 50, 420, 600, RGB(0, 0, 0)); //�� ��� DC�� hdc�� ��� 
		InitBoard();
		isWin = 0;
		Game_Start = 0; //�ʱ�ȭ 0�� ������ 1�� ����

		break;
    case WM_DRAWITEM: //Owenr Draw�� ��ư�� �׷���. 
		lpdis = (LPDRAWITEMSTRUCT)lParam;
		HMDC = CreateCompatibleDC(lpdis->hDC);
		switch (lpdis->CtlID)
		{
		case 0:
			if (lpdis->itemState & ODS_SELECTED )
				SelectObject(HMDC, STARTBmp);
			else
				SelectObject(HMDC, STARTBmp);
			BitBlt(lpdis->hDC, 0, 0, 200, 80, HMDC, 0, 0, SRCCOPY);
			break;
		}
		DeleteDC(HMDC);
		return 0;
	case WM_COMMAND: //��ư �޼��� 
		switch (LOWORD(wParam))
		{
		case 0: //START ��ư ���� �� 
			mciSendCommand(1, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL); //����ȭ�� ��� ����
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //��ư Ŭ���� 
			Game_Start = 2;
			
			//PlaySound(NULL, 0, 0); //���带 �����մϴ�
			DestroyWindow(Button1);
			Sound2 = LoadWAV(hWnd, L"..\\Project______Resource\\����\\Digital_Solitude.mp3", 0); //�ܿ�� �׸� ��� 
			Sound2 = mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		return 0;

	case WM_LBUTTONDOWN: //��� Ŭ�� �̺�Ʈ�� ���� 
	{
		TCHAR text[100] = { 0 };
		GetCursorPos(&mouse); //Ŀ�� ��ǥ ������
		ScreenToClient(hWnd, &mouse); //Ŭ���̾�Ʈ(����â) ��ǥ�� ��ȯ
		COLORREF color = GetPixel(BackBufDC, mouse.x, mouse.y);
		int R, G, B;
		//wsprintf(text, L"x: %d y: %d", mouse.x + Plusa, mouse.y);

		R = G = B = 0;
		R = color & 0xFF;
		G = (color >> 8) & 0xFF;
		B = (color >> 16) & 0xFF;

		wsprintf(text, L"x: %d y: %d", mouse.x + Plusa, mouse.y - 120);
		//MessageBox(hWnd, text, (LPCWSTR)"as", MB_OK);
		if (Game_Start == 2)
			WhatCircle(mouse.x, mouse.y);
		//wsprintf(text, L"R: %d G: %d B: %d", R,G,B);
		//MessageBox(hWnd, text, (LPCWSTR)"as", MB_OK);

		if (R == 207 && G == 205 && B == 205 && mouse.x < 400) //���� �����ư
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //��ư Ŭ���� 
			if (Sx != -100)
				Sx -= 100;
			InvalidateRect(hWnd, NULL, FALSE);
		}
		else if (R == 207 && G == 205 && B == 205 && mouse.x > 400) //������ �����ư
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //��ư Ŭ���� 
			if (Sx != 1700)
				Sx += 100;
			InvalidateRect(hWnd, NULL, FALSE);
		}
		else if ( (R == 111 && G == 118 && B == 255) || (R == 218 && G == 220 && B == 255) ) //�ڷ� ����
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //��ư Ŭ���� 
			Game_Start = 0;
			InvalidateRect(hWnd, NULL, FALSE);

			Button1 = CreateWindow(TEXT("button"), //START ��ư
				TEXT("START"), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW |
				BS_PUSHBUTTON, 300, 400, 200, 80, hWnd, (HMENU)0,
				g_hInst, NULL);
		}
		else if ((R == 151 && G == 175 && B == 255) || (R == 95 && G == 83 && B == 255)) //����â 
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //��ư Ŭ���� 
			if (_Option == 1)
				_Option = 0;
			else
				_Option = 1;
			InvalidateRect(hWnd, NULL, FALSE);
		}
		else if (R == 119 && G == 199 && B == 84) //
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //��ư Ŭ���� 
			mciSendCommand(1, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL); //���� Ʋ�����ִ� ��� ����
			Sound1 = LoadWAV(hWnd, L"..\\Project______Resource\\����\\Digital_Solitude.mp3", 0); //�� ��� �ְ�
			Sound1 = mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay); //���
			Game_Start = 2;
			InvalidateRect(hWnd, NULL, FALSE);
		}
		else if (R == 255 && G == 122 && B == 122) //���� ��ư
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //��ư Ŭ���� 
			PlayBGM();
			Inform = 0;
			Game_Start = 1;
			InvalidateRect(hWnd, NULL, FALSE);
			SetTimer(hWnd, 10, SCTimer, NULL); //���� ���ھ�
			SetTimer(hWnd, 1, Time1, NULL);
			SetTimer(hWnd, 6, Time2, NULL);
		}
		else if (R == 182 && G == 36 && B == 12)
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //��ư Ŭ���� 
			Inform = 0;
			InvalidateRect(hWnd, NULL, FALSE);
		}
		else if (mouse.x >= 520 && mouse.x <= 720 && mouse.y >= 450 && mouse.y <= 530 && Game_Start == 1) //520, 450  // 520, 550 //RETRY
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //��ư Ŭ���� 
			BitBlt(CopyDC, 50, 50, 420, 600, BMemDC, 420 * (Chapter - 1), 0, SRCCOPY);//�ش� ��Ʈ���� ����� ��������μ� ������ ������
			cx = StartX; cy = StartY; //ĳ���� ��ġ�� �ٽ� ���������� ���� 
			score = ScoreSave;

			InitBoard(); //�� �� �ʱ�ȭ
			KillTimer(hWnd, 10);
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 6); //230 110

			XOrig = 230;
			YOrig = 110;

			InvalidateRect(hWnd, NULL, FALSE);
			SetTimer(hWnd, 1, Time1, NULL);
			SetTimer(hWnd, 6, Time2, NULL);
			SetTimer(hWnd, 10, SCTimer, NULL);
		}
		else if (mouse.x >= 520 && mouse.x <= 720 && mouse.y >= 550 && mouse.y <= 630 && Game_Start == 1) //OPTION
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //��ư Ŭ����
		}
		return 0;
	}

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			if (isWin == 0)
			{
				if ((WhatAround(-1) == 0 || WhatAround(-1) == 1) && Game_Start == 1)
					leftmove();
				else
				{
					if (Sx != -100 && Game_Start == 2)
					{
						PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //��ư Ŭ����
						Sx -= 100;
						Plusa -= 100;
						InvalidateRect(hWnd, NULL, FALSE);
					}
				}
			}
			break;
		case VK_RIGHT:
			if (isWin == 0)
			{
				if ((WhatAround(1) == 0 || WhatAround(1) == 1) && Game_Start == 1)
					rightmove();
				else
				{
					if (Sx != 1700 && Game_Start == 2)
					{
						PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //��ư Ŭ���� 
						Sx += 100;
						Plusa += 100;
						InvalidateRect(hWnd, NULL, FALSE);
					}
				}
			}

			break;
		case VK_UP: 
			if (isWin == 0)
			rotate();
			break;
		case VK_DOWN:
			if (IsKeyDown != 1 && isWin == 0)
			{
				SetTimer(hWnd, 4, 100, NULL);
				IsKeyDown = 1;
			}
			break;
		case VK_SPACE:
			if (Game_Start == 1 && isWin == 0)
			{
				KillTimer(hWnd, 1);
				RightNowSelec(); //��� ��ġ 
			}
			break;
		case 0x44: //DŰ �뽬�� ��ü  
			if (isDash == 0 && isWin==0)
			{
				KillTimer(hWnd, 6);
				SetTimer(hWnd, 9, DASHTIME, NULL);
			}
			break;

		case 0x46: //FŰ Active
			if (isWin == 0)
			{
				KillTimer(hWnd, 6);
				SetTimer(hWnd, 7, SLEEPTIME, NULL);
			}
			break;
		}

		break;
	case WM_KEYUP: //DŰ�� ĳ���� ����Ű 
		switch (wParam)
		{
		case VK_DOWN:
			if (IsKeyDown != 0)
				IsKeyDown = 0;
			KillTimer(hWnd, 4);
			if (CheckCols() != 1 && DownSecond >= 3)
			{
				KillTimer(hWnd, 2);
				SetTimer(hWnd, 1, Time1, NULL);
				DownSecond = 0;
			}
			break;
		}
		break;

	case WM_TIMER: //800ms 
		switch (wParam)
		{
		case 1:
			if (Game_Start == 1)
			{
				if (CheckCols() == 1) //�� �浹 ������ 
				{
					SetTimer(hWnd, 3, 120, NULL);
				}
				else
				{
					Draw_Block(0);
					downmove();
					CheckCols();
				}
			}
			break;

		case 2:
			if (Game_Start == 1)
			{
				if (CheckCols() != 1)
				{
					downmove();
					CheckCols();
				}
			}
			break;

		case 3:
			if (Game_Start == 1)
			{
				if (CheckCols() != 1)
				{
					Second = 0;
					KillTimer(hWnd, 3);
				}
				else
				{
					if (Second < 4)
					{
						CheckCols();
						Second++;
					}
					else
					{
						//KillTimer(hWnd, 3);
						SelectBlock();
						IsLose();
						BitBlt(OldDC, 50, 50, 420, 600, BackBufDC, 50, 50, SRCCOPY);
						for (int i = 0; i < 10; i++)
							isfull();
						x = 230; y = 110;
						XOrig = x; YOrig = y;

						///////////// �� ���� �ʱ�ȭ////////////////
						Rand = NRand;
						MaxArray = NMaxArray;
						NRand = random(7);
						NMaxArray = 8 * (rand() % brickpatnum[NRand] + 1);

						NowColor = NextColor;
						NextColor = RandColor();
						hNextBlock = LoadBitmap(g_hInst, MAKEINTRESOURCE(NextColor));
						SelectObject(NextBDC, hNextBlock);
						hBlock = LoadBitmap(g_hInst, MAKEINTRESOURCE(NowColor));
						SelectObject(hMemDC, hBlock);
						//////////////////////////////////////////////

						DrawNextBlock();
						Second = 0;
						CantMove = 0;
						Down = 0;
						KillTimer(hWnd, 3);
					}
				}
			}
			break;

		case 4: //DownŰ Ÿ�̸� 
			if (Game_Start == 1)
			{
				DownSecond++;
				if (DownSecond >= 3)
				{
					KillTimer(hWnd, 1);
					SetTimer(hWnd, 2, Time2, NULL);
					KillTimer(hWnd, 4);
				}
			}
			break;
		case 5: //�� ���� �ִϸ��̼� //460 * (Ex - 1)
		{
			if (Ex == 1)
				PlaySound(MAKEINTRESOURCE(IDR_WAVE6), NULL, SND_RESOURCE | SND_ASYNC); //������
			Graphics Exp(EffectDC);
			BitBlt(EffectDC, 0, 0, 420, 70, EffBlackDC, 0, 0, SRCCOPY); //����Ʈ DC ��������
			Exp.DrawImage(imgEffect, (30 * Ex) + Sec, 0, 460 * (Ex - 1), 0, 200, 70, UnitPixel);
			InvalidateRect(hWnd, NULL, FALSE);
			Sec += 15;
			Ex++;

			if (Ex == 10)
			{
				KillTimer(hWnd, 5);
				Ex = 1;
				Sec = 0;
			}
		}
		break;

		case 6: //ĳ���� �ִϸ��̼�  0= �����, 1= �̵����� �� 2= ��ġ�� �� 3 = ��
			//cx = 260, cy = 570; //ĳ���� ��ǥ

			//�� ���� �˻� ����
			if (cx % 30 == 15)
			{
				FallDown_Block(cx + 15);
				FallDown_Block(cx - 15);
			}
			else
				FallDown_Block(cx);
			//////////////////////

			IsWin();
			if ( (Map[cy / 30][(cx - 35) / 30] == 1 || Map[cy / 30][(cx-35) / 30] == 2 || Map[cy / 30][(cx-35) / 30] == 3) && status == 0)
			{
				status = 1;
				Pix = 5;
			}
			else if ( (Map[cy / 30][(cx - 50 + 75) / 30] == 1 || Map[cy / 30][(cx - 50 + 75) / 30] == 2 || Map[cy / 30][(cx - 50 + 75) / 30] == 3)  && status == 1)
			{
				status = 0;
				Pix = 1;
			}
			
			if (status == 0) //status 0�Ͻ� <-
			{
				cx -= 15;
				if (Map[(cy + 60) / 30][cx / 30] == 0 && Map[(cy + 90) / 30][cx / 30] == 0 
					&& Map[(cy + 120) / 30][cx / 30] == 0 && Map[(cy + 150) / 30][cx / 30] == 0) //4ĭ �̻�� ���� 
				{
					cy += 60;
					islose = 1;
				}
				else if (Map[(cy + 30) / 30][cx / 30] != 0) //��� ����
						cy -= 30;
				else if (Map[(cy + 60) / 30][cx / 30] == 0)
						cy += 30;

				if (Pix != 4)
					Pix++;
				else
					Pix = 1;
			}
			else //1�Ͻ� ->
			{
				cx += 15;
				if (Map[(cy + 60) / 30][(cx) / 30] == 0 && Map[(cy + 90) / 30][(cx) / 30] == 0
					&& Map[(cy + 120) / 30][(cx) / 30] == 0 && Map[(cy + 150) / 30][(cx) / 30] == 0) //4ĭ �̻� �� ���� 
				{
					cy += 120;
					islose = 1;
				}
				else if (Map[(cy + 30) / 30][(cx + 15) / 30] != 0) //��� ����
						cy -= 30;
				else if (Map[(cy + 60) / 30][(cx) / 30] == 0)
						cy += 30;


				if (Pix != 8)
					Pix++;
				else
					Pix = 5;
			}

			if (cx % 30 == 15)
				FallDown_Block(cx - 15);
			else
				FallDown_Block(cx);

			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case 7: //FŰ ��� (3�ʰ� ����)
			if (s == 16)
				KillTimer(hWnd, 6); //ĳ���� �̵� Ÿ�̸� ��� ����
			SEC++;

			InvalidateRect(hWnd, NULL, FALSE);
			if (s != 14)
				s++;
			if (s == 18)
				s = 13;

			if (SEC == 15 )
			{
				s = 16;
				SEC = 0;
				SetTimer(hWnd, 6, Time2, NULL);
				KillTimer(hWnd, 7);
			}
			break;
		case 8: //���� ������ �������� ����ִ� Ÿ�̸� 
			WL++;
			InvalidateRect(hWnd, NULL, FALSE);
			if (WL == HIDTH - 2)
			{
				COUNT = 2;
				SetTimer(hWnd, 12, 80, NULL);
				KillTimer(hWnd, 8);
				WL = 0;
				InvalidateRect(hWnd, NULL, FALSE);
			}
			break;
		case 9: //ĳ���� ��� //cx = 260, cy = 570; //ĳ���� ��ǥ 1~20 
			Dash();
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case 10:
			score -= MinusScore; //���� ���� 
			IsLose();
			break;
		case 11:
			//ClearEffect();
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case 12:
			GameOverEf();
			break;
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		if (Game_Start == 2)//�������� â 
		{
			PrintStage();
			if (Inform == 1)
				StageInform();
			if (_Option == 1)
				OPtion();
			BitBlt(hdc, 0, 0, FIXWID, FIXHID, BackBufDC, 0, 0, SRCCOPY); //BackBufDC�� ȭ������ ������ ���
			isWin = 0;
		}
		else if (Game_Start == 1)
		{
			Graphics UK(BackBufDC);
			DrawScreen(); //����� ������ ��� ȭ�� ���
			Draw_Block(1); //��� ��� 1 = ��� & 0 = ���� ��� 
			TransparentBlt(BackBufDC, 50, 50, 420, 600, CopyDC, 50, 50, 420, 600, RGB(255, 255, 255)); //�� ��� DC�� hdc�� ��� 
			Draw_AlphaBlock(BackBufDC); //����� �� ��� 
			UK.DrawImage(HPLine, 50, Fy, 0, 45, 315, 45, UnitPixel); //������ ��
			WhereBlock(); //������ ���
			TransparentBlt(BackBufDC, 50, DeleteLine * 30 - 10, 420, 70, EffectDC, 0, 0, 420, 70, RGB(0, 0, 0)); //����Ʈ ���
			
			if (isWin == 1)
			{
				ClearEffect();
				BitBlt(hdc, 0, 0, FIXWID, FIXHID, BackBufDC, 0, 0, SRCCOPY); //BackBufDC�� ȭ������ ������ ��� 
			}
			if (isDash == 1)
			{
				if(DashCount != 4)//540  600 
					UK.DrawImage(Char, cx, cy, 540 + (status * 2 * 60), 0, 60, 60, UnitPixel);
				else
					UK.DrawImage(Char, cx, cy, 600 + (status * 2 * 60), 0, 60, 60, UnitPixel);
			}
			else if (SEC != 0 && islose != 1 && isDash == 0) //�ڴ°Ÿ� 
				ActiveSleep(s);
			else if (islose != 1 && SEC == 0 && isDash == 0 && isWin == 0) //�й谡 �ƴҽ� ��� �̵� 
				ChAnime();
			else if (islose == 1) //����� ��� �ִϸ��̼� 
			{
				if (COUNT == 0)
				{
					_KillTimer();
					SetTimer(hWnd, 8, 50, FALSE);
					COUNT=1;
				}
				else if (COUNT == 2)
				{
					GameOverEf();
					BitBlt(hdc, 0, 0, FIXWID, FIXHID, BackBufDC, 0, 0, SRCCOPY); //BackBufDC�� ȭ������ ������ ���
				}

				Over_Block(WL);
				WhenChaDie();
			}
			BitBlt(hdc, 0, 0, FIXWID, FIXHID, BackBufDC, 0, 0, SRCCOPY); //BackBufDC�� ȭ������ ������ ��� 
		}
		else if(Game_Start == 0) //����
		{
			BitBlt(hdc, 0, 0, FIXWID, FIXHID, MainDC, 0, 0, SRCCOPY); //���� ȭ�� ��� 
		}
		EndPaint(hWnd, &ps);
		break;

	case WM_CLOSE: //�й� ��
		_KillTimer();
		if (islose == 1)
		{
			//SetTimer(hWnd, 8, 25, NULL);
			SendMsg = 1;
			if (MessageBox(hWnd, End, TEXT("Close"), MB_OK) == IDYES && WL == HIDTH - 2)
				DestroyWindow(hWnd);
		}
		if (isWin == 1)
		{
			if(MessageBox(hWnd, Win, TEXT("Close"), MB_OK) == IDYES)
				DestroyWindow(hWnd);
		}

	case WM_DESTROY:
		if (image != NULL) //GDI+ ��ü ���� 
		{
			delete imgEffect;
			delete WBimage;
			delete image;
			delete Score;
			delete Char;
			delete ScoreUI;
			delete GameOver;
			delete OverBlock;
			delete Stage;
			delete Coin;
			delete StgInform;
			delete Option;
			delete StageNum;
			delete HPLine;
			delete Boss;
			delete ClrEff;
		}
		ReleaseDC(hWnd, hdc); //DC ���� 
		mciSendCommand(1, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
		mciSendCommand(2, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
		DeleteDC(NextBDC);
		DeleteDC(BackBufDC);
		DeleteDC(MemDC);
		DeleteDC(hMemDC);
		DeleteDC(BMemDC);
		DeleteDC(OLMemDC);
		DeleteDC(OldDC);
		DeleteDC(CopyDC);
		DeleteDC(BlackDC);
		DeleteDC(WhenRandDC);
		DeleteDC(EffectDC);
		DeleteDC(EffBlackDC);
		DeleteDC(BGDC);
		DeleteDC(MainDC);
		DeleteDC(NextBackDC);
		DeleteDC(CharDC);
		DeleteDC(FinishDC);
		DeleteDC(UiDC);
		DeleteDC(BUTDC);
		DeleteDC(StageMDC);
		DeleteDC(ClearDC);
		DeleteDC(TextDC);
		DeleteDC(CopyClearDC);
		DeleteDC(MultipleDC);
		//DeleteDC(BDC);
		
		DeleteObject(MultipleBitmap);
		DeleteObject(CopyClearBmp);
		DeleteObject(TextBmp);
		DeleteObject(StageCircle);
		DeleteObject(StageMBmp);
		DeleteObject(ButtonBmp);
		DeleteObject(UIBmp);
		DeleteObject(FinishBmp);
		DeleteObject(CharBitmap);
		DeleteObject(hEffect);
		DeleteObject(hWhenR);
		DeleteObject(BlackBitmap);
		DeleteObject(CopyBitMap);
		DeleteObject(SelectObject(BackBufDC, OldBitmap));
		DeleteObject(SaveBitmap);
		DeleteObject(hBlock);
		DeleteObject(hBlock2);
		DeleteObject(BackGround);
		DeleteObject(hOlMem);
		DeleteObject(hNextBlock);
		DeleteObject(BackBitmap);
		DeleteObject(OldBitmap);
		DeleteObject(MyBitmap);
		DeleteObject(hEffBlack);
		DeleteObject(BGBitmap);
		DeleteObject(MainBitmap);
		DeleteObject(NextBackBitmap);
		DeleteObject(STARTBmp);

		PostQuitMessage(0);
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void PrintStage() //�������� â������ UI 
{ 
	int CicleX=0;
	static int O = 0;
	//�ڷ� / ���� / ����UI 
	Graphics STAGE(StageMDC);
	Graphics COIN(BackBufDC);

	BitBlt(BackBufDC, 0, 0, 800, 750, BGDC, 0, 0, SRCCOPY); //�޹��

	////////////////////////�������� ��///////////////////////////////////////////
	if (O == 0)
	{
		STAGE.DrawImage(Stage, 0, 0, 0, 0, 1750, 325, UnitPixel); //�������� �� StageMDC�� ��� 
		STAGE.DrawImage(Stage, 0, 0, 0, 0, 1750, 325, UnitPixel);
		STAGE.DrawImage(Stage, 0, 0, 0, 0, 1750, 325, UnitPixel);
		O++;
	}
		STAGE.DrawImage(Stage, 0, 0, 0, 0, 1750, 325, UnitPixel);
	for (int i = 0; i < MaxClear * 2; i+=2) //�������� ��Ŭ ��� 
	{
		int j;
		if (i == 4 || i == 16 || i == 28 || i == 40) //�߰����� ��������
			CicleX = 120;
		else if (i == 10 || i == 22 || i == 34 || i == 46) //���� �������� 
			CicleX = 60;
		else //�̿� �������� 
			CicleX = 0;
		STAGE.DrawImage(StageCircle, PointXY[i], PointXY[i+1], CicleX, 0,60,60,UnitPixel); //�������� ��ư �� �׷��ֱ� 

		j = i / 2 + 1;
		if(j < 10)
			STAGE.DrawImage(StageNum, PointXY[i] + 31, PointXY[i + 1] + 30, j * 15, 0, 15, 18, UnitPixel);//��ȣ �׸��� 
		else
		{
			int t = j / 10, o = j % 10; //���� �ڸ� ���� �ڸ�
			STAGE.DrawImage(StageNum, PointXY[i] + 25, PointXY[i + 1] + 30, t * 15, 0, 15, 18, UnitPixel);//��ȣ �׸���
			STAGE.DrawImage(StageNum, PointXY[i] + 40, PointXY[i + 1] + 30, o * 15, 0, 15, 18, UnitPixel);//��ȣ �׸���
		}
	} //��ư ���� ���

	BitBlt(BackBufDC, 0, 120, 800, 435, StageMDC, Sx, Sy, SRCCOPY); //�� �׷��� ������������ �� ���ۿ� ���� 
	//////////////////////////////////////////////////////////////////////////////

	BitBlt(BackBufDC, 20, 30, 40, 40, BUTDC, 60, 0, SRCCOPY); //�ڷΰ��� 
	BitBlt(BackBufDC, 70, 30, 40, 40, BUTDC, 120, 0, SRCCOPY); //����
	COIN.DrawImage(Coin, 530, 30, 240, 60); //���� BackBufDC�� ��� 
	Draw_Score(590, 35, _Coin);
	TransparentBlt(BackBufDC, 10, 300, 30, 60, BUTDC, 240, 0, 29, 60,RGB(64,0,64)); //�� ��ư
	TransparentBlt(BackBufDC, 730, 300, 30, 60, BUTDC, 270, 0, 30, 60, RGB(64, 0, 64)); //���� ��ư
}

void RightNowSelec() //��� ��ġ �Լ�
{
	PlaySound(MAKEINTRESOURCE(IDR_WAVE3), NULL, SND_RESOURCE | SND_ASYNC); //������ 
	int C=0;
	Draw_Block(0);
	for (int i = 0; i < HIDTH; i++)
	{
		if (CheckCols() != 1)
		{
			CleanAry();
			YOrig += 30;
			InsertAry();
		}
		else
		{
			if (cx % 30 == 15 && islose == 0)
			{
				FallDown_Block(cx + 15);
				FallDown_Block(cx - 15);
			}
			else if (islose == 0)
			{
				FallDown_Block(cx);
			}
			InvalidateRect(hWnd, NULL, FALSE);
			Draw_Block(1);
			SelectBlock();
			IsLose();
			BitBlt(OldDC, 50, 50, 420, 600, BackBufDC, 50, 50, SRCCOPY);
			for (int i = 0; i < 10; i++)
				isfull();
			x = 230; y = 110;
			XOrig = x; YOrig = y;

			///////////// �� ���� �ʱ�ȭ////////////////
			Rand = NRand;
			MaxArray = NMaxArray;
			NRand = random(7);
			NMaxArray = 8 * (rand() % brickpatnum[NRand] + 1);

			NowColor = NextColor;
			NextColor = RandColor();
			hNextBlock = LoadBitmap(g_hInst, MAKEINTRESOURCE(NextColor));
			SelectObject(NextBDC, hNextBlock);
			hBlock = LoadBitmap(g_hInst, MAKEINTRESOURCE(NowColor));
			SelectObject(hMemDC, hBlock);
			//////////////////////////////////////////////

			CantMove = 0;
			Down = 0;
			break;
		}
	}
	SetTimer(hWnd, 1, Time1, NULL);
}

void WhereBlock() //������ ��
{
	Graphics WB(BackBufDC);
	int k = 0;
	int yorig = YOrig;
	int x, y;
	int X, Y;

	while (k != 1)
	{
		for (int i = MaxArray - 8; i < MaxArray; i += 2)
		{
			X = XOrig - 50;
			Y = yorig - 50;
			X += (pat[Rand][i] * 30);
			Y += (pat[Rand][i + 1] * 30);
			X = (X / 30) + 1;
			Y = (Y / 30) + 1;
			if (Map[Y + 1][X] == 3 || Map[Y + 1][X] == 2)
			{
				k = 1;
				break;
			}
		}
		if (k == 1)
		{
			for (int j = MaxArray - 8; j < MaxArray; j += 2)
			{
				x = XOrig;
				y = yorig;
				x += (pat[Rand][j] * 30);
				y += (pat[Rand][j + 1] * 30);
				WB.DrawImage(WBimage, x + 2, y + 2, (NowColor - 122) * 20, 0, 20, 20, UnitPixel); //http://www.soen.kr/lecture/library/gdiplus/old/5-2.htm
			}
			break;
		}
		else
			yorig += 30;
	}
}

void Draw_Glass()
{
	Graphics Glass(BackBufDC);
	for (int i = 1; i < HIDTH - 1; i++)
	{
		for (int j = 1; j < WIDTH - 1; j++)
		{
			if (Map[i][j] == 0)
				Glass.DrawImage(image, j * 30 + 50, i * 30 + 50, 30, 30);
		}
	}
}

void DrawScreen() //���, UI���� ��� ��� 
{
	Graphics UI(BackBufDC);
	
	BitBlt(BackBufDC, 0, 0, 800, 750, BGDC, 0, 0, SRCCOPY); //�޹��
	BitBlt(BackBufDC, 40, 40, 440, 620, OLMemDC, 0, 0, SRCCOPY); //�ܰ��� 
	BitBlt(BackBufDC, 500, 41, 240, 240, NextBackDC, 0, 0, SRCCOPY);  //�̸�����â
	BitBlt(BackBufDC, 50, 50, 420, 600, BMemDC, 420*(Chapter-1), 0, SRCCOPY);//��Ʈ���� ��� 
	DrawNextBlock(); //���� ��
	BitBlt(BackBufDC, 500, 300, 240, 360, UiDC, 0, 0,SRCCOPY); //�����ϴ� UI
	UI.DrawImage(ScoreUI, 580, 320, 96, 34); //Score ���� ��� 
	BitBlt(BackBufDC, 520, 450, 200, 80, TextDC, 200, 0, SRCCOPY); //RETRY 
	BitBlt(BackBufDC, 520, 550, 200, 80, TextDC, 600, 0, SRCCOPY); //OPTION
	Draw_Score(540, 370, score); //���� ���
}

void DrawNextBlock() //���� ���� �� ��� 
{
	int X = 615, Y = 165;
	//hNextBlock = LoadBitmap(g_hInst, MAKEINTRESOURCE(RandColor()) ); //

	for (int i = NMaxArray - 8; i < NMaxArray; i += 2)
	{
		X += (pat[NRand][i] * 30);
		Y += (pat[NRand][i + 1] * 30);
		BitBlt(BackBufDC, X, Y, 30, 30, NextBDC, 0, 0, SRCCOPY);
		X = 615;
		Y = 165;
	}
}

void InitBoard() //�迭 �ʱ�ȭ 0 = ����� 1 = �� 
{
	for (int i = 0; i < HIDTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (i == 0 || i == HIDTH - 1 || j == 0 || j == WIDTH - 1)
				Map[i][j] = 3;
			else
				Map[i][j] = 0;
		}
	}
}

void Draw_Block(int flag) //�� ��� �Լ�  // brickpatnum[7] = { 2,1,2,2,4,4,4 };
{
	//testArray();
	HDC B;
	B = GetDC(hWnd);

	if (flag == 1) //1�̸� ���� 0�̸� ���� 
	{
		B = hMemDC;
		for (int i = MaxArray - 8; i < MaxArray; i += 2)
		{
			x = XOrig;
			y = YOrig;
			x += (pat[Rand][i] * 30);
			y += (pat[Rand][i + 1] * 30);
			CheckCols();
			BitBlt(CopyDC, x, y, 30, 30, B, 0, 0, SRCCOPY);
		}
	}
	else
	{
		B = BlackDC;
		for (int i = MaxArray - 8; i < MaxArray; i += 2)
		{
			x = XOrig;
			y = YOrig;
			x += (pat[Rand][i] * 30);
			y += (pat[Rand][i + 1] * 30);
			BitBlt(CopyDC, x, y, 30, 30, B, 0, 0, SRCCOPY);
		}
	}

}

void Draw_AlphaBlock(HDC DC) //�� ��ü�� ������� ����ش�. 
{
	x = 20; y = 50;
	Graphics g(DC); //Gdi Graphic ��ü g ������ dc �ʱ�ȭ
						   /*Bitmap *pBitmap = image; //����� �̹��� �����Դϴ�
						   Bitmap memBitmap(pBitmap->Width(), pBitmap->Height()); //������ �̹����� ũ�⸸ŭ Bitmap ������ �ϳ� ����ϴ�.
						   Graphics memG(&memBitmap); //�޸𸮿� �׷��� Graphics�����Դϴ�.*/

	for (int j = 0; j < 20; j++)
	{
		for (int i = 0; i < 14; i++)
		{
			x += 30;
			g.DrawImage(image, x, y, 30, 30);
		}
		y += 30;
		x = 20;
	}
	x = 230; y = 110;
}

int CheckCols() //0 = �浹X 1 = �浹o 
{
	for (int i = HIDTH - 1; i > 0; i--)
	{

		for (int j = WIDTH - 1; j >= 0; j--)
		{
			if (Map[i][j] == 3 || Map[i][j] == 2) //���̰ų� ��ġ�� ���̸�
			{
				if (Map[i - 1][j] == 1)
				{
					Down = 1;
					return Down;
				}
				else
				{
					Down = 0;
				}
			}

		}
		if (Down == 1)
			break;
	}

	return Down;
}

int RandColor()
{
	return  (rand() % 7 + 122); //resource.h�� ���ҽ� ��ȣ�� ���� ����. 122~128 ��
}

void downmove() //WM_TIMER�� timer �ֱ�� ����� 1ĭ�� ������.
{
	Draw_Block(0);
	InvalidateRect(hWnd, NULL, FALSE);
	CleanAry();
	YOrig += 30;
	InsertAry();
	CheckCols();
	Draw_Block(1);
}

void leftmove() //�������� �̵�.
{
	Draw_Block(0);
	InvalidateRect(hWnd, NULL, FALSE);
	CleanAry();
	XOrig -= 30;
	InsertAry();
	//CheckCols();
	Draw_Block(1);
	//testArray();
}

void rightmove() //���������� �̵�.
{
	Draw_Block(0);
	InvalidateRect(hWnd, NULL, FALSE);
	CleanAry();
	XOrig += 30;
	InsertAry();
	//CheckCols();
	Draw_Block(1);
	//testArray();
}

void CleanAry() //�迭�� ������ִ� �̵����� ������ �����ش�.
{
	int X, Y;

	for (int i = MaxArray - 8; i < MaxArray; i += 2)
	{
		X = XOrig - 50;
		Y = YOrig - 50;
		X += (pat[Rand][i] * 30);
		Y += (pat[Rand][i + 1] * 30);
		X = X / 30 + 1;
		Y = Y / 30 + 1;
		Map[Y][X] = 0;

	}
}

void SelectBlock() //�غκ��� ������ 2�̴� ���� 3�� �ٲ�� ������.
{
	int X, Y;
	CantMove = 1;
	for (int i = MaxArray - 8; i < MaxArray; i += 2)
	{
		X = XOrig - 50;
		Y = YOrig - 50;
		X += (pat[Rand][i] * 30);
		Y += (pat[Rand][i + 1] * 30);
		X = (X / 30) + 1;
		Y = (Y / 30) + 1;
		Map[Y][X] = 2;
	}
}

void InsertAry() //��ϰ��� 1���� �ʱ�ȭ �Ͽ� �̵������� ��Ÿ����.
{
	int X, Y;
	for (int i = MaxArray - 8; i < MaxArray; i += 2)
	{
		X = XOrig - 50;
		Y = YOrig - 50;
		X += (pat[Rand][i] * 30);
		Y += (pat[Rand][i + 1] * 30);
		X = (X / 30) + 1;
		Y = (Y / 30) + 1;
		Map[Y][X] = 1;
	}
}

void rotate() //�� ȸ�� �Լ� 
{
	if ((WhatAround(1) == 0 || WhatAround(1) == 1) && (WhatAround(-1) == 0 || WhatAround(-1) == 1) && Down != 1)
	{
		Draw_Block(0);
		InvalidateRect(hWnd, NULL, FALSE);

		CleanAry();

		if (MaxArray / 8 == brickpatnum[Rand])
			MaxArray = 8;
		else
			MaxArray += 8;

		InsertAry();
		Draw_Block(1);

	}
}

int isfull() //1ĭ�� �� á���� �����.
{
	int i, j;
	int Count = 0;

	for (i = 1; i < HIDTH - 1; i++)
	{
		for (j = 1; j < WIDTH - 1; j++)
		{
			if (Map[i][j] == 2)
				Count++;
		}
		if (Count == 14)
		{
			DeleteLine = i;
			CleanLine();
		}
		else
			Count = 0;
	}
	return Count;
}

void CleanLine() //���� �� ä���� ���� ������, �������ŭ �� ������ ������ �����ش�.
{
	SetTimer(hWnd, 5, 60, NULL); //���� ����Ʈ Ÿ�̸� 
	score += PlusScore;
	for (int j = 1; j < WIDTH - 1; j++)
	{
		Map[DeleteLine][j] = 0;
	}

	for (int m = DeleteLine; m > 1; m--) //HIDTH 22 
	{
		for (int n = 1; n < WIDTH - 1; n++)
		{
			BitBlt(CopyDC, n * 30 + 20, m * 30 + 20, 30, 30, CopyDC, n * 30 + 20, (m - 1) * 30 + 20, SRCCOPY);
			Map[m][n] = Map[m - 1][n];
		}
	}

	for (int k = 1; k < WIDTH - 1; k++)
		Map[1][k] = 0;
}

void IsLose() //�й� ó�� 
{
	for (int i = 1; i < WIDTH - 2; i++)
	{
		if (Map[3][i] == 2 || score == 0)
		{
			_KillTimer();
			islose = 1;
			InvalidateRect(hWnd, NULL, FALSE);

			break;
		}
	}
}

int WhatAround(int x)
{
	int j, k = 0;
	int X, Y;
	for (int i = MaxArray - 8; i < MaxArray; i += 2)
	{
		X = XOrig - 50;
		Y = YOrig - 50;
		X += (pat[Rand][i] * 30);
		Y += (pat[Rand][i + 1] * 30);
		X = (X / 30) + 1 + x;
		Y = (Y / 30) + 1;
		j = Map[Y][X];
		if (j > k)
			k = j;
	}
	return k;
}

void ChAnime()
{
	Graphics CHAR(BackBufDC); //�ѹ��ڱ��� 15�ȼ��� �̵�. 
							  //Status�� 0�̸� ����. 1�̸� ���������� �̵� 
	CHAR.DrawImage(Char, cx, cy, Pix * 30, 0, 30, 60, UnitPixel);

	/*
	���� �÷��̾� �Ӹ����� �������ԵǸ�
	0.5�ʵ����� ���� ĳ���� �Ӹ������ִٰ�
	�ٽ� ������ �׶������� ���ӿ���
	*/

}//ĳ���� �ִϸ��̼� �����Լ�

void Draw_Score(int x, int y, int what) //score�� �� �ڸ����� �и��Ͽ� ���ڿ��� ������ �� ���ڴ�� ���ھ� �̹��� ���
{
	Graphics S_core(BackBufDC);
	int Squa = 1, Per = what;
	int quo;
	char ScoreStr[6] = { 0 };

	for (int i = 0; i < 5; i++)
	{
		quo = Per / (10000 / Squa); //��
		ScoreStr[i] = (char)quo;
		Per %= (10000 / Squa);
		Squa *= 10;
		//540  370
		S_core.DrawImage(Score, x + (i * 35), y, ScoreStr[i] * 30, 0, 30, 36, UnitPixel);
	}
}

void IsWin() //�¸� üũ 
{
	if (cy < Fy) //ĳ���� ��ǥ�� ���� Y���� ������
	{
		_KillTimer();
		isWin = 1;
		SetTimer(hWnd, 11, 100, NULL);
	}
}

//int cx = 260, cy = 570; //ĳ���� ��ǥ // y = 80
void FallDown_Block(int a) //���� ĳ���� ��ǥ�� ��ĥ�� ������� ����.
{
	if ( Map[(cy ) / 30][ (a - 20) / 30 ] ==  1 || Map[(cy+30) / 30][(a - 20) / 30] == 1)
	{
		_KillTimer();
		islose = 1;
		//SendMessage(hWnd, WM_CLOSE, 0, 0);
	}
}

void WhenChaDie()	 //ĳ���Ͱ� ����Ҷ� �ִϸ��̼� 15
{
	Graphics ChLose(BackBufDC);

	ChLose.DrawImage(Char, cx, cy, 15 * 30, 0, 30, 60, UnitPixel);
}

void ActiveSleep(int Pix) //16 17 13 14
{
	Graphics Sleep(BackBufDC);
	Sleep.DrawImage(Char, cx, cy, Pix * 30, 0, 30, 60, UnitPixel);
}

void Over_Block(int i) //���� ������ ��� ���� ���������� �ٲ�.
{
	Graphics Over__Block(BackBufDC);
	
	for (int j = 1; j < WIDTH - 1; j++)
	{
		if (Map[i][j] == 2)
			Over__Block.DrawImage(OverBlock, j * 30 + 20, i * 30 + 20, 30, 30);
	}
}

void StageInform()
{
	Graphics Stg(BackBufDC);

	MultipleBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP26));
	SelectObject(MultipleDC, MultipleBitmap);

	Stg.DrawImage(StgInform, 200, 50, 420,600); //200 ~ 620 50 ~ 650 //������ â 
	BitBlt(BackBufDC, 250, 70, 250, 357, MultipleDC, (Chapter-1) * 250 , 0 , SRCCOPY); //�� �̸�����
	Stg.DrawImage(ScoreUI, 230, 540, 96, 34); //Score ���� ��� 
	Draw_Score(340,530, score);
	BitBlt(BackBufDC, 590, 40, 40, 40, BUTDC, 0, 0, SRCCOPY); //X��ư
	TransparentBlt(BackBufDC, 550, 580, 60, 60, BUTDC, 180, 0, 60, 60, RGB(64, 00, 64)); 
}

void OPtion()
{
	Graphics Opt(BackBufDC);

	Opt.DrawImage(Option, 200, 50, 370, 500);
}

void Dash() //���� ������ �غ� //int cx = 260, cy = 570; //ĳ���� ��ǥ // y = 80
{
	static int IsCanDs = 0;
	isDash = 1;
	if (DashCount < 4)
	{
		if (status == 1) //->
		{
			if ((cx - 50) % 30 == 0)
			{
				if (Map[cy / 30 ][(cx - 50) / 30 + 1] != 0)
					IsCanDs = 1;
			}
			else if ((cx - 50) % 30 == 15)
			{
				if (Map[cy / 30][(cx - 35) / 30 + 1] != 0)
					IsCanDs = 1;
			}

			if (IsCanDs == 0)
				cx += 15;
		}
		
		if(status == 0) // <-
		{
			if ((cx - 50) % 30 == 0)
			{
				if (Map[cy / 30 + 1][(cx - 50) / 30 - 1] != 0)
					IsCanDs = 1;
			}
			else if ((cx - 50) % 30 == 15)
			{
				if (Map[cy / 30 + 1][(cx - 65) / 30 - 1] != 0)
					IsCanDs = 1;
			}

			if(IsCanDs == 0)
				cx -= 30;
		}
	}
	else if(DashCount == 12)
	{
		DashCount = 0;
		IsCanDs = 0;
		isDash = 0;
		KillTimer(hWnd, 9);
		SetTimer(hWnd, 6, Time2, NULL);
	}
	DashCount++;
}

int WhatCircle(int x, int y) //�������� ����
{
	int Select=0;
	for (int i = 0; i < MaxClear*2; i+=2)
	{
		if (x+Plusa >= PointXY[i] && x + Plusa <= (PointXY[i] + 80) && y-120 >= PointXY[i + 1] && y-120 <= PointXY[i + 1]+80 && (i/2)+1 <= MaxClear)
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //��ư Ŭ����
			
			if (i != 0)
				Select = i / 2 + 1;
			else
				Select = 1;

			Chapter = (Select-1) / 6 + 1;

			LoadStageInform(Select);

			if (Inform == 1)
				Inform = 0;
			else
				Inform = 1;

			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
	}
	return Select;
}

void LoadStageInform(int StgNum)
{// StageData.txt ���Ͽ��� �������� �����͸� �о��.
	int DataBuf[7] = { 0 }; //���Ͽ��� �޾ƿ� ���� ��� ������ ����
	int Ten = StgNum / 10 , One = StgNum % 10;
	FILE* F;
	char buff[60];

	fopen_s(&F, "..\\Project______Resource\\StageData.txt","r");
	if (F == NULL)   //���������� ������ �о����� �˻�
	{ //���� �ε� ����
		return;
	}
	else //���� �ε� ���� 
	{
		while (!feof(F)) //���پ� �о����
		{
			fgets(buff, sizeof(buff), F);
			char* Data;
			if (buff[5] == Ten + 48 && buff[6] == One + 48) //�������� ��ȣ�� ������ �Ͱ� ������
			{
				Data = strtok(buff, " ");
				for (int i = 0; i < 7; i++)
				{
					Data = strtok(NULL, " ");
					DataBuf[i] = atoi(Data);
				}
				//�������� ���� �ʱ�ȭ
				MinusScore = DataBuf[0];
				PlusScore = DataBuf[1];
				Fy = DataBuf[2];
				ScoreSave = score = DataBuf[3];
				Time2 = DataBuf[4];
				Time1 = DataBuf[5];
				Laser = DataBuf[6];
				break;
			}
		}

	}
	fclose(F);
}

void _KillTimer()
{
	KillTimer(hWnd, 1);
	KillTimer(hWnd, 2);
	KillTimer(hWnd, 3);
	KillTimer(hWnd, 4);
	KillTimer(hWnd, 5);
	KillTimer(hWnd, 6);
	KillTimer(hWnd, 7);
	KillTimer(hWnd, 8);
	KillTimer(hWnd, 9);
	KillTimer(hWnd, 10);
	KillTimer(hWnd, 11);
	KillTimer(hWnd, 12);
}

void PlayBGM() //���� ����� ����ϴ� �Լ� 
{
	LPCWSTR BGM[5]; //���� ��� ��� �����͹迭 
	BGM[0] = L"..\\Project______Resource\\����\\Space.mp3";
	BGM[1] = L"..\\Project______Resource\\����\\Factory.mp3";
	BGM[2] = L"..\\Project______Resource\\����\\Mirror.mp3";
	BGM[3] = L"..\\Project______Resource\\����\\SnowNight.mp3";
	BGM[4] = L"..\\Project______Resource\\����\\Digital_Solitude.mp3";


	mciSendCommand(1, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL); //���� Ʋ�����ִ� ��� ���� 
	Sound1 = LoadWAV(hWnd, BGM[Chapter], 0); //�� ��� �ְ�
	Sound1 = mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay); //���
}

void ClearEffect()
{
	static int px = 0;
	Graphics CE(BackBufDC);

	CE.DrawImage(Option, 150, 30, 0, 0, 370, 500, UnitMillimeter); //���� â 
	CE.DrawImage(Result, 180, 300, 0, 200, 330, 400, UnitPixel); //��� ��� 
	CE.DrawImage(ClrEff, 200, 100, px * 300, 0, 300, 120, UnitPixel); //clear �ִϸ��̼�

	if (px == 4)
	{
		KillTimer(hWnd, 11);
		px = 0;
		//Ŭ���� �� �������� �ʱ�ȭ//
		BitBlt(CopyDC, 50, 50, 420, 600, CopyClearDC, 0, 0, SRCCOPY);//�ش� ��Ʈ���� ����� ��������μ� ������ ������
		TransparentBlt(CopyDC, 50, 50, 420, 600, CopyDC, 50, 50, 420, 600, RGB(0, 0, 0)); //�� ��� DC�� hdc�� ��� 
		InvalidateRect(hWnd, NULL, FALSE);
		MaxClear++; //Ȱ��ȭ ���������� 1 �ø���

		Sleep(1000);
		cx = StartX; cy = StartY; //ĳ���� ��ġ�� �ٽ� ���������� ����
		InitBoard();
	}
	px++;
}

void GameOverEf()
{
	static int ypix=0;

	Graphics GO(BackBufDC);
	GO.DrawImage(GameOver, 200, 200, 0, ypix * 120, 300, 120, UnitPixel);
	GO.DrawImage(Result, 180, 300, 0, 300, 330, 100, UnitPixel); //��� ��� 
	ypix++;

	if (ypix == 3)
	{
		_KillTimer();
		BitBlt(CopyDC, 50, 50, 420, 600, CopyClearDC, 0, 0, SRCCOPY);//�ش� ��Ʈ���� ����� ��������μ� ������ ������
		InitBoard();
		cx = StartX; cy = StartY; //ĳ���� ��ġ�� �ٽ� ���������� ����
		islose = 0;
		Game_Start = 2; //�������� ����â���� �̵�
		ypix = 0;
		COUNT = 0;
		KillTimer(hWnd, 12);
	}
	InvalidateRect(hWnd, NULL, FALSE);
}
