// Shtet3
// Win32 API������ ���� ��Ʈ����

#include <windows.h>
#include <stdlib.h>
//#include "resource.h"

// ���� �������� ���� ������ ���� ��ũ�ι�
#define random(n) (rand()%n)

// �Լ� ���� ����
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
void brick(int flag);
void leftmove();     
void rightmove();    
int downmove();
void rotate();
int whataround(int,int);
void isfull();
void printstage();
void makenewblock();
void drawscreen();
void printscore();
void drawnextbrick();

// �� ������ ���� �迭. �� ������ 8����Ʈ���̸� ȸ�� ����� ������ ����  
// ������ �������� ������ �ٸ���. �� ���� �߽��������� ������� �Ÿ��̴�   
int pat[7][32]={
  {0,0,1,0,2,0,-1,0,0,0,0,1,0,-1,0,-2,},
  {0,0,1,0,0,1,1,1,},
  {0,0,-1,0,0,-1,1,-1,0,0,0,1,-1,0,-1,-1,},
  {0,0,-1,-1,0,-1,1,0,0,0,-1,0,-1,1,0,-1,},
  {0,0,0,-1,1,0,2,0,0,0,-1,0,0,-1,0,-2,0,0,-1,0,- 2,0,0,1,0,0,1,0,0,1,0,2},
  {0,0,-1,0,-2,0,0,-1,0,0,-1,0,0,1,0,2,0,0,0,1,1,0,2,0,0,0,1,0,0,-1,0,-2},
  {0,0,-1,0,1,0,0,1,0,0,0,-1,0,1,1,0,0,0,-1,0,1,0,0,-1,0,0,-1,0,0,-1,0,1}
   };
int brickpatnum[7]={2,1,2,2,4,4,4};  // �� ������ ���� ���� 
int tet[14][23];         // ������ �迭 
int i,j,k;               // �ٸ��� �ӽ� ����, �ַ� ���� ��� ��� 
int score;               // ����  
int speed;               // �ӵ�
char imsistr[128];       // ���ڿ� ����� ���� �ӽ� ���� 
int nowbrick,nowrot;     // ���� ���õ� ������ ȸ�� ��� 
int nextbrick;           // ���� ��µ� ����             
int nowx,nowy;           // ������ ��ġ ȭ�� ��ǥ���̴�. 
BOOL GameStart;			 // ���� ���� ���� ��?

HDC hDC,hMemDC,hMemDC2;
HBITMAP hbrick,hbrick2;
HINSTANCE g_hInst;
HWND hWnd;

