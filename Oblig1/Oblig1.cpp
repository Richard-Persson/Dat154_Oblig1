// Oblig1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Oblig1.h"
#include <vector>

//TRAFIKKLYS 1
static HBRUSH topBrush1 = NULL;
static HBRUSH middleBrush1 = NULL;
static HBRUSH bottomBrush1 = NULL;
static BOOLEAN stopp1 = false;

//TRAFIKKLYS 2
static HBRUSH topBrush2 = NULL;
static HBRUSH middleBrush2 = NULL;
static HBRUSH bottomBrush2 = NULL;
static BOOLEAN stopp2 = false;

struct Car {
    POINT positionCar;
    bool inMove;
};

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];            

static POINT position = { 500,500 };
int state = 0;
std::vector<Car> carsWest, carsNorth;


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

    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
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

        InitializeTrafficLightBrushes();
        SetTimer(hWnd, ID_TIMER_TRAFFIC_LIGHT, 2000, NULL);
      
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        RECT size;
        GetClientRect(hWnd, &size);


        //Tegne veien
        HBRUSH greyBrush = CreateSolidBrush(RGB(128, 128, 128));

        SelectObject(hdc, greyBrush);
        Rectangle(hdc, size.left, size.top, size.right, size.bottom);


        HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, whiteBrush);

        Rectangle(hdc, 550, 285, size.right, size.bottom);
        Rectangle(hdc, size.left, 285, 500, size.bottom);

        Rectangle(hdc, 550, size.top, size.right, 235);
        Rectangle(hdc, size.left, size.top, 500, 235);

        tegnTrafikklys(hdc, hWnd, position, topBrush1, middleBrush1, bottomBrush1, topBrush2, middleBrush2, bottomBrush2);




        //Bil
        HBRUSH carBrush = CreateSolidBrush(RGB(0, 0, 255));
        SelectObject(hdc, carBrush);
        for (const auto& Car : carsWest) {
            Rectangle(hdc, Car.positionCar.x + 10, Car.positionCar.y + 10, Car.positionCar.x - 10, Car.positionCar.y - 10);
        };

        for (const auto& Car : carsNorth) {
            Rectangle(hdc, Car.positionCar.x - 10, Car.positionCar.y - 10, Car.positionCar.x + 10, Car.positionCar.y + 10);
        };

        //Slette børster
        DeleteObject(whiteBrush);
        DeleteObject(greyBrush);
        DeleteObject(carBrush);
        EndPaint(hWnd, &ps);

    }
    break;


    case WM_LBUTTONDOWN: {
        //carPositionVertical.x = ;
        //carPositionVertical.y = 500;
        Car newCarWest = { {0,260}, true };
        carsWest.push_back(newCarWest);
        SetTimer(hWnd, ID_TIMER_CAR_MOVEMENT, 100, NULL);
        InvalidateRect(hWnd, NULL, TRUE);
        break; }


    case WM_RBUTTONDOWN: {
        //carPositionHorisontal.x = 0;
        //carPositionHorisontal.y = 500;
        Car newCarNorth = { {525,10}, true };
        carsNorth.push_back(newCarNorth); 
        SetTimer(hWnd, ID_TIMER_CAR_MOVEMENT2, 100, NULL);
        InvalidateRect(hWnd, NULL, TRUE); 
        break; }

    case WM_TIMER:
    {
        if (wParam == ID_TIMER_TRAFFIC_LIGHT) {
            UpdateTrafficLightState1(hWnd);
            UpdateTrafficLightState2(hWnd);
        }
        void UpdateCarPositions(std::vector<Car>&cars, int direction);
        if (wParam == ID_TIMER_CAR_MOVEMENT) {
            UpdateCarPositions(carsWest, 0);  
        //    carPositionVertical.y += 5; 
        }

        else if (wParam == ID_TIMER_CAR_MOVEMENT2) {
            UpdateCarPositions(carsNorth, 1);
        //    carPositionHorisontal.x += 5;
       }


        InvalidateRect(hWnd, NULL, TRUE);
        break;
    }


    case WM_DESTROY:
        CleanupResources();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
   }



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



