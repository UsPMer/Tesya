	/*
	모든 출력은 더블 버퍼링 기법을 이용하여 출력하며,
	투명블럭, 이펙트등은 PNG형식으로 투명을 출력하여 작업량을 줄이고,
	이외의 블럭, 배경등은 bmp형식으로 출력한다.
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

//Gdi+ 사용을 위한 초기화
ULONG_PTR gpToken;  // 마지막에 GdiplusShutdown에서 사용하므로 저장필수.
GdiplusStartupInput gpsi;

#define random(n) (rand()%n); //난수 생성
#define JUMPINGSEC 40
#define SLEEPTIME 200
#define UP 72
#define ESC 27
#define FIXWID 800 //가로
#define FIXHID 750 //세로 
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

int MinusScore; //감점 값
int PlusScore; //증가 값 
int Fy ; //골인 높이
int score; //기본 점수
int Time2; //캐릭터 이동속도
int Time1; //블럭 내려오는 속도 (ms)
int Laser; //레이저 주기

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
				   //각 스테이지의 중앙 좌표값을 저장후 마우스 커서의 위치와 대조하여 비교한다. 
int ScoreArray[24] = { 10000,10000, };
int pat[7][32] = { //블럭 패턴
	{ 0,0, 1,0, 2,0, -1,0, 0,0, 0,1, 0,-1, 0,-2, }, //|
	{ 0,0, 1,0, 0,1, 1,1, }, //ㅁ
	{ 0,0, -1,0, 0,-1, 1,-1,   -1,-1,0,0, 0,1, -1,0, }, // ㄱㄴ
	{ 0,0, -1,-1, 0,-1, 1,0,   0,0, -1,0, -1,1, 0,-1, }, //역ㄱㄴ
	{ 0,0, 0,-1, 1,0, 2,0,   0,0, -1,0 , 0,-1, 0,-2,   0,0, -1,0, -2,0, 0,1,   0,0, 1,0, 0,1, 0,2 },//|--
	{ 0,0, -1,0, -2,0, 0,-1,   0,0, -1,0, 0,1, 0,2,   0,0, 0,1, 1,0, 2,0,   0,0, 1,0, 0,-1, 0,-2 }, //--|
	{ 0,0, -1,0, 1,0, 0,1,   0,0 ,0,-1 ,0,1, 1,0,   0,0, -1,0, 1,0, 0,-1,   0,0 ,-1,0, 0,-1, 0,1 } // ㅗ
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
//int x = 180 + 50, y = 60 + 50 원점 == 230, y = 110
int x = 260, y = 110, XOrig = x, YOrig = y;
int cx = 260, cy = 570; //캐릭터 좌표
int Nx = 520, Ny = 50;
int NextColor = 0, NowColor = 0;
int IsFirst = 0;
int IsKeyDown = 0;
int DeleteLine;

LPCTSTR Win = TEXT("클리어");
LPCTSTR End = TEXT("패배");
POINT mouse;
HDC hdc, MemDC, NextBDC, hMemDC, BMemDC, OLMemDC, BackBufDC,OldDC, CopyDC, BlackDC, WhenRandDC,BUTDC, MultipleDC; //DC
HDC EffectDC, EffBlackDC, BGDC, MainDC, NextBackDC, CharDC, FinishDC, UiDC, StageMDC, ClearDC, TextDC, CopyClearDC;
HBITMAP MyBitmap, OldBitmap, BackBitmap, SaveBitmap, CopyBitMap, BlackBitmap, hEffBlack, BGBitmap, MainBitmap, UIBmp,ButtonBmp; //비트맵 저장 핸들
HBITMAP hBlock, hNextBlock, hBlock2, BackGround, hOlMem,hWhenR, hEffect, NextBackBitmap, CharBitmap ,BUT2DC,StageMBmp , CopyClearBmp; //블럭 이미지 저장 핸들
HBITMAP STARTBmp, FinishBmp, TextBmp, MultipleBitmap;
HWND hWnd, Button1,Lb,Rb;
HINSTANCE g_hInst;
BOOL Game_Start; //Game_Start = 0 -> 게임 시작전, 1 -> 시작 
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
void ChAnime(); //캐릭터 애니메이션 구현 함수 
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

Image* LoadPNG(HMODULE hModule, LPCWSTR ResourceName) //PNG 파일을 리소스 파일에서 로드 하는 Gdi 함수 
{
	//http://m.blog.naver.com/totoru1219/220702210611 자세한 것은 다음 블로그 참고.

	Image* image = NULL;
	IStream* pStream = NULL;

	HRSRC hResource = FindResource(hModule, ResourceName, L"PNG"); //"PNG" 형식의 파일을 리소스파일에서 찾은 후 hResource에 반환
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

	if(sel == 1) //1이면 wav
		m_mciOpenParms.lpstrDeviceType = L"WaveAudio";
	else //0이면 mp3
		m_mciOpenParms.lpstrDeviceType = L"MPEGVideo";
	//WaveAudio 대신 MPEGVideo를 사용하면 mp3 형식을 재생합니다.

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
	Token인자는 윈도우의 핸들과 유사한 GDI+의 라이브러리 Token. 이 값은 GdiplusShutdown()함수의 인자로 이용됨.
	Input인자는 입력 옵션을 정의하는 GdiPlusStartupInput구조체의 주소, 별도의 옵션이 없다면 Default값이 설정됨.
	Ouput는 초기화 결과 반환. NULL이라면 결과받지 않음.
	*/
	if (GdiplusStartup(&gpToken, &gpsi, NULL) != Ok) { //Gdi+ 초기화
		MessageBox(NULL, TEXT("GDI+ 라이브러리 초기화 불가."),
			TEXT("알림"), MB_OK);
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
		FIXWID, //가로
		FIXHID, //세로
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

////////////////// 메시지 처리 루틴///////////////// 

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC HMDC;
	LPDRAWITEMSTRUCT lpdis; //버튼 DC 지정할 포인터

	switch (iMessage) {
	case WM_CREATE: //윈도우 생성시 메세지 
		/****************초기 필수 정보 초기화****************/
		srand(time(NULL));
		Rand = random(7);
		MaxArray = 8 * (rand() % brickpatnum[Rand] + 1);
		NRand = random(7);
		NMaxArray = 8 * (rand() % brickpatnum[NRand] + 1); //1~ NRand - 1 
		NowColor = RandColor();
		NextColor = RandColor();

		//////// DC 초기화 /////////////
		hdc = GetDC(hWnd);
		MemDC = CreateCompatibleDC(hdc); //CreateCompatibleDC(원본DC): 원본 DC를 복사함.
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

		TextBmp = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP24)); //Text비트맵 
		SelectObject(TextDC, TextBmp);

		StageMBmp = CreateCompatibleBitmap(hdc, 2334, 435); //Stage비트맵
		SelectObject(StageMDC, StageMBmp);
	
		CharBitmap = CreateCompatibleBitmap(hdc, 420, 60); //캐릭터 비트맵
		SelectObject(CharDC, CharBitmap);

		hEffect = CreateCompatibleBitmap(hdc, 420, 70); //이펙트 그려둘 비트맵 
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
		FillRect(BackBufDC, &rt, (HBRUSH)GetStockObject(WHITE_BRUSH)); //도화지 색 변경
		/////////////////////////////////////////

		////////// DC에 초기 비트맵 저장/////////
		FinishBmp = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP19)); //목표 높이 
		SelectObject(FinishDC, FinishBmp);
		NextBackBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP17));
		SelectObject(NextBackDC, NextBackBitmap);

		BGBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP15));

		/////////////////// PNG //////////////////////
		image = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG1)); //빈공간 블록 이미지 저장 (Gdi)
		WBimage = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG2)); //착지점 블럭
		imgEffect = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG3)); //이펙트 
		Score = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG4)); //숫자 0~9
		Char = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG5)); //캐릭터 스프라이트 저장 
		GameOver = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG6)); //GameOver 문구
		ScoreUI = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG7)); //Score 문구 
		OverBlock = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG8)); //오버 블럭
		Stage = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG9)); //스테이지 맵 
		Coin = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG10)); //코인
		StgInform = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG11)); //스테이지 정보
		StageCircle = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG12));
		Option = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG13)); //옵션 창 
		StageNum = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG14)); //스테이지 번호
		HPLine = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG15));
		Boss = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG16));
		ClrEff = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG17));
		Result = LoadPNG(g_hInst, MAKEINTRESOURCE(IDB_PNG18));
		//////////////////////////////////////////////

		hEffBlack = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP14));
		SelectObject(EffBlackDC, hEffBlack);

		///////// 다음 나올 블록 비트맵 초기 설정 ////////
		hNextBlock = LoadBitmap(g_hInst, MAKEINTRESOURCE(NextColor));
		SelectObject(NextBDC, hNextBlock);
		////////////////////////////////////////////////

		////////맨 처음 나올 블록 비트맵 초기 설정 ////////
		hBlock = LoadBitmap(g_hInst, MAKEINTRESOURCE(NowColor)); //벽돌 이미지 저장
		SelectObject(hMemDC, hBlock); //hMemDC에 hBlock 비트맵 선택
		///////////////////////////////////////////////////
		ButtonBmp = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP21));
		SelectObject(BUTDC, ButtonBmp);
		MainBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP16));
		SelectObject(MainDC, MainBitmap);
		BlackBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP12));
		SelectObject(BGDC, BGBitmap);
		SelectObject(BlackDC, BlackBitmap);
		BackGround = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP22)); //배경 이미지 저장
		SelectObject(BMemDC, BackGround);
		hOlMem = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP9)); //외곽선 이미지 저장 
		SelectObject(OLMemDC, hOlMem);
		////////////////////////////////////////

		/*********************** 음악 ******************************/
		/* 모든 음악은 상대경로를 지정하여 다른 컴퓨터에서도 실행이 되도록 한다..
		효과음은 PlaySound를 이용하여 출력을 한다. */
		 //
		Sound1 = LoadWAV(hWnd, L"..\\Project______Resource\\음향\\MainTitle_BGM.wav", 1); //메인 BGM
		Sound1 = mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
		/***********************************************************/

		/********************** 버튼 *******************************/
		
		STARTBmp = LoadBitmap((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDB_BITMAP18)); //START 이미지
		//SendMessage(Button1, BM_SETIMAGE, 0, (LPARAM)hEffect);
		Button1 = CreateWindow(TEXT("button"), //START 버튼
			TEXT("START"), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW|
			BS_PUSHBUTTON, 300, 400, 200, 80, hWnd, (HMENU)0,
			g_hInst, NULL);
		//SendMessage(Button1, BM_SETIMAGE, 0, (LPARAM)STARTBmp); //버튼 이미지를 버튼에 씌움
		/*Button1 = CreateWindowEx(WS_EX_TRANSPARENT,TEXT("button"), //START 버튼
			TEXT("START"), WS_CHILD | WS_VISIBLE | BS_ICON | 
			BS_PUSHBUTTON , 300, 400, 200, 80, hWnd, (HMENU)0,
			g_hInst, NULL);
		SendMessage(Button1, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_ICON1))); //버튼 이미지를 버튼에 씌움*/
		/************************************************************/
		BitBlt(CopyDC, 50, 50, 420, 600, CopyClearDC, 0, 0, SRCCOPY);//해당 테트리스 배경을 덮어씌움으로서 블럭들을 없애줌
		TransparentBlt(CopyDC, 50, 50, 420, 600, CopyDC, 50, 50, 420, 600, RGB(0, 0, 0)); //블럭 담는 DC를 hdc에 출력 
		InitBoard();
		isWin = 0;
		Game_Start = 0; //초기화 0은 시작전 1이 시작

		break;
    case WM_DRAWITEM: //Owenr Draw로 버튼을 그려줌. 
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
	case WM_COMMAND: //버튼 메세지 
		switch (LOWORD(wParam))
		{
		case 0: //START 버튼 누를 시 
			mciSendCommand(1, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL); //메인화면 브금 종료
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //버튼 클릭음 
			Game_Start = 2;
			
			//PlaySound(NULL, 0, 0); //사운드를 정지합니다
			DestroyWindow(Button1);
			Sound2 = LoadWAV(hWnd, L"..\\Project______Resource\\음향\\Digital_Solitude.mp3", 0); //겨울밤 테마 브금 
			Sound2 = mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		return 0;

	case WM_LBUTTONDOWN: //모든 클릭 이벤트를 관리 
	{
		TCHAR text[100] = { 0 };
		GetCursorPos(&mouse); //커서 좌표 얻어오기
		ScreenToClient(hWnd, &mouse); //클라이언트(게임창) 좌표로 변환
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

		if (R == 207 && G == 205 && B == 205 && mouse.x < 400) //왼쪽 방향버튼
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //버튼 클릭음 
			if (Sx != -100)
				Sx -= 100;
			InvalidateRect(hWnd, NULL, FALSE);
		}
		else if (R == 207 && G == 205 && B == 205 && mouse.x > 400) //오른쪽 방향버튼
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //버튼 클릭음 
			if (Sx != 1700)
				Sx += 100;
			InvalidateRect(hWnd, NULL, FALSE);
		}
		else if ( (R == 111 && G == 118 && B == 255) || (R == 218 && G == 220 && B == 255) ) //뒤로 가기
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //버튼 클릭음 
			Game_Start = 0;
			InvalidateRect(hWnd, NULL, FALSE);

			Button1 = CreateWindow(TEXT("button"), //START 버튼
				TEXT("START"), WS_CHILD | WS_VISIBLE | BS_OWNERDRAW |
				BS_PUSHBUTTON, 300, 400, 200, 80, hWnd, (HMENU)0,
				g_hInst, NULL);
		}
		else if ((R == 151 && G == 175 && B == 255) || (R == 95 && G == 83 && B == 255)) //설정창 
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //버튼 클릭음 
			if (_Option == 1)
				_Option = 0;
			else
				_Option = 1;
			InvalidateRect(hWnd, NULL, FALSE);
		}
		else if (R == 119 && G == 199 && B == 84) //
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //버튼 클릭음 
			mciSendCommand(1, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL); //전에 틀어져있던 브금 종료
			Sound1 = LoadWAV(hWnd, L"..\\Project______Resource\\음향\\Digital_Solitude.mp3", 0); //새 브금 넣고
			Sound1 = mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay); //재생
			Game_Start = 2;
			InvalidateRect(hWnd, NULL, FALSE);
		}
		else if (R == 255 && G == 122 && B == 122) //시작 버튼
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //버튼 클릭음 
			PlayBGM();
			Inform = 0;
			Game_Start = 1;
			InvalidateRect(hWnd, NULL, FALSE);
			SetTimer(hWnd, 10, SCTimer, NULL); //감점 스코어
			SetTimer(hWnd, 1, Time1, NULL);
			SetTimer(hWnd, 6, Time2, NULL);
		}
		else if (R == 182 && G == 36 && B == 12)
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //버튼 클릭음 
			Inform = 0;
			InvalidateRect(hWnd, NULL, FALSE);
		}
		else if (mouse.x >= 520 && mouse.x <= 720 && mouse.y >= 450 && mouse.y <= 530 && Game_Start == 1) //520, 450  // 520, 550 //RETRY
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //버튼 클릭음 
			BitBlt(CopyDC, 50, 50, 420, 600, BMemDC, 420 * (Chapter - 1), 0, SRCCOPY);//해당 테트리스 배경을 덮어씌움으로서 블럭들을 없애줌
			cx = StartX; cy = StartY; //캐릭터 위치를 다시 시작점으로 돌림 
			score = ScoreSave;

			InitBoard(); //맵 값 초기화
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
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //버튼 클릭음
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
						PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //버튼 클릭음
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
						PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //버튼 클릭음 
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
				RightNowSelec(); //즉시 배치 
			}
			break;
		case 0x44: //D키 대쉬로 교체  
			if (isDash == 0 && isWin==0)
			{
				KillTimer(hWnd, 6);
				SetTimer(hWnd, 9, DASHTIME, NULL);
			}
			break;

		case 0x46: //F키 Active
			if (isWin == 0)
			{
				KillTimer(hWnd, 6);
				SetTimer(hWnd, 7, SLEEPTIME, NULL);
			}
			break;
		}

		break;
	case WM_KEYUP: //D키가 캐릭터 점프키 
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
				if (CheckCols() == 1) //블럭 충돌 감지시 
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

						///////////// 블럭 정보 초기화////////////////
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

		case 4: //Down키 타이머 
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
		case 5: //블럭 폭발 애니메이션 //460 * (Ex - 1)
		{
			if (Ex == 1)
				PlaySound(MAKEINTRESOURCE(IDR_WAVE6), NULL, SND_RESOURCE | SND_ASYNC); //폭발음
			Graphics Exp(EffectDC);
			BitBlt(EffectDC, 0, 0, 420, 70, EffBlackDC, 0, 0, SRCCOPY); //이펙트 DC 리프레시
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

		case 6: //캐릭터 애니메이션  0= 빈공간, 1= 이동중인 블럭 2= 배치된 블럭 3 = 벽
			//cx = 260, cy = 570; //캐릭터 좌표

			//블럭 낙사 검사 구간
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
			
			if (status == 0) //status 0일시 <-
			{
				cx -= 15;
				if (Map[(cy + 60) / 30][cx / 30] == 0 && Map[(cy + 90) / 30][cx / 30] == 0 
					&& Map[(cy + 120) / 30][cx / 30] == 0 && Map[(cy + 150) / 30][cx / 30] == 0) //4칸 이상시 낙사 
				{
					cy += 60;
					islose = 1;
				}
				else if (Map[(cy + 30) / 30][cx / 30] != 0) //계단 판정
						cy -= 30;
				else if (Map[(cy + 60) / 30][cx / 30] == 0)
						cy += 30;

				if (Pix != 4)
					Pix++;
				else
					Pix = 1;
			}
			else //1일시 ->
			{
				cx += 15;
				if (Map[(cy + 60) / 30][(cx) / 30] == 0 && Map[(cy + 90) / 30][(cx) / 30] == 0
					&& Map[(cy + 120) / 30][(cx) / 30] == 0 && Map[(cy + 150) / 30][(cx) / 30] == 0) //4칸 이상 시 낙사 
				{
					cy += 120;
					islose = 1;
				}
				else if (Map[(cy + 30) / 30][(cx + 15) / 30] != 0) //계단 판정
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
		case 7: //F키 모션 (3초간 수면)
			if (s == 16)
				KillTimer(hWnd, 6); //캐릭터 이동 타이머 잠시 멈춤
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
		case 8: //게임 오버시 오버블럭을 깔아주는 타이머 
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
		case 9: //캐릭터 대시 //cx = 260, cy = 570; //캐릭터 좌표 1~20 
			Dash();
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		case 10:
			score -= MinusScore; //점수 감소 
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
		if (Game_Start == 2)//스테이지 창 
		{
			PrintStage();
			if (Inform == 1)
				StageInform();
			if (_Option == 1)
				OPtion();
			BitBlt(hdc, 0, 0, FIXWID, FIXHID, BackBufDC, 0, 0, SRCCOPY); //BackBufDC를 화면으로 복사후 출력
			isWin = 0;
		}
		else if (Game_Start == 1)
		{
			Graphics UK(BackBufDC);
			DrawScreen(); //블록을 제외한 모든 화면 출력
			Draw_Block(1); //블록 출력 1 = 블록 & 0 = 공백 블록 
			TransparentBlt(BackBufDC, 50, 50, 420, 600, CopyDC, 50, 50, 420, 600, RGB(255, 255, 255)); //블럭 담는 DC를 hdc에 출력 
			Draw_AlphaBlock(BackBufDC); //빈공간 블럭 출력 
			UK.DrawImage(HPLine, 50, Fy, 0, 45, 315, 45, UnitPixel); //도달점 바
			WhereBlock(); //착지점 출력
			TransparentBlt(BackBufDC, 50, DeleteLine * 30 - 10, 420, 70, EffectDC, 0, 0, 420, 70, RGB(0, 0, 0)); //이펙트 출력
			
			if (isWin == 1)
			{
				ClearEffect();
				BitBlt(hdc, 0, 0, FIXWID, FIXHID, BackBufDC, 0, 0, SRCCOPY); //BackBufDC를 화면으로 복사후 출력 
			}
			if (isDash == 1)
			{
				if(DashCount != 4)//540  600 
					UK.DrawImage(Char, cx, cy, 540 + (status * 2 * 60), 0, 60, 60, UnitPixel);
				else
					UK.DrawImage(Char, cx, cy, 600 + (status * 2 * 60), 0, 60, 60, UnitPixel);
			}
			else if (SEC != 0 && islose != 1 && isDash == 0) //자는거면 
				ActiveSleep(s);
			else if (islose != 1 && SEC == 0 && isDash == 0 && isWin == 0) //패배가 아닐시 계속 이동 
				ChAnime();
			else if (islose == 1) //사망시 사망 애니메이션 
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
					BitBlt(hdc, 0, 0, FIXWID, FIXHID, BackBufDC, 0, 0, SRCCOPY); //BackBufDC를 화면으로 복사후 출력
				}

				Over_Block(WL);
				WhenChaDie();
			}
			BitBlt(hdc, 0, 0, FIXWID, FIXHID, BackBufDC, 0, 0, SRCCOPY); //BackBufDC를 화면으로 복사후 출력 
		}
		else if(Game_Start == 0) //메인
		{
			BitBlt(hdc, 0, 0, FIXWID, FIXHID, MainDC, 0, 0, SRCCOPY); //메인 화면 출력 
		}
		EndPaint(hWnd, &ps);
		break;

	case WM_CLOSE: //패배 시
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
		if (image != NULL) //GDI+ 객체 삭제 
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
		ReleaseDC(hWnd, hdc); //DC 해제 
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

