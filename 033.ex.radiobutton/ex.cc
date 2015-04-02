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
	WndClass.hbrBackground=(HBRUSH)GetStockObject(LTGRAY_BRUSH);
	//WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
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

#define ID_R1 101
#define ID_R2 102
#define ID_R3 103
#define ID_R4 104
#define ID_R5 105
#define ID_R6 106
HWND r1,r2,r3,r4,r5,r6;
int GRAPH=0;
int COLOR=0;
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH MyBrush, OldBrush;
	switch(iMessage) {
	case WM_CREATE:
		CreateWindow("button","Graph",WS_CHILD | WS_VISIBLE |
			BS_GROUPBOX,5,5,120,110,hWnd,(HMENU)0,g_hInst,NULL);
		CreateWindow("button","Color",WS_CHILD | WS_VISIBLE |
			BS_GROUPBOX,145,5,120,110,hWnd,(HMENU)1,g_hInst,NULL);
		r1=CreateWindow("button","Rectangle",WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON | WS_GROUP,
			10,20,100,30,hWnd,(HMENU)ID_R1,g_hInst,NULL);
		r2=CreateWindow("button","Ellipse",WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON,
			10,50,100,30,hWnd,(HMENU)ID_R2,g_hInst,NULL);
		r3=CreateWindow("button","Line",WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON,
			10,80,100,30,hWnd,(HMENU)ID_R3,g_hInst,NULL);
		r4=CreateWindow("button","Black",WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON | WS_GROUP,
			250,20,100,30,hWnd,(HMENU)ID_R4,g_hInst,NULL);
		r5=CreateWindow("button","Red",WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON,
			150,50,100,30,hWnd,(HMENU)ID_R5,g_hInst,NULL);
		r6=CreateWindow("button","Blue",WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON,
			150,80,100,30,hWnd,(HMENU)ID_R6,g_hInst,NULL);
		CheckRadioButton(hWnd, ID_R1, ID_R3, ID_R1);
		CheckRadioButton(hWnd, ID_R4, ID_R6, ID_R4);
		break;
	case WM_COMMAND:
		if (HIWORD(wParam) == BN_CLICKED) {
			switch (LOWORD(wParam)) {
			case ID_R1:
				GRAPH=0;
				break;
			case ID_R2:
				GRAPH=1;
				break;
			case ID_R3:
				GRAPH=2;
				break;
			case ID_R4:
				COLOR=0;
				break;
			case ID_R5:
				COLOR=1;
				break;
			case ID_R6:
				COLOR=2;
				break;
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		switch (COLOR) {
		case 0:
			MyBrush=CreateSolidBrush(RGB(0,0,0));
			break;
		case 1:
			MyBrush=CreateSolidBrush(RGB(255,0,0));
			break;
		case 2:
			MyBrush=CreateSolidBrush(RGB(0,0,255));
			break;
		}
		OldBrush=(HBRUSH)SelectObject(hdc,MyBrush);
		switch (GRAPH) {
		case 0:
			Rectangle(hdc,10,200,200,300);
			break;
		case 1:
			Ellipse(hdc,10,200,200,300);
			break;
		case 2:
			MoveToEx(hdc,10,200,NULL);
			LineTo(hdc,200,300);
			break;
		}
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
