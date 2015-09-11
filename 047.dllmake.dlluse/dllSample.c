#include "dllSample.h"

#include <windows.h>
#include <stdio.h>


BOOL APIENTRY DllMain(HANDLE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved)
{
    return TRUE;
}

EXPORT int APlusB(int nA, int nB)
{
    return nA + nB;
}

EXPORT int AMinusB(int nA, int nB)
{
	return nA - nB;
}
