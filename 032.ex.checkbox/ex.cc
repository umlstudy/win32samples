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

#include "MessageToString.hpp"
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static HWND c1,c2,c3,c4;
	static BOOL ELLIPSE = FALSE;
	CWindowsMessageToString msgConverter;
	LPSTR lpszMsg = msgConverter.GetStringFromMsg( WM_COMMAND );
	printf("%s\n", lpszMsg );


	switch(iMessage) {
	case WM_CREATE:
		c1=CreateWindow("button","Draw Ellipse?",WS_CHILD | WS_VISIBLE |
			BS_CHECKBOX,20,20,160,25,hWnd,(HMENU)0,g_hInst,NULL);
		c2=CreateWindow("button","Good bye Message?",WS_CHILD | WS_VISIBLE |
			BS_AUTOCHECKBOX,20,50,160,25,hWnd,(HMENU)1,g_hInst,NULL);
		c3=CreateWindow("button","3State",WS_CHILD | WS_VISIBLE | BS_3STATE,
			20,80,160,25,hWnd,(HMENU)2,g_hInst,NULL);
		c4=CreateWindow("button","Auto 3State",WS_CHILD | WS_VISIBLE |
			BS_AUTO3STATE,20,110,160,25,hWnd,(HMENU)3,g_hInst,NULL);
		return 0;
	case WM_COMMAND:
		switch(LOWORD(wParam)) {
		case 0:
			if (SendMessage(c1,BM_GETCHECK,0,0)==BST_UNCHECKED) {
				SendMessage(c1,BM_SETCHECK,BST_CHECKED,0);
				ELLIPSE = TRUE;
			}
			else {
				SendMessage(c1,BM_SETCHECK,BST_UNCHECKED,0);
				ELLIPSE = FALSE;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 2:
			if (SendMessage(c3,BM_GETCHECK,0,0)==BST_UNCHECKED)
				SendMessage(c3,BM_SETCHECK,BST_CHECKED,0);
			else
			if (SendMessage(c3,BM_GETCHECK,0,0)==BST_INDETERMINATE)
				SendMessage(c3,BM_SETCHECK,BST_UNCHECKED,0);
			else
				SendMessage(c3,BM_SETCHECK,BST_INDETERMINATE,0);
			break;
		}
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		if (ELLIPSE == TRUE)
			Ellipse(hdc,200,100,400,200);
		else
			Rectangle(hdc,200,100,400,200);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		if (SendMessage(c2,BM_GETCHECK,0,0)==BST_CHECKED)
			MessageBox(hWnd,"Good bye","Check",MB_OK);
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
