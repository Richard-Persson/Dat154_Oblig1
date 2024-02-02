// Oblig1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Oblig1.h"
#define ID_TIMER_TRAFFIC_LIGHT 1

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_OBLIG1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OBLIG1));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OBLIG1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_OBLIG1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static POINT position = { 500,500 }; 
    static int state = 0;
    static int top = 165;
    static int bottom = top + 50;
    static int left = 150;
    static int right = left-150;
    
    static HBRUSH topBrush = CreateSolidBrush(RGB(255, 0, 0));
    static HBRUSH middleBrush = CreateSolidBrush(RGB(128, 128, 128));
    static HBRUSH bottomBrush = CreateSolidBrush(RGB(128, 128, 128));

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_CREATE:
        SetTimer(hWnd, ID_TIMER_TRAFFIC_LIGHT, 2000, NULL);
        break;
    case WM_PAINT: 
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);


            //Create black brush
            HBRUSH blackBrush = CreateSolidBrush(RGB(1, 1, 1));
            HGDIOBJ hOrg = SelectObject(hdc, blackBrush); // Ikke lage flere instanser av denne. Det skal bare være en orignal

            //TRAFIKKLYS HORISONTAL

            //Black rectangle background
            Rectangle(hdc, position.x - left, position.y - top, position.x - right, position.y - bottom);
            SelectObject(hdc, topBrush); 
            //Grey circles inside the black rectangle
            Ellipse(hdc, position.x -left +100, position.y - top, position.x - right -0, position.y - bottom);
            SelectObject(hdc, middleBrush);
            Ellipse(hdc, position.x - left + 50, position.y - top, position.x - 50, position.y - bottom);
            SelectObject(hdc, bottomBrush);
            Ellipse(hdc, position.x - left - 0, position.y - top, position.x - 100, position.y - bottom);

            //TRAFIKKLYS VERTIKAL

            //Black rectangle background
            SelectObject(hdc,blackBrush);
            Rectangle(hdc, position.x - left +100, position.y - top - 250, position.x - right, position.y - bottom - 50);
            //Grey circles inside the black rectangle
            SelectObject(hdc, topBrush);
            Ellipse(hdc, position.x - left + 100, position.y - top - 250, position.x - right , position.y - bottom - 150);
            SelectObject(hdc, middleBrush);
            Ellipse(hdc, position.x - left + 100 , position.y - top-200, position.x - right, position.y - bottom - 100);
            SelectObject(hdc, bottomBrush);
            Ellipse(hdc, position.x - left + 100, position.y - top - 150, position.x - right, position.y - bottom - 50);

            //Drawing the road
            HBRUSH greyBrush = CreateSolidBrush(RGB(200, 200, 200));
            SelectObject(hdc, greyBrush);
            //Horisontal
            Rectangle(hdc, position.x + 600, position.y - 270, position.x - 600, position.y - 220);
            //Vertikal
            Rectangle(hdc, position.x + 50, position.y +600, position.x + 0, position.y - 600);
            
           

            //Delete brushes to stop memory leak
            SelectObject(hdc, hOrg);
            DeleteObject(blackBrush);
            DeleteObject(topBrush);
            DeleteObject(middleBrush);
            DeleteObject(bottomBrush);
            EndPaint(hWnd, &ps);
            
        }
        break;


    case WM_LBUTTONDOWN:
    {
        switch (state)
        {

        case 0:
        {
            topBrush = CreateSolidBrush(RGB(255, 0, 0));
            middleBrush = CreateSolidBrush(RGB(255, 255, 0));
            bottomBrush = CreateSolidBrush(RGB(128, 128, 128));
        }
        break;
        case 1:
        {
            topBrush = CreateSolidBrush(RGB(128, 128, 128));
            middleBrush = CreateSolidBrush(RGB(128,128,128));
            bottomBrush = CreateSolidBrush(RGB(0, 255, 0));

        }
        break;
        case 2:
        {
            topBrush = CreateSolidBrush(RGB(128, 128, 128));
            middleBrush = CreateSolidBrush(RGB(255, 255, 0));
            bottomBrush = CreateSolidBrush(RGB(128, 128, 128));
        }
        break;
        case 3:
        {
            topBrush = CreateSolidBrush(RGB(255, 0, 0));
            middleBrush = CreateSolidBrush(RGB(128, 128, 128));
            bottomBrush = CreateSolidBrush(RGB(128, 128, 128));
            state = -1;
        }
        break;

        default:
            break;
        }
       
        state++;
        InvalidateRect(hWnd,0,true);
    }
    break;

    case WM_TIMER:
    {
        if (wParam == ID_TIMER_TRAFFIC_LIGHT) {
            // Code to change traffic light colors
            switch (state)
            {
            case 0:
                // Change colors based on the current state
                topBrush = CreateSolidBrush(RGB(255, 0, 0));
                middleBrush = CreateSolidBrush(RGB(255, 255, 0));
                bottomBrush = CreateSolidBrush(RGB(128, 128, 128));
                break;
            case 1:
                topBrush = CreateSolidBrush(RGB(128, 128, 128));
                middleBrush = CreateSolidBrush(RGB(128, 128, 128));
                bottomBrush = CreateSolidBrush(RGB(0, 255, 0));
                break;
            case 2:
                topBrush = CreateSolidBrush(RGB(128, 128, 128));
                middleBrush = CreateSolidBrush(RGB(255, 255, 0));
                bottomBrush = CreateSolidBrush(RGB(128, 128, 128));
                break;
            case 3:
                topBrush = CreateSolidBrush(RGB(255, 0, 0));
                middleBrush = CreateSolidBrush(RGB(128, 128, 128));
                bottomBrush = CreateSolidBrush(RGB(128, 128, 128));
                state = -1;
                break;
            default:
                break;
            }
            state++;
            InvalidateRect(hWnd, 0, true); 
        }
        break;
    }
    
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
