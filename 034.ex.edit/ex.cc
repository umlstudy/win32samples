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

// 에디트는 최대 32k까지의 문자열을 편집할 수 있으며 여러줄 편집, 블럭선택, 클립보드 지원 기능까지 다양한 기능을 가지고 있는데 비해 사용하기는 비교적 쉬운편에 속한다. 14장에서 에디트에 대한 상세한 프로그래밍 방법을 익혀 보도록 하자.
// 컨트롤이 윈도우라는 결정적인 증거는 스스로 메시지를 처리할 수 있는 능력이 있다는 점이다.
#define ID_EDIT 100
HWND hEdit;
char str[128];
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	switch(iMessage) {
	case WM_CREATE:
		hEdit=CreateWindow("edit",NULL,WS_CHILD | WS_VISIBLE | WS_BORDER |
		ES_AUTOHSCROLL,10,10,200,25,hWnd,(HMENU)ID_EDIT,g_hInst,NULL);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_EDIT:
			switch (HIWORD(wParam)) {
			case EN_CHANGE:
				GetWindowText(hEdit,str,128);
				SetWindowText(hWnd,str);
			}
		}
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
