#include <windows.h>
#include <time.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPSTR lpszClass="Timer";

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

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	time_t mytime;
	static HANDLE hTimer;
	static RECT rt={100,100,400,120};
	static char *str;
	switch(iMessage) {
	case WM_CREATE:
		hTimer=(HANDLE)SetTimer(hWnd,1,1000,NULL);
		str="";
		SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;
	case WM_TIMER:
		time(&mytime);
		str=ctime(&mytime);
		InvalidateRect(hWnd,&rt,TRUE);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		TextOut(hdc,100,100,str,strlen(str)-1);
		EndPaint(hWnd,&ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd,1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
