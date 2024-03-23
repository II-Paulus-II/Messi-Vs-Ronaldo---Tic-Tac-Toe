#pragma once

#include "../resources/resources.h"
#include "framework.h"

#define MAX_LOADSTRING 100

extern HINSTANCE hInst;                                // current instance
extern WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
extern WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

extern bool start_Game;

extern LPCWSTR file_messi;
extern HBITMAP messi;
extern LPCWSTR file_ronaldo;
extern HBITMAP ronaldo;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

extern enum square_x_o;
extern square_x_o player_Turn;
extern square_x_o board_value[3][3];

//void text_vs(HWND hwnd, HDC hdc);
void draw_Board(HDC hdc);

void draw_Messi(HDC hdc, int iX, int iY);
void draw_Ronaldo(HDC hdc, int iX, int iY);

bool place_Messi(HWND hwnd, LPARAM lParam);
bool place_Ronaldo(LPARAM lparam);

void new_Game();
bool winner_Messi();
bool winner_Ronaldo();
bool nobody_Wins();
