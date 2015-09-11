/*
 * main.c
 *
 *  Created on: 2015. 9. 11.
 *      Author: fffffff
 */


#include <stdio.h>
#include <windows.h>

// DLL���� ȣ���� �Լ��� ��
typedef int (*APlusB)(int, int);
typedef int (*AMinusB)(int, int);

int main()
{
	printf("TEST START\n");
    HINSTANCE    hInst;

    APlusB    fAPlusB;
    AMinusB    fAMinusB;

    // DLL �ε�
    hInst = LoadLibrary("dllSample.dll");

    if(hInst == NULL) {
    	printf("Dll Load Fail\n");
        return 1;
    }
	printf("�Լ�����\n");

	printf("hInst address : %x\n",hInst);
	printf("hInst& address : %x\n",&hInst);
	printf("hInst* address : %x\n",*hInst);

	// ȣ���� �Լ��� ����
    fAPlusB = (APlusB)GetProcAddress(hInst, "APlusB");
    fAMinusB = (AMinusB)GetProcAddress(hInst, "AMinusB");
    printf("address : %x %x\n",fAPlusB, fAMinusB);

    int            nA = 700;
    int            nB = 200;
    int            nRet = 0;
    //int            nRetVal = 0;

	printf("������\n");

    nRet = fAPlusB(nA, nB);
    printf("%d + %d = %d\n",nA, nB, nRet);

    nRet = fAMinusB(nA, nB);
    printf("%d - %d = %d\n",nA, nB, nRet);
    //if(nRet)
    //    printf("%d - %d = %d\n",nA, nB, nRetVal);
    //else
    //    printf("%d < %d \n",nA, nB);

    // DLL ��ε�
    FreeLibrary(hInst);

    return 0;
}
