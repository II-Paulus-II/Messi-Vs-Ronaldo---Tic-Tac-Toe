#ifndef HEADERS
#define HEADERS
#endif // HEADERS

// Seperate header file not connected to "resource.h" for std libraries needed.
#include <iostream>
#include <string>
#include <filesystem>
#include <tchar.h>
#include <windows.h>
#include <wingdi.h>

enum square_x_o { blank, its_messi, its_ronaldo };
square_x_o player_Turn = blank;
square_x_o board_value[3][3] = {{ blank , blank , blank },
                                { blank , blank , blank },
                                { blank , blank , blank }};

void text_vs(HWND hwnd, HDC hdc);
void draw_Board(HDC hdc);

void draw_Messi (HDC hdc, int iX, int iY);
void draw_Ronaldo (HDC hdc, int iX, int iY);

bool place_Messi (HWND hwnd, LPARAM lParam);
bool place_Ronaldo (LPARAM lparam);

void new_Game();
bool winner_Messi();
bool winner_Ronaldo();
bool nobody_Wins();







