#include <windows.h>
#include <time.h>
#include <stdio.h>

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPSTR lpszClass="Timer Callback";

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;

	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	//WndClass.style=CS_HREDRAW | CS_VREDRAW;
	// 더블클릭허용
	WndClass.style=CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,"My First Program",WS_OVERLAPPEDWINDOW,
		  CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		  NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);

	while(GetMessage(&Message,0,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	HDC hdc;
	int i;
	hdc=GetDC(hWnd);
	for (i=0;i<10000;i++)
		SetPixel(hdc,rand()%500, rand()%400,
		RGB(rand()%256,rand()%256,rand()%256));
	ReleaseDC(hWnd, hdc);
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{

	//OutputDebugStringA("Event Called");
	//http://agebreak.blog.me/60203230209
	printf("WndProc called\n");

	switch(iMessage) {
	case WM_CREATE:
		AllocConsole(); // console
		freopen( "CONOUT$",  "wt", stdout);  // console
		SetTimer(hWnd, 1, 5, (TIMERPROC)TimerProc);
		return 0;
	case WM_TIMER:
		printf("Timer called\n");
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		FreeConsole();  // console
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
