#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPSTR lpszClass="Menu";

#define IDR_MENU1 10000
#define IDM_FILE 10001
#define IDM_MENU1 10002
#define IDM_MENU2 10003
#define IDM_EXIT 10004
#define IDC_DUCK 100
#define IDR_ACCEL1 1
#define IDS_STRING1 50000

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
	//WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hCursor=LoadCursor(hInstance,MAKEINTRESOURCE(IDC_DUCK));
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	AllocConsole(); // console
	freopen( "CONOUT$",  "wt", stdout);  // console

	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,
		  CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		  NULL,(HMENU)NULL,hInstance,NULL);

	ShowWindow(hWnd,nCmdShow);

	HACCEL hAccel;
	hAccel=LoadAccelerators(hInstance,MAKEINTRESOURCE(IDR_ACCEL1));

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

/*
프로그램 실행중에 사용자가 메뉴 항목을 선택하면 WM_COMMAND 메시지가 발생한다. 이때 어떤 메뉴 항목이 선택되었는가는 wParam의 하위 워드로 전달되므로 LOWORD(wParam)을 읽어 판단할 수 있다. 그래서 Menu.cpp의 WndProc에서는 WM_COMMAND 메시지를 받을 경우 switch문으로 다시 LOWORD(wParam)의 값에 따라 분기를 하여 각 메뉴 항목에 따른 처리를 수행한다. DI_FILE_MENU1메뉴 항목(Menu1)이 선택되었을 경우 메시지 박스를 열어 메뉴 항목이 선택되었음을 알려주고 ID_FILE_EXIT메뉴 항목(Exit)이 선택되었을 경우 프로그램을 종료하도록 하였다. 메뉴 항목이 더 늘어난다면 WM_COMMAND의 switch문안에 case만 계속 늘려주면 된다.
WM_COMMAND 메시지는 메뉴 항목을 선택할 때 뿐만 아니라 액셀러레이터를 누를 때도 발생하며 또한 버튼, 에디트 박스 등의 컨트롤이 부모 윈도우로 통지 메시지를 보낼 때도 발생한다. 이 메시지의 추가 정보는 다음과 같은 구조를 가진다
 */
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
 {
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH MyBrush, OldBrush;
	switch (iMessage) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		MyBrush = (HBRUSH) GetStockObject(GRAY_BRUSH);
		OldBrush = (HBRUSH) SelectObject(hdc, MyBrush);
		Rectangle(hdc, 50, 50, 300, 200);
		SelectObject(hdc, OldBrush);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