void InitializeTrafficLightBrushes() {
    if (!topBrush1) topBrush1 = CreateSolidBrush(RGB(255, 0, 0)); // Rød
    if (!middleBrush1) middleBrush1 = CreateSolidBrush(RGB(128, 128, 128))    ; // Grå
    if (!bottomBrush1) bottomBrush1 = CreateSolidBrush(RGB(128, 128, 128)); // Grå

    if (!topBrush2) topBrush2 = CreateSolidBrush(RGB(128, 128, 128)); // Grå
    if (!middleBrush2) middleBrush2 = CreateSolidBrush(RGB(128, 128, 128)); // Grå
    if (!bottomBrush2) bottomBrush2 = CreateSolidBrush(RGB(0, 255, 0)); // Grå
}


void CleanupResources() {
    DeleteObject(topBrush1);
    DeleteObject(middleBrush1);
    DeleteObject(bottomBrush1);
    DeleteObject(topBrush2);
    DeleteObject(middleBrush2);
    DeleteObject(bottomBrush2);
}

void UpdateTrafficLightState2(HWND hWnd) {
    static int stateTrafficLight1 = 0;
    static int stateTrafficLight2 = 0;
    int* state = 0;
    int durationRed, durationGreen, durationYellow;



    state = &stateTrafficLight2;
    durationRed = DURATION_RED_2;
    durationGreen = DURATION_GREEN_2;
    durationYellow = DURATION_YELLOW_2;




    HBRUSH newTopBrush, newMiddleBrush, newBottomBrush;

    switch (*state) {
    case 2: // Rød
        newTopBrush = CreateSolidBrush(RGB(255, 0, 0));
        newMiddleBrush = CreateSolidBrush(RGB(128, 128, 128));
        newBottomBrush = CreateSolidBrush(RGB(128, 128, 128));
        stopp2 = false;
        break;
    case 3: // Gul og rød
        newTopBrush = CreateSolidBrush(RGB(255, 0, 0));
        newMiddleBrush = CreateSolidBrush(RGB(255, 255, 0));
        newBottomBrush = CreateSolidBrush(RGB(128, 128, 128));
        break;

    case 0: //Grønn
        newTopBrush = CreateSolidBrush(RGB(128, 128, 128));
        newMiddleBrush = CreateSolidBrush(RGB(128, 128, 128));
        newBottomBrush = CreateSolidBrush(RGB(0, 255, 0));
        stopp2 = true;
        break;

    case 1: // Gul
        newTopBrush = CreateSolidBrush(RGB(128, 128, 128));
        newMiddleBrush = CreateSolidBrush(RGB(255, 255, 0));
        newBottomBrush = CreateSolidBrush(RGB(128, 128, 128));
        break;

    default: // Default to green
        newTopBrush = CreateSolidBrush(RGB(128, 128, 128));
        newMiddleBrush = CreateSolidBrush(RGB(128, 128, 128));
        newBottomBrush = CreateSolidBrush(RGB(0, 255, 0));
        *state = 0;
        stopp2 = true;
        break;
    }

    *state = *state + 1;

    // Slette gamle børster oppdater global. 
    topBrush2 = newTopBrush;
    middleBrush2 = newMiddleBrush;
    bottomBrush2 = newBottomBrush;



    InvalidateRect(hWnd, NULL, TRUE);
}

