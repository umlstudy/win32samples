// http://d.hatena.ne.jp/y2q_actionman/20070628/p1
// http://wwwi.tistory.com/72
// http://7ujm.net/C++/Win32%20Dynamic-Link%20Library.html
// http://egloos.zum.com/qufl1999/v/2338204
// http://stackoverflow.com/questions/3460533/why-cant-i-use-declspecdllexport-to-export-dllgetclassobject-from-a-com-d

#ifndef DLLSAMPLE_H_INCLUDED
#define DLLSAMPLE_H_INCLUDED

#ifdef BUILD_DLL
#define EXPORT __declspec(dllexport) __cdecl //__stdcall
#else
#define EXPORT __declspec(dllimport) __cdecl //__stdcall
#endif

//#define EXPORT extern "C" __declspec(dllexport)
//#define EXPORT __declspec(dllexport) __stdcall

// DLL을 로드한 곳에서 EXPORT한 함수명을 쓸수있게 함
#ifdef __cplusplus
extern "C" {
#endif
EXPORT int APlusB(int nA, int nB);
EXPORT int AMinusB(int nA, int nB);
#ifdef __cplusplus
}
#endif

#endif // DLLSAMPLE_H_INCLUDED
