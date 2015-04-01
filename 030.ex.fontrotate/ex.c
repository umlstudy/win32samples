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
	int i;
	char str[]="                   Beautiful Korea";
	HFONT MyFont, OldFont;
	switch(iMessage) {
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		for (i=0;i<900;i+=100)
		{
			MyFont=CreateFont(50,0,i,0,FW_NORMAL,FALSE,FALSE,FALSE,
				ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,VARIABLE_PITCH | FF_SWISS,
				"Times New Roman");
			OldFont=(HFONT)SelectObject(hdc,MyFont);
			TextOut(hdc,0,450,str,strlen(str));
			SelectObject(hdc,OldFont);
			DeleteObject(MyFont);
		}
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
