//#include <stdio.h>
//#include <wincon.h>
//#include <windef.h>
//#include <wingdi.h>
//#include <winnt.h>
//#include <winuser.h>
#include <windows.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
extern LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
extern int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpszCmdParam,int nCmdShow);
extern LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam);
#ifdef __cplusplus
}
#endif

HINSTANCE g_hInst;
LPSTR lpszClass="CHECKBOX";

#define IDR_MENU1 10000
#define IDM_FILE 10001
#define IDM_MENU1 10002
#define IDM_MENU2 10003
#define IDM_EXIT 10004
#define IDC_DUCK 100
#define IDR_ACCEL1 1
#define IDS_STRING1 50000
#define IDB_BITMAP1 101

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;

	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
//	WndClass.hbrBackground=(HBRUSH)GetStockObject(LTGRAY_BRUSH);
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	//WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hCursor=LoadCursor(hInstance,MAKEINTRESOURCE(IDC_DUCK));
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	printf("wndclass created.\n");

	AllocConsole(); // console
	freopen( "CONOUT$",  "wt", stdout);  // console

	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,
		  CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		  NULL,(HMENU)NULL,hInstance,NULL);
	printf("window created.\n");

	ShowWindow(hWnd,nCmdShow);
	printf("window showed.\n");

	HACCEL hAccel;
	hAccel=LoadAccelerators(hInstance,MAKEINTRESOURCE(IDR_ACCEL1));
	printf("accel loaded.\n");

	while(GetMessage(&Message,0,0,0)) {
		if (!TranslateAccelerator(hWnd,hAccel,&Message)) {
				TranslateMessage(&Message);
				DispatchMessage(&Message);
		}
//		TranslateMessage(&Message);
//		DispatchMessage(&Message);
	}
	FreeConsole();  // console

	return Message.wParam;
}

#define ID_SCRRED 100
#define ID_SCRGREEN 101
#define ID_SCRBLUE 102
HWND hRed,hGreen,hBlue;
int Red,Green,Blue;

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH MyBrush, OldBrush;
	int TempPos;
	switch(iMessage) {
	case WM_CREATE:
		hRed=CreateWindow("scrollbar",NULL,WS_CHILD | WS_VISIBLE | SBS_HORZ,
			10,10,200,20,hWnd,(HMENU)ID_SCRRED,g_hInst,NULL);
		hGreen=CreateWindow("scrollbar",NULL,WS_CHILD | WS_VISIBLE | SBS_HORZ,
			10,40,200,20,hWnd,(HMENU)ID_SCRGREEN,g_hInst,NULL);
		hBlue=CreateWindow("scrollbar",NULL,WS_CHILD | WS_VISIBLE | SBS_HORZ,
			10,70,200,20,hWnd,(HMENU)ID_SCRBLUE,g_hInst,NULL);
		SetScrollRange(hRed,SB_CTL,0,255,TRUE);
		SetScrollPos(hRed,SB_CTL,0,TRUE);
		SetScrollRange(hGreen,SB_CTL,0,255,TRUE);
		SetScrollPos(hGreen,SB_CTL,0,TRUE);
		SetScrollRange(hBlue,SB_CTL,0,255,TRUE);
		SetScrollPos(hBlue,SB_CTL,0,TRUE);
		return 0;
	case WM_HSCROLL:
		if ((HWND)lParam == hRed) TempPos = Red;
		if ((HWND)lParam == hGreen) TempPos = Green;
		if ((HWND)lParam == hBlue) TempPos = Blue;
		switch (LOWORD(wParam)) {
		case SB_LINELEFT:
			TempPos=max(0,TempPos-1);
			break;
		case SB_LINERIGHT:
			TempPos=min(255,TempPos+1);
			break;
		case SB_PAGELEFT:
			TempPos=max(0,TempPos-10);
			break;
		case SB_PAGERIGHT:
			TempPos=min(255,TempPos+10);
			break;
		case SB_THUMBTRACK:
			TempPos=HIWORD(wParam);
			break;
		}
		if ((HWND)lParam == hRed) Red=TempPos;
		if ((HWND)lParam == hGreen) Green=TempPos;
		if ((HWND)lParam == hBlue) Blue=TempPos;
		SetScrollPos((HWND)lParam,SB_CTL,TempPos,TRUE);
		InvalidateRect(hWnd,NULL,FALSE);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		MyBrush=CreateSolidBrush(RGB(Red,Green,Blue));
		OldBrush=(HBRUSH)SelectObject(hdc,MyBrush);
		Rectangle(hdc,10,100,210,200);
		SelectObject(hdc,OldBrush);
		DeleteObject(MyBrush);
		EndPaint(hWnd,&ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

/*
 *
 * 	case WM_COMMAND:
	switch(LOWORD(wParam) {		// ID에 따른 분기
	case 메뉴1:처리1;break;
	case 메뉴2:처리2;break;
	case 액셀러레이터1:처리3;break;
	case 컨트롤1:
		switch(HIWORD(wParam)) {	// 통지 코드에 따른 분기
		case 통지코드1:처리1;break;
		case 통지코드2:처리2;break;
		...........
		}
		break;
	}
	return 0;
*/
