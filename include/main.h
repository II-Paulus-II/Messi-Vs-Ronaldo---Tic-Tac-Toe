#pragma once

#include "../resources/resources.h"
#include "framework.h"

#define MAX_LOADSTRING 100

extern HINSTANCE hInst;                                // current instance
extern WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
extern WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

extern enum game_state { no_game, new_game, messi_won, ronaldo_won};
extern game_state game;

extern enum square_x_o { blank, its_messi, its_ronaldo };
extern square_x_o player_Turn;
extern square_x_o board_value[3][3];

//void text_vs(HWND hwnd, HDC hdc);
void draw_Board(HDC hdc);

bool place_Face(HWND hWnd, LPARAM lparam);

void new_Game();
bool winner_Messi();
bool winner_Ronaldo();
bool nobody_Wins();

void show_New_Game_Button(HWND hWnd);

