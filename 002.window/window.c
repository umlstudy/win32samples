#include <windows.h>

// プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);


// エントリポイント
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR pCmdLine, int showCmd)
{
    WNDCLASSEX wc;  // ウィンドウクラス構造体
    HWND hWnd;      // ウィンドウハンドル
    MSG msg;        // メッセージ構造体

    // ウィンドウクラス情報を設定(構造体)
    wc.cbSize = sizeof(wc);                     // 構造体サイズ
    wc.style = CS_HREDRAW | CS_VREDRAW;         // スタイル
    wc.lpfnWndProc = WndProc;                   // ウィンドウプロシージャ
    wc.cbClsExtra = 0;                          // 拡張情報１
    wc.cbWndExtra = 0;                          // 拡張情報２
    wc.hInstance = hInst;                       // インスタンスハンドル
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // アイコン
    wc.hIconSm = wc.hIcon;                      // 子アイコン
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);   // マスカーソル
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // ウィンドウ背景
    wc.lpszMenuName = NULL;                     // メニュー名
    wc.lpszClassName = "fooWindowClass";        // ウィンドウクラス名

    // ウィンドウクラスの登録
    if(RegisterClassEx(&wc) == 0){ return 1; }

    // ウィンドウを作成
    hWnd = CreateWindow(
        wc.lpszClassName,      // ウィンドウクラス名
        "Sample Window",       // タイトルバーに表示する文字列
        WS_OVERLAPPEDWINDOW,   // ウィンドウの種類
        CW_USEDEFAULT,         // ウィンドウを表示するX座標
        CW_USEDEFAULT,         // ウィンドウを表示するY座標
        CW_USEDEFAULT,         // ウィンドウ幅
        CW_USEDEFAULT,         // ウィンドウ高さ
        NULL,                  // 親ウィンドウのウィンドウハンドル
        NULL,                  // メニューハンドル
        hInst,                 // インスタンスハンドル
        NULL                   // その他の作成データ
    );
    if(hWnd == NULL){ return 1; }

    // ウィンドウを表示
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    // メッセージループ
    while(1) {
        BOOL ret = GetMessage(&msg, NULL, 0, 0);  // メッセージを取得する
        if(ret == 0 || ret == -1) { // アプリケーション終了またはGetMessage()失敗なら
            break;
        } else {
            // メッセージを処理する
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 0;
}

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch(msg) {
    case WM_DESTROY:  // ウィンドウが破棄されたら
        PostQuitMessage(0);
        return 0;
    }

    // 他のメッセージはデフォルトの処理を行う
    return DefWindowProc(hWnd, msg, wp, lp);
}
