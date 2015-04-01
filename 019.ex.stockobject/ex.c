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
���α׷� �����߿� ����ڰ� �޴� �׸��� �����ϸ� WM_COMMAND �޽����� �߻��Ѵ�. �̶� � �޴� �׸��� ���õǾ��°��� wParam�� ���� ����� ���޵ǹǷ� LOWORD(wParam)�� �о� �Ǵ��� �� �ִ�. �׷��� Menu.cpp�� WndProc������ WM_COMMAND �޽����� ���� ��� switch������ �ٽ� LOWORD(wParam)�� ���� ���� �б⸦ �Ͽ� �� �޴� �׸� ���� ó���� �����Ѵ�. DI_FILE_MENU1�޴� �׸�(Menu1)�� ���õǾ��� ��� �޽��� �ڽ��� ���� �޴� �׸��� ���õǾ����� �˷��ְ� ID_FILE_EXIT�޴� �׸�(Exit)�� ���õǾ��� ��� ���α׷��� �����ϵ��� �Ͽ���. �޴� �׸��� �� �þ�ٸ� WM_COMMAND�� switch���ȿ� case�� ��� �÷��ָ� �ȴ�.
WM_COMMAND �޽����� �޴� �׸��� ������ �� �Ӹ� �ƴ϶� �׼��������͸� ���� ���� �߻��ϸ� ���� ��ư, ����Ʈ �ڽ� ���� ��Ʈ���� �θ� ������� ���� �޽����� ���� ���� �߻��Ѵ�. �� �޽����� �߰� ������ ������ ���� ������ ������
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