void PrintStage() //스테이지 창에서의 UI 
{ 
	int CicleX=0;
	static int O = 0;
	//뒤로 / 설정 / 코인UI 
	Graphics STAGE(StageMDC);
	Graphics COIN(BackBufDC);

	BitBlt(BackBufDC, 0, 0, 800, 750, BGDC, 0, 0, SRCCOPY); //뒷배경

	////////////////////////스테이지 맵///////////////////////////////////////////
	if (O == 0)
	{
		STAGE.DrawImage(Stage, 0, 0, 0, 0, 1750, 325, UnitPixel); //스테이지 맵 StageMDC에 출력 
		STAGE.DrawImage(Stage, 0, 0, 0, 0, 1750, 325, UnitPixel);
		STAGE.DrawImage(Stage, 0, 0, 0, 0, 1750, 325, UnitPixel);
		O++;
	}
		STAGE.DrawImage(Stage, 0, 0, 0, 0, 1750, 325, UnitPixel);
	for (int i = 0; i < MaxClear * 2; i+=2) //스테이지 써클 출력 
	{
		int j;
		if (i == 4 || i == 16 || i == 28 || i == 40) //중간보스 스테이지
			CicleX = 120;
		else if (i == 10 || i == 22 || i == 34 || i == 46) //보스 스테이지 
			CicleX = 60;
		else //이외 스테이지 
			CicleX = 0;
		STAGE.DrawImage(StageCircle, PointXY[i], PointXY[i+1], CicleX, 0,60,60,UnitPixel); //스테이지 버튼 다 그려주기 

		j = i / 2 + 1;
		if(j < 10)
			STAGE.DrawImage(StageNum, PointXY[i] + 31, PointXY[i + 1] + 30, j * 15, 0, 15, 18, UnitPixel);//번호 그리기 
		else
		{
			int t = j / 10, o = j % 10; //십의 자리 일의 자리
			STAGE.DrawImage(StageNum, PointXY[i] + 25, PointXY[i + 1] + 30, t * 15, 0, 15, 18, UnitPixel);//번호 그리기
			STAGE.DrawImage(StageNum, PointXY[i] + 40, PointXY[i + 1] + 30, o * 15, 0, 15, 18, UnitPixel);//번호 그리기
		}
	} //버튼 숫자 출력

	BitBlt(BackBufDC, 0, 120, 800, 435, StageMDC, Sx, Sy, SRCCOPY); //다 그려진 스테이지맵을 백 버퍼에 복사 
	//////////////////////////////////////////////////////////////////////////////

	BitBlt(BackBufDC, 20, 30, 40, 40, BUTDC, 60, 0, SRCCOPY); //뒤로가기 
	BitBlt(BackBufDC, 70, 30, 40, 40, BUTDC, 120, 0, SRCCOPY); //설정
	COIN.DrawImage(Coin, 530, 30, 240, 60); //코인 BackBufDC에 출력 
	Draw_Score(590, 35, _Coin);
	TransparentBlt(BackBufDC, 10, 300, 30, 60, BUTDC, 240, 0, 29, 60,RGB(64,0,64)); //왼 버튼
	TransparentBlt(BackBufDC, 730, 300, 30, 60, BUTDC, 270, 0, 30, 60, RGB(64, 0, 64)); //오른 버튼
}

