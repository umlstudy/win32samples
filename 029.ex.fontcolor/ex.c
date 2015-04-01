#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPSTR lpszClass="FONT";

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

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HFONT font, oldfont;
	char str[]="ÆùÆ® Test 1234";
	HBRUSH MyBrush, OldBrush;
	switch(iMessage) {
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		MyBrush=CreateHatchBrush(HS_CROSS,RGB(0,0,255));
		OldBrush=(HBRUSH)SelectObject(hdc,MyBrush);
		Rectangle(hdc,50,50,400,200);
		SelectObject(hdc,OldBrush);

		font=CreateFont(30,0,0,0,0,0,0,0,HANGEUL_CHARSET,0,0,0,0,"±Ã¼­");
		oldfont=(HFONT)SelectObject(hdc,font);
		SetTextColor(hdc,RGB(255,0,0));
		SetBkColor(hdc,RGB(255,255,0));
		TextOut(hdc, 100,100,str,strlen(str));
		SetBkMode(hdc,TRANSPARENT);
		TextOut(hdc, 100, 150,str,strlen(str));

		SelectObject(hdc,oldfont);
		DeleteObject(MyBrush);
		DeleteObject(font);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
