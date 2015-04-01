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
    wc.cbSize = sizeof(wc);               // 構造体サイズ
    wc.style = CS_HREDRAW | CS_VREDRAW;   // スタイル
    wc.lpfnWndProc = WndProc;             // ウィンドウプロシージャ
    wc.cbClsExtra = 0;                    // 拡張情報１
    wc.cbWndExtra = 0;                    // 拡張情報２
    wc.hInstance = hInst;                 // インスタンスハンドル
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // アイコン
    wc.hIconSm = wc.hIcon;                // 子アイコン
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // マスカーソル
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // ウィンドウ背景
    wc.lpszMenuName = NULL;               // メニュー名
    wc.lpszClassName = "fooWindowClass";  // ウィンドウクラス名

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
    static HMENU hMenu;
    int wmId;

    switch(msg) {
    case WM_CREATE:   // ウィンドウが作成されたら
        hMenu = LoadMenu(NULL, "WIN_MENU"); // メニューリソースをロード
        SetMenu(hWnd, hMenu);               // ウィンドウにメニューリソース割り当て
        return 0;

    case WM_COMMAND:  // メニューが選択されたら
        wmId = LOWORD(wp);
        switch (wmId) {
        case 40001: MessageBox(NULL, "開く", "メッセージ", MB_OK);
            break;
        case 40002: MessageBox(NULL, "保存", "メッセージ", MB_OK);
            break;
        case 40003: DestroyWindow(hWnd); // 終了
            break;
        case 40004: MessageBox(NULL, "切り取り", "メッセージ", MB_OK);
            break;
        case 40005: MessageBox(NULL, "コピー", "メッセージ", MB_OK);
            break;
        case 40006: MessageBox(NULL, "貼\\り付け", "メッセージ", MB_OK);
            break;
        case 40007: MessageBox(NULL, "ツールバー", "メッセージ", MB_OK);
            break;
        case 40008: MessageBox(NULL, "イ", "メッセージ", MB_OK);
            break;
        case 40009: MessageBox(NULL, "ロ", "メッセージ", MB_OK);
            break;
        case 40010: MessageBox(NULL, "ハ", "メッセージ", MB_OK);
            break;
        case 40011: MessageBox(NULL, "ソ\\ース", "メッセージ", MB_OK);
            break;
        case 40012: MessageBox(NULL, "ヘルプ", "メッセージ", MB_OK);
            break;
        case 40013: MessageBox(NULL, "ver1.00", "バージョン情報", MB_OK);
            break;
        }
        break;

    case WM_CLOSE:    // ウィンドウが閉じられるとき
        SetMenu(hWnd, NULL);  // ウィンドウからメニュー削除
        DestroyMenu(hMenu);   // メニューバーリソース破棄
        hMenu = NULL;
        break;                // ウィンドウを閉じる処理はDefWindowProc()に任せる

    case WM_DESTROY:  // ウィンドウが破棄されたら
        PostQuitMessage(0);
        return 0;
    }

    // 他のメッセージはデフォルトの処理を行う
    return DefWindowProc(hWnd, msg, wp, lp);
}
