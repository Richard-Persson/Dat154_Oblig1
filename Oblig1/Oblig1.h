#pragma once

#include "resource.h"
#define ID_TIMER_TRAFFIC_LIGHT 1
#define ID_TIMER_TRAFFIC_LIGHT_2 2
#define ID_TIMER_CAR_MOVEMENT 3
#define ID_TIMER_CAR_MOVEMENT2 4


void tegnTrafikklys(HDC hdc, HWND hWnd, POINT point,  HBRUSH topBrush1, HBRUSH middleBrush1, HBRUSH bottomBrush1, HBRUSH topBrush2, HBRUSH middleBrush2, HBRUSH bottomBrush2);
void InitializeTrafficLightBrushes();
void CleanupResources();
void UpdateTrafficLightState1(HWND hWind);
void UpdateTrafficLightState2(HWND hWind);

int stateTrafficLight1 = 0;
int stateTrafficLight2 = 2;

const int DURATION_RED_1 = 2000;
const int DURATION_GREEN_1 = 3000;
const int DURATION_YELLOW_1 = 1000;

const int DURATION_RED_2 = 3000;
const int DURATION_GREEN_2 = 2000;
const int DURATION_YELLOW_2 = 1500;