//######################################################
// ���� ��ƾ, �����츦 �����ϸ� �޽��� ������ �����Ų��. 
//######################################################
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
{
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;

	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor=LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon=LoadIcon(g_hInst,MAKEINTRESOURCE(IDI_ICON1));
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName="Shtet3";
	WndClass.lpszMenuName=MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd=CreateWindow("Shtet3","Sh tetris 3",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		50,50,470,460, NULL,NULL,g_hInst,NULL);
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	while(GetMessage(&Message,0,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

//######################################################
// �޽��� ó�� ��ƾ 
//######################################################
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	static FARPROC lpfnAboutDlgProc;
	PAINTSTRUCT ps;
	switch(iMessage) {
	// �����찡 ó�� ������� �� �������� �޽����̴�.
	// �� �޽��� ó�� ��ƾ���� �ַ� ���α׷� �ʱ�ȭ�� �����ϸ� ������
	// ���� �غ� �Ѵ�. ���⼭�� �޸� DC�� ����� �ΰ��� ��Ʈ����
	// �̸� �о�д�.
	case WM_CREATE:
		hDC=GetDC(hWnd);
		hMemDC=CreateCompatibleDC(hDC);
		hMemDC2=CreateCompatibleDC(hDC);
		ReleaseDC(hWnd,hDC);
		hbrick=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BRICK));      // ���� ��� 
		SelectObject(hMemDC,hbrick);
		hbrick2=LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BLANK));     // ������ ����� ���� ���� 
		SelectObject(hMemDC2,hbrick2);
		GameStart=FALSE;
		return 0;
	// Ű���� �̺�Ʈ ó��. �����¿� Ű�� ���� ������ �����̴� �Լ���
	// ȣ���Ѵ�. 
	case WM_KEYDOWN:
		switch(wParam) {
		case VK_LEFT:
			leftmove();
			break;
		case VK_RIGHT:
			rightmove();
			break;
		case VK_UP:
			rotate();
			break;
		case VK_DOWN:
			while(downmove());
			makenewblock();
			break;
		}
		return 0;
	// Ÿ�̸� �̺�Ʈ�� �߻��� ������ ������ ��ĭ�� �Ʒ��� ������.
	// Ÿ�̸� �̺�Ʈ�� �����ϰ� �߻��ϹǷ� ������ �ӵ��� �׻� ����
	// �ϰ� ������ų �� �ִ�.  
	case WM_TIMER:
		if (downmove()==0) makenewblock();
		return 0;
	// ȭ���� �ٽ� �׷��� �� ��� ��ü ȭ���� �׸��� ���� �̵�����
	// ������ ������ �ٽ� �׸���. 
	case WM_PAINT:
		hDC=BeginPaint(hWnd,&ps);
		EndPaint(hWnd,&ps);         // �۾� ������ ��ȿȭ��Ų��.
		drawscreen();               // ȭ���� �ٽ� �׸��� �Լ�
		if (GameStart)
			brick(1);       // �̵����� ���� �׸�
		return 0;
	// �޴� �׸��� ���õ� �� �߻��ϴ� �޽����̴�.
	// Start �׸��� ���õǸ� �迭�� ������ �ʱ�ȭ�ϰ� Ÿ�̸Ӹ� ����
	// �Ͽ� ������ �����Ѵ�. 
	case WM_COMMAND:
		switch (wParam)	{
		case ID_START:
			for (i=0;i<23;i++)for(j=0;j<14;j++)     // �迭�� �ʱ�ȭ�Ѵ�.
			if (i==21 || j==0 || j==13) 
				tet[j][i]=2;  
			else 
				tet[j][i]=0;
			speed=500;
			score=0;
			SetTimer(hWnd,1,speed,NULL);
			nextbrick=random(7);
			makenewblock();
			EnableMenuItem(GetMenu(hWnd),ID_START,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
			GameStart=TRUE;
			InvalidateRect(hWnd,NULL,TRUE);
			UpdateWindow(hWnd);
			break;
		}
		return 0;
	// �����찡 �ı��� �� �������� �޽����̴�. �����ߴ� DC�� ��� �����ϰ�
	// Ÿ�̸Ӹ� ������Ű�� GDI������Ʈ�� �����Ѵ�.
	case WM_DESTROY:
		DeleteDC(hMemDC);
		DeleteDC(hMemDC2);
		KillTimer(hWnd,1);
		DeleteObject(hbrick);
		DeleteObject(hbrick2);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

//######################################################
// ���⼭���� �Ϲ� �Լ���
// ����ϴ� ���� shtet1�� �����ϴ�. 
//######################################################

// ���ο� ���� �����. ���� �Ѵܰ� �տ� ����� nextbrick
// ������ ������ �ΰ� ���� ���� ���� ����� ȭ�� ���ϴܿ�
// ����� �ش�. 
void makenewblock()
{
	nowbrick=nextbrick;
	nextbrick=random(7);
	nowx=8;
	nowy=3;
	nowrot=0;    // ���� �ʱ�ȭ
	brick(1);
	drawnextbrick();
	// ������ ������ ��ġ�� �̹� ������ ������ ������ ������.
	// ������ ���� ���� �ݵ�� Ÿ�̸Ӹ� ���� �־�� �Ѵ�.
	if (whataround(nowx,nowy)!=0) {
		KillTimer(hWnd,1);
		GameStart=FALSE;
		if (MessageBox(hWnd,"������ ������!\r\n����ִµ� �� �ҷ�?"
		,"������ ��Ʈ����",MB_YESNO | MB_ICONHAND)==IDYES)
			SendMessage(hWnd,WM_COMMAND,ID_START,NULL);
		else 
			EnableMenuItem(GetMenu(hWnd),ID_START,MF_BYCOMMAND | MF_ENABLED);
	}
}

// WM_PAINT �޽��� ó�� ��ƾ���� ȣ���ϴ� �Լ�
// ȭ���� �ٽ� �׸���. 
void drawscreen()
{
	HDC c;
	hDC=GetDC(hWnd);
	Rectangle(hDC,8,8,252,412);
	Rectangle(hDC,260,8,460,150);
	TextOut(hDC,320,20,"Shtet 3",7);

	printscore();

	// �迭���� ������ �о �������� ����� �ش�.
	Rectangle(hDC,260,300,460,412);
	for (i=1;i<=20;i++)
		for (j=1;j<=12;j++)	{
			if (tet[j][i]==1) 
				c=hMemDC; 
			else 
				c=hMemDC2;
			BitBlt(hDC,(j-1)*20+10,(i-1)*20+10,
			20,20,c,0,0,SRCCOPY);
		}
	ReleaseDC(hWnd, hDC);
	drawnextbrick();
}

void drawnextbrick()
{
	hDC=GetDC(hWnd);
	RECT rect={261,301,459,399};
	FillRect(hDC,&rect,(HBRUSH)GetStockObject(WHITE_BRUSH));
	for (i=0;i<4;i++){             // ���� �迭�� �о� ȭ�鿡 �׸� 
		BitBlt(hDC,(17+pat[nextbrick][i*2]-1)*20,
		(18+pat[nextbrick][i*2+1]-1)*20,
		20,20,hMemDC,0,0,SRCCOPY);
	}
	ReleaseDC(hWnd, hDC);
}

// ������ ����Ѵ�.
void printscore()
{
	wsprintf(imsistr,"���� : %d",score);
	TextOut(hDC,260,200,imsistr,strlen(imsistr));
}

// ������ ����ϰų� �����Ѵ�.
void brick(int flag)
{
	HDC c;
	hDC=GetDC(hWnd);
	// flag���� ���� ���� ������ ������ ����Ѵ�.
	if (flag==0) 
		c=hMemDC2; 
	else 
		c=hMemDC; 
	for (i=0;i<4;i++) {             // ���� �迭�� �о� ȭ�鿡 �׸�
		BitBlt(hDC,(nowx+pat[nowbrick][nowrot*8+i*2]-1)*20+10,
		(nowy+pat[nowbrick][nowrot*8+i*2+1]-1)*20+10,20,20,c,0,0,SRCCOPY);
	}
	ReleaseDC(hWnd,hDC);
}

// ������ �� ĭ �Ʒ��� ����߸�. �� �������� �������� 1�� ����,  
// �ٴ��̳� ���� ������ �ε�ġ�� ���� ���� �� 0�� �����Ͽ�      
// ���ο� ������ ���鵵�� �Ѵ�.                                   
int downmove()
{
	if (whataround(nowx,nowy+1)!=0) {
		isfull();
		return 0;
	}
	brick(0);     // ���� �ڸ� ����� �� ĭ �ؿ� �ٽ� �׸�
	nowy++;
	brick(1);
	return 1;
}

// ���� �̵�. ������ ���̸� �̵����� �ʴ´�. 
void leftmove()
{
	if (whataround(nowx-1,nowy)!=0)
		return;
	brick(0);
	nowx-=1;
	brick(1);
}

 // ���� �̵�. ������ ���̸� �̵����� �ʴ´�. 
void rightmove()
{
	if (whataround(nowx+1,nowy)!=0)
		return;
	brick(0);
	nowx+=1;
	brick(1);
}

// ȸ��. ȸ���� �� ���� �����̸� ȸ������ �ʴ´� 
void rotate()
{
	int imsi,imsi2;
	imsi=nowrot;
	nowrot++;
	if (nowrot==brickpatnum[nowbrick]) 
		nowrot=0;
	if (whataround(nowx,nowy)!=0) {
		nowrot=imsi;
		return;
	}
	imsi2=nowrot;
	nowrot=imsi;
	brick(0);
	nowrot=imsi2;
	brick(1);
}

// �ֺ��� ������ �ִ��� �Ǻ����ش�. �μ�(x,y)�� �迭���� ��ǥ�̴�. 
// �� �����̸� 0, ���� ������ �ε�ġ�� 1, ���� �ε�ġ�� 2�� �����Ѵ�. 
int whataround(int x,int y)
{
	k=0;
	for (i=0;i<4;i++) {
		j=tet[x+pat[nowbrick][nowrot*8+i*2]]
			[y+pat[nowbrick][nowrot*8+i*2+1]];
		if (j>k) k=j;
	}
	return k;
}

// ������ �ٴڿ� ����� ���� ó��. ��ü �迭�� �˻��ؼ� �� ������  
// �� ���� �������ش�.                                             
void isfull()
{
	int check,check2;
	score++;
	printscore();
	for (i=0;i<4;i++)       // �迭�� ���� ������ ������ ��� 
		tet[nowx+pat[nowbrick][nowrot*8+i*2]]
		[nowy+pat[nowbrick][nowrot*8+i*2+1]]=1;
	check2=0;
	for (i=20;i>=0;i--) {     // �� ������ �� á���� �˻� 
		check=0;
		for (j=1;j<13;j++)
			if (tet[j][i]==0) check=1;
		if (check==0) {             // �� �� ������ �߰ߵǸ� �����Ѵ�.  
			check2=1;                // ���� ������ �Ʒ��� �������ش�.   
			for (k=i-1;k>0;k--)      // �� ������ �ٽ� �˻��ϱ� ���� i�� 
				for (j=1;j<13;j++)       // �� �ڸ��� ���� �ξ�� �Ѵ�.      
					tet[j][k+1]=tet[j][k];
			i++;
		}
	}

	if (check2==0) return;     // �� ���ε� ������ �������� ����  
	score+=10;
	KillTimer(hWnd,1);
	speed-=10;
	if (speed<100) speed=100;
	SetTimer(hWnd,1,speed,NULL);
	drawscreen();
}