void UpdateTrafficLightState1(HWND hWnd) {
    static int stateTrafficLight1 = 0;
    static int stateTrafficLight2 = 0;
    int* state = 0;
    int durationRed, durationGreen, durationYellow;

    // Definer trafikklys som skal oppdateres. 
    
        state = &stateTrafficLight1;
        durationRed = DURATION_RED_1;
        durationGreen = DURATION_GREEN_1;
        durationYellow = DURATION_YELLOW_1;

    //Definerer børstene for trafikklys
    HBRUSH newTopBrush, newMiddleBrush, newBottomBrush;

    switch (*state) {
    case 0: // Rød
        newTopBrush = CreateSolidBrush(RGB(255, 0, 0));
        newMiddleBrush = CreateSolidBrush(RGB(128, 128, 128));
        newBottomBrush = CreateSolidBrush(RGB(128, 128, 128));
        stopp1 = false;
        break;
    case 1: // Gul og rød
        newTopBrush = CreateSolidBrush(RGB(255, 0, 0));
        newMiddleBrush = CreateSolidBrush(RGB(255, 255, 0));
        newBottomBrush = CreateSolidBrush(RGB(128, 128, 128));
        break;
  
    case 2: //Grønn
        newTopBrush = CreateSolidBrush(RGB(128, 128, 128));
        newMiddleBrush = CreateSolidBrush(RGB(128, 128, 128));
        newBottomBrush = CreateSolidBrush(RGB(0, 255, 0));
        stopp1 = true;
        break;

    case 3: // Gul
        newTopBrush = CreateSolidBrush(RGB(128, 128, 128));
        newMiddleBrush = CreateSolidBrush(RGB(255, 255, 0));
        newBottomBrush = CreateSolidBrush(RGB(128, 128, 128));
        break;

    default: // Default til rød
        newTopBrush = CreateSolidBrush(RGB(255, 0, 0));
        newMiddleBrush = CreateSolidBrush(RGB(128, 128, 128));
        newBottomBrush = CreateSolidBrush(RGB(128, 128, 128));
        *state = 0;
        stopp1 = false;
        break;
    }

    *state = *state + 1;

    // Slette gamble brushes og oppdatere globale
    topBrush1 = newTopBrush;
    middleBrush1 = newMiddleBrush;
    bottomBrush1 = newBottomBrush;



    // Endre state på trafikklys
    InvalidateRect(hWnd, NULL, TRUE);
}



void tegnTrafikklys(HDC hdc, HWND hWnd,POINT position,HBRUSH topBrush1,HBRUSH middleBrush1,HBRUSH bottomBrush1
    , HBRUSH topBrush2, HBRUSH middleBrush2, HBRUSH bottomBrush2) {


    RECT size;
    GetClientRect(hWnd, &size);
     int left = 150;
     int right = left - 150;
     int top = 165;
     int bottom = top + 50;


     HBRUSH blackBrush = CreateSolidBrush(RGB(1, 1, 1));
     HGDIOBJ hOrg = SelectObject(hdc,blackBrush);


    //TRAFIKKLYS HORISONTAL

    //Svart rektangel
    Rectangle(hdc, position.x - left, position.y - top, position.x - right, position.y - bottom);
    SelectObject(hdc, topBrush1);
    //Sirkler inni svart rektangel
    Ellipse(hdc, position.x - left + 100, position.y - top, position.x - right - 0, position.y - bottom);
    SelectObject(hdc, middleBrush1);
    Ellipse(hdc, position.x - left + 50, position.y - top, position.x - 50, position.y - bottom);
    SelectObject(hdc, bottomBrush1);
    Ellipse(hdc, position.x - left - 0, position.y - top, position.x - 100, position.y - bottom);

    //TRAFIKKLYS VERTIKAL
    //Svart bakgrunn
    SelectObject(hdc, blackBrush);
    Rectangle(hdc, position.x - left + 100, position.y - top - 250, position.x - right, position.y - bottom - 50);
    //Sirkler inni svart
    SelectObject(hdc, topBrush2);
    Ellipse(hdc, position.x - left + 100, position.y - top - 250, position.x - right, position.y - bottom - 150);
    SelectObject(hdc, middleBrush2);
    Ellipse(hdc, position.x - left + 100, position.y - top - 200, position.x - right, position.y - bottom - 100);
    SelectObject(hdc, bottomBrush2);
    Ellipse(hdc, position.x - left + 100, position.y - top - 150, position.x - right, position.y - bottom - 50);


    SelectObject(hdc, hOrg);
    DeleteObject(blackBrush);
}

void UpdateCarPositions(std::vector<Car>& cars, int direction) {
    for (auto& Car : cars) {
        if (Car.inMove) {
            if (direction == 0) {

                if (!stopp1 && Car.positionCar.x <500) 
                    Car.positionCar.x == Car.positionCar.x;
                
                else 
                    Car.positionCar.x += 10;
                

            }
            else {
                if (!stopp2 && Car.positionCar.y < 225)
                    Car.positionCar.y == Car.positionCar.y;
                else
                Car.positionCar.y += 10;
            }
        }
    }
}