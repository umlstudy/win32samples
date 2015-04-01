#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPSTR lpszClass="GDIOBJ";

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
	HPEN MyPen, OldPen;
	HBRUSH MyBrush,OldBrush;
	switch(iMessage) {
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		MyBrush=CreateHatchBrush(HS_BDIAGONAL, RGB(255,255,0));
		OldBrush=(HBRUSH)SelectObject(hdc,MyBrush);
		MyPen = CreatePen(PS_SOLID, 5, RGB(0,0,255));
		OldPen = (HPEN)SelectObject(hdc, MyPen);
		Rectangle(hdc,50,50,300,200);
		SelectObject(hdc, OldPen);
		// 삭제하고자 하는 GDI 오브젝트의 핸들만 인수로 넘겨주면 된다. 단, 이때 주의할 것은 DC에 현재 선택되어 있는 GDI 오브젝트는 삭제할 수 없다는 점이다. 현재 사용되고 있는 객체를 함부로 삭제하도록 내버려 둘 수는 없기 때문에 생긴 일종의 안전 장치 역할을 하는 규정이다. 그래서 삭제를 하기 전에 먼저 DC에 선택된 객체를 선택 해제해 주어야 하는데 선택을 해제시켜주는 별도의 함수는 제공되지 않으므로 다른 GDI 오브젝트를 선택해 주는 방법을 사용한다. 이런 이유로 OldPen이라는 핸들을 만든 후 이 핸들에 MyPen이 선택되기 전의 펜 핸들을 저장해 두고 MyPen을 삭제하기 전에 OldPen을 다시 선택해 주는 것이다.
		// SelectObject가 이전 핸들값을 리턴해 주므로 OldPen을 선택함과 동시에 리턴되어져 나오는 MyPen을 삭제하는 것이다. 이때 사용되는 OldPen은 이전에 선택되어 있던 펜을 보존한다기보다는 단순히 MyPen을 선택해제하기 위한 용도로 사용된 것이다. GDI 오브젝트를 만들고 사용하는 일반적인 절차는 다음과 같다.
		DeleteObject(MyPen);
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
