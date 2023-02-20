// GraphicEngine.cpp : Defines the entry point for the application.
//

#include "Framework.h"
#include "WindowApp.h"


#define MAX_LOADSTRING 100

// Global Variables:
//HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
   
#ifdef _DEBUG
    LoadStringW(hInstance, IDS_APP_TITLE_DEBUG, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GAMEENGINE_DEBUG, szWindowClass, MAX_LOADSTRING);
#else
    LoadStringW(hInstance, IDS_APP_TITLE_RELEASE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GAMEENGINE_RELEASE, szWindowClass, MAX_LOADSTRING);
#endif // _DEBUG
    HWND hWnd{};
    FLOAT dpiX, dpiY;
    MyRegisterClass(hInstance);
    SetProcessDPIAware();
    HDC screen = GetDC(0);
    dpiX = static_cast<FLOAT>(GetDeviceCaps(screen, LOGPIXELSX));
    dpiY = static_cast<FLOAT>(GetDeviceCaps(screen, LOGPIXELSY));
    ReleaseDC(0, screen);
    int width = (int)(Framework::get()->getScreenWidth());
    int height = (int)(Framework::get()->getScreenHeight());
    //UINT dpi = GetDpiForSystem();

    hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME | WS_VISIBLE,
        0, 0, width, height, nullptr, nullptr, hInstance, nullptr);
    //SetWindowPos(hWnd, NULL, 0, 0, (int)(dpiX * framework.getScreenWidth() / 96), (int)(dpiY * framework.getScreenHeight() / 96), SWP_NOZORDER | SWP_NOMOVE);
    
    ShowWindow(hWnd, nCmdShow);
    {
        LONG lStyle = GetWindowLong(hWnd, GWL_STYLE);
        lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
        SetWindowLong(hWnd, GWL_STYLE, lStyle);
    }
    
    HACCEL hAccelTable;
#ifdef _DEBUG
    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAMEENGINE_DEBUG));
#else
    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAMEENGINE_RELEASE));
#endif // _DEBUG
   
    int q = Framework::get()->GameRun();;
    delete Framework::get();
    return q;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    LPCWSTR name;
#ifdef _DEBUG
    name = MAKEINTRESOURCEW(IDC_GAMEENGINE_DEBUG);
#else
    name = MAKEINTRESOURCEW(IDC_GAMEENGINE_RELEASE);
#endif // _DEBUG
    wcex.lpszMenuName   = name;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    
    return Framework::get()->WndProc(hWnd, message, wParam, lParam);
}