void RightNowSelec() //즉시 배치 함수
{
	PlaySound(MAKEINTRESOURCE(IDR_WAVE3), NULL, SND_RESOURCE | SND_ASYNC); //착지음 
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

			///////////// 블럭 정보 초기화////////////////
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

void WhereBlock() //착지점 블럭
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

void DrawScreen() //배경, UI등을 모두 출력 
{
	Graphics UI(BackBufDC);
	
	BitBlt(BackBufDC, 0, 0, 800, 750, BGDC, 0, 0, SRCCOPY); //뒷배경
	BitBlt(BackBufDC, 40, 40, 440, 620, OLMemDC, 0, 0, SRCCOPY); //외곽선 
	BitBlt(BackBufDC, 500, 41, 240, 240, NextBackDC, 0, 0, SRCCOPY);  //미리보기창
	BitBlt(BackBufDC, 50, 50, 420, 600, BMemDC, 420*(Chapter-1), 0, SRCCOPY);//테트리스 배경 
	DrawNextBlock(); //다음 블럭
	BitBlt(BackBufDC, 500, 300, 240, 360, UiDC, 0, 0,SRCCOPY); //우측하단 UI
	UI.DrawImage(ScoreUI, 580, 320, 96, 34); //Score 문구 출력 
	BitBlt(BackBufDC, 520, 450, 200, 80, TextDC, 200, 0, SRCCOPY); //RETRY 
	BitBlt(BackBufDC, 520, 550, 200, 80, TextDC, 600, 0, SRCCOPY); //OPTION
	Draw_Score(540, 370, score); //점수 출력
}

void DrawNextBlock() //다음 나올 블럭 출력 
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

void InitBoard() //배열 초기화 0 = 빈공간 1 = 벽 
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

void Draw_Block(int flag) //블럭 출력 함수  // brickpatnum[7] = { 2,1,2,2,4,4,4 };
{
	//testArray();
	HDC B;
	B = GetDC(hWnd);

	if (flag == 1) //1이면 벽돌 0이면 투명 
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

void Draw_AlphaBlock(HDC DC) //맵 전체에 투명블럭을 깔아준다. 
{
	x = 20; y = 50;
	Graphics g(DC); //Gdi Graphic 객체 g 선언후 dc 초기화
						   /*Bitmap *pBitmap = image; //출력할 이미지 변수입니다
						   Bitmap memBitmap(pBitmap->Width(), pBitmap->Height()); //가져온 이미지의 크기만큼 Bitmap 파일을 하나 만듭니다.
						   Graphics memG(&memBitmap); //메모리에 그려줄 Graphics변수입니다.*/

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

int CheckCols() //0 = 충돌X 1 = 충돌o 
{
	for (int i = HIDTH - 1; i > 0; i--)
	{

		for (int j = WIDTH - 1; j >= 0; j--)
		{
			if (Map[i][j] == 3 || Map[i][j] == 2) //벽이거나 설치된 블럭이면
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
	return  (rand() % 7 + 122); //resource.h의 리소스 번호에 따라 조정. 122~128 블럭
}

void downmove() //WM_TIMER의 timer 주기로 블록이 1칸씩 내려감.
{
	Draw_Block(0);
	InvalidateRect(hWnd, NULL, FALSE);
	CleanAry();
	YOrig += 30;
	InsertAry();
	CheckCols();
	Draw_Block(1);
}

void leftmove() //왼쪽으로 이동.
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

void rightmove() //오른쪽으로 이동.
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

void CleanAry() //배열에 저장되있는 이동전의 블럭값을 없애준다.
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

void SelectBlock() //밑부분이 닿을시 2이던 값은 3로 바뀌며 고정됨.
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

void InsertAry() //블록값을 1으로 초기화 하여 이동중임을 나타낸다.
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

void rotate() //블럭 회전 함수 
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

int isfull() //1칸이 다 찼을시 비워줌.
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

void CleanLine() //블럭이 다 채워진 줄을 지운후, 지운수만큼 윗 블럭들을 밑으로 내려준다.
{
	SetTimer(hWnd, 5, 60, NULL); //폭발 이펙트 타이머 
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

void IsLose() //패배 처리 
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
	Graphics CHAR(BackBufDC); //한발자국에 15픽셀씩 이동. 
							  //Status가 0이면 왼쪽. 1이면 오른쪽으로 이동 
	CHAR.DrawImage(Char, cx, cy, Pix * 30, 0, 30, 60, UnitPixel);

	/*
	블럭이 플레이어 머리위로 떨어지게되면
	0.5초동안은 블럭이 캐릭터 머리위에있다가
	다시 떨어짐 그때맞으면 게임오버
	*/

}//캐릭터 애니메이션 구현함수

void Draw_Score(int x, int y, int what) //score의 각 자리값을 분리하여 문자열에 넣은후 그 문자대로 스코어 이미지 출력
{
	Graphics S_core(BackBufDC);
	int Squa = 1, Per = what;
	int quo;
	char ScoreStr[6] = { 0 };

	for (int i = 0; i < 5; i++)
	{
		quo = Per / (10000 / Squa); //몫
		ScoreStr[i] = (char)quo;
		Per %= (10000 / Squa);
		Squa *= 10;
		//540  370
		S_core.DrawImage(Score, x + (i * 35), y, ScoreStr[i] * 30, 0, 30, 36, UnitPixel);
	}
}

void IsWin() //승리 체크 
{
	if (cy < Fy) //캐릭터 좌표가 일정 Y값을 넘으면
	{
		_KillTimer();
		isWin = 1;
		SetTimer(hWnd, 11, 100, NULL);
	}
}

//int cx = 260, cy = 570; //캐릭터 좌표 // y = 80
void FallDown_Block(int a) //블럭이 캐릭터 좌표에 곂칠시 사망으로 판정.
{
	if ( Map[(cy ) / 30][ (a - 20) / 30 ] ==  1 || Map[(cy+30) / 30][(a - 20) / 30] == 1)
	{
		_KillTimer();
		islose = 1;
		//SendMessage(hWnd, WM_CLOSE, 0, 0);
	}
}

void WhenChaDie()	 //캐릭터가 사망할때 애니메이션 15
{
	Graphics ChLose(BackBufDC);

	ChLose.DrawImage(Char, cx, cy, 15 * 30, 0, 30, 60, UnitPixel);
}

void ActiveSleep(int Pix) //16 17 13 14
{
	Graphics Sleep(BackBufDC);
	Sleep.DrawImage(Char, cx, cy, Pix * 30, 0, 30, 60, UnitPixel);
}

void Over_Block(int i) //게임 오버시 모든 블럭이 오버블럭으로 바뀜.
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

	Stg.DrawImage(StgInform, 200, 50, 420,600); //200 ~ 620 50 ~ 650 //상세정보 창 
	BitBlt(BackBufDC, 250, 70, 250, 357, MultipleDC, (Chapter-1) * 250 , 0 , SRCCOPY); //맵 미리보기
	Stg.DrawImage(ScoreUI, 230, 540, 96, 34); //Score 문구 출력 
	Draw_Score(340,530, score);
	BitBlt(BackBufDC, 590, 40, 40, 40, BUTDC, 0, 0, SRCCOPY); //X버튼
	TransparentBlt(BackBufDC, 550, 580, 60, 60, BUTDC, 180, 0, 60, 60, RGB(64, 00, 64)); 
}

void OPtion()
{
	Graphics Opt(BackBufDC);

	Opt.DrawImage(Option, 200, 50, 370, 500);
}

void Dash() //여기 수정할 준비 //int cx = 260, cy = 570; //캐릭터 좌표 // y = 80
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

int WhatCircle(int x, int y) //스테이지 구별
{
	int Select=0;
	for (int i = 0; i < MaxClear*2; i+=2)
	{
		if (x+Plusa >= PointXY[i] && x + Plusa <= (PointXY[i] + 80) && y-120 >= PointXY[i + 1] && y-120 <= PointXY[i + 1]+80 && (i/2)+1 <= MaxClear)
		{
			PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC); //버튼 클릭음
			
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
{// StageData.txt 파일에서 스테이지 데이터를 읽어옴.
	int DataBuf[7] = { 0 }; //파일에서 받아온 값을 잠시 저장할 버퍼
	int Ten = StgNum / 10 , One = StgNum % 10;
	FILE* F;
	char buff[60];

	fopen_s(&F, "..\\Project______Resource\\StageData.txt","r");
	if (F == NULL)   //정상적으로 파일을 읽었는지 검사
	{ //파일 로드 실패
		return;
	}
	else //파일 로드 성공 
	{
		while (!feof(F)) //한줄씩 읽어내려감
		{
			fgets(buff, sizeof(buff), F);
			char* Data;
			if (buff[5] == Ten + 48 && buff[6] == One + 48) //스테이지 번호가 선택한 것과 같으면
			{
				Data = strtok(buff, " ");
				for (int i = 0; i < 7; i++)
				{
					Data = strtok(NULL, " ");
					DataBuf[i] = atoi(Data);
				}
				//스테이지 정보 초기화
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

void PlayBGM() //음악 재생을 담당하는 함수 
{
	LPCWSTR BGM[5]; //음악 경로 담는 포인터배열 
	BGM[0] = L"..\\Project______Resource\\음향\\Space.mp3";
	BGM[1] = L"..\\Project______Resource\\음향\\Factory.mp3";
	BGM[2] = L"..\\Project______Resource\\음향\\Mirror.mp3";
	BGM[3] = L"..\\Project______Resource\\음향\\SnowNight.mp3";
	BGM[4] = L"..\\Project______Resource\\음향\\Digital_Solitude.mp3";


	mciSendCommand(1, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL); //전에 틀어져있던 브금 종료 
	Sound1 = LoadWAV(hWnd, BGM[Chapter], 0); //새 브금 넣고
	Sound1 = mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay); //재생
}

void ClearEffect()
{
	static int px = 0;
	Graphics CE(BackBufDC);

	CE.DrawImage(Option, 150, 30, 0, 0, 370, 500, UnitMillimeter); //바탕 창 
	CE.DrawImage(Result, 180, 300, 0, 200, 330, 400, UnitPixel); //결과 출력 
	CE.DrawImage(ClrEff, 200, 100, px * 300, 0, 300, 120, UnitPixel); //clear 애니메이션

	if (px == 4)
	{
		KillTimer(hWnd, 11);
		px = 0;
		//클리어 후 정보들을 초기화//
		BitBlt(CopyDC, 50, 50, 420, 600, CopyClearDC, 0, 0, SRCCOPY);//해당 테트리스 배경을 덮어씌움으로서 블럭들을 없애줌
		TransparentBlt(CopyDC, 50, 50, 420, 600, CopyDC, 50, 50, 420, 600, RGB(0, 0, 0)); //블럭 담는 DC를 hdc에 출력 
		InvalidateRect(hWnd, NULL, FALSE);
		MaxClear++; //활성화 스테이지를 1 늘린다

		Sleep(1000);
		cx = StartX; cy = StartY; //캐릭터 위치를 다시 시작점으로 돌림
		InitBoard();
	}
	px++;
}

void GameOverEf()
{
	static int ypix=0;

	Graphics GO(BackBufDC);
	GO.DrawImage(GameOver, 200, 200, 0, ypix * 120, 300, 120, UnitPixel);
	GO.DrawImage(Result, 180, 300, 0, 300, 330, 100, UnitPixel); //결과 출력 
	ypix++;

	if (ypix == 3)
	{
		_KillTimer();
		BitBlt(CopyDC, 50, 50, 420, 600, CopyClearDC, 0, 0, SRCCOPY);//해당 테트리스 배경을 덮어씌움으로서 블럭들을 없애줌
		InitBoard();
		cx = StartX; cy = StartY; //캐릭터 위치를 다시 시작점으로 돌림
		islose = 0;
		Game_Start = 2; //스테이지 선택창으로 이동
		ypix = 0;
		COUNT = 0;
		KillTimer(hWnd, 12);
	}
	InvalidateRect(hWnd, NULL, FALSE);
}
