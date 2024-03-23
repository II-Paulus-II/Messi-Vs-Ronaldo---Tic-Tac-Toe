#include "../include/main.h"

extern enum square_x_o { blank, its_messi, its_ronaldo };
extern square_x_o player_Turn = blank;
extern square_x_o board_value[3][3] = { { blank , blank , blank },
                                { blank , blank , blank },
                                { blank , blank , blank } };


void draw_Board(HDC hdc)
{
    HPEN hPenOld;
    // Draw the board lines
    HPEN hLinePen;
    COLORREF qLineColor;
    qLineColor = RGB(0, 0, 0);
    hLinePen = CreatePen(PS_SOLID, 10, qLineColor);
    hPenOld = (HPEN)SelectObject(hdc, hLinePen);
    // Draw two vertical lines
    MoveToEx(hdc, 255, 0, NULL);
    LineTo(hdc, 255, 765);
    MoveToEx(hdc, 515, 0, NULL);
    LineTo(hdc, 515, 765);
    // two horizontal ones
    MoveToEx(hdc, 0, 255, NULL);
    LineTo(hdc, 765, 255);
    MoveToEx(hdc, 0, 515, NULL);
    LineTo(hdc, 765, 515);

    SelectObject(hdc, hPenOld);
    DeleteObject(hLinePen);
}

void draw_Messi(HDC hdc, int iX, int iY) {
    HDC hdcMem = CreateCompatibleDC(hdc); //
    SelectObject(hdcMem, messi);
    int PosX, PosY;
    if (iX == 0) {
        PosX = 0;
    }
    else if (iX == 1) {
        PosX = 260;
    }
    else {
        PosX = 520;
    }
    if (iY == 0) {
        PosY = 0;
    }
    else if (iY == 1) {
        PosY = 260;
    }
    else {
        PosY = 520;
    }

    BitBlt(
        hdc,
        PosX,
        PosY,
        250,
        250,
        hdcMem,
        0,
        0,
        SRCCOPY);

    SelectObject(hdcMem, messi);
    DeleteObject(hdcMem);
}

void draw_Ronaldo(HDC hdc, int iX, int iY) {
    HDC hdcMem = CreateCompatibleDC(hdc); //
    SelectObject(hdcMem, ronaldo);
    int PosX, PosY;
    if (iX == 0) {
        PosX = 0;
    }
    else if (iX == 1) {
        PosX = 260;
    }
    else {
        PosX = 520;
    }
    if (iY == 0) {
        PosY = 0;
    }
    else if (iY == 1) {
        PosY = 260;
    }
    else {
        PosY = 520;
    }

    BitBlt(
        hdc,
        PosX,
        PosY,
        250,
        250,
        hdcMem,
        0,
        0,
        SRCCOPY);
    SelectObject(hdcMem, ronaldo);
    DeleteObject(hdcMem);
}

bool place_Messi(HWND hwnd, LPARAM lparam) {

    int iPosX = LOWORD(lparam);
    int iPosY = HIWORD(lparam);
    int iSqX;
    int iSqY;
    if (iPosX <= 255) {
        iSqX = 0;
        //MessageBox(hwnd,"0", "X", MB_OK);
    }
    else if (iPosX > 255 && iPosX <= 515) {
        //MessageBox(hwnd,"1", "X", MB_OK);
        iSqX = 1;
    }
    else {
        //MessageBox(hwnd,"2", "X", MB_OK);
        iSqX = 2;
    }
    if (iPosY <= 255) {
        //MessageBox(hwnd,"0", "Y", MB_OK);
        iSqY = 0;
    }
    else if (iPosY > 255 && iPosY <= 515) {
        //MessageBox(hwnd,"1", "Y", MB_OK);
        iSqY = 1;
    }
    else {
        //MessageBox(hwnd,"2", "Y", MB_OK);
        iSqY = 2;
    }
    if ((player_Turn == its_messi) &&
        (iSqX < 3) && (iSqY < 3) &&
        (board_value[iSqX][iSqY] == blank))
    {
        board_value[iSqX][iSqY] = its_messi;
        return true;
    }
    return false;
}

bool place_Ronaldo(LPARAM lparam) {

    int iPosX = LOWORD(lparam);
    int iPosY = HIWORD(lparam);
    int iSqX;
    int iSqY;
    if (iPosX <= 255) {
        iSqX = 0;
    }
    else if (iPosX > 255 && iPosX <= 515) {
        iSqX = 1;
    }
    else {
        iSqX = 2;
    }
    if (iPosY <= 255) {
        iSqY = 0;
    }
    else if (iPosY > 255 && iPosY <= 515) {
        iSqY = 1;
    }
    else {
        iSqY = 2;
    }
    if ((player_Turn == its_ronaldo) &&
        (iSqX < 3) && (iSqY < 3) &&
        (board_value[iSqX][iSqY] == blank))
    {
        board_value[iSqX][iSqY] = its_ronaldo;
        return true;
    }
    return false;
}

bool winner_Messi() {
    //vertical lines
    if ((board_value[0][0] == its_messi && board_value[0][1] == its_messi && board_value[0][2] == its_messi) ||
        (board_value[1][0] == its_messi && board_value[1][1] == its_messi && board_value[1][2] == its_messi) ||
        (board_value[2][0] == its_messi && board_value[2][1] == its_messi && board_value[2][2] == its_messi)) {
        return true;
    }
    //horizontal lines
    if ((board_value[0][0] == its_messi && board_value[1][0] == its_messi && board_value[2][0] == its_messi) ||
        (board_value[0][1] == its_messi && board_value[1][1] == its_messi && board_value[2][1] == its_messi) ||
        (board_value[0][2] == its_messi && board_value[1][2] == its_messi && board_value[2][2] == its_messi)) {
        return true;
    }
    // diagonal
    if ((board_value[0][0] == its_messi && board_value[1][1] == its_messi && board_value[2][2] == its_messi) ||
        (board_value[0][2] == its_messi && board_value[1][1] == its_messi && board_value[2][0] == its_messi)) {
        return true;
    }

    else return false;
}

bool winner_Ronaldo() {
    //vertical lines
    if ((board_value[0][0] == its_ronaldo && board_value[0][1] == its_ronaldo && board_value[0][2] == its_ronaldo) ||
        (board_value[1][0] == its_ronaldo && board_value[1][1] == its_ronaldo && board_value[1][2] == its_ronaldo) ||
        (board_value[2][0] == its_ronaldo && board_value[2][1] == its_ronaldo && board_value[2][2] == its_ronaldo)) {
        return true;
    }
    //horizontal lines
    if ((board_value[0][0] == its_ronaldo && board_value[1][0] == its_ronaldo && board_value[2][0] == its_ronaldo) ||
        (board_value[0][1] == its_ronaldo && board_value[1][1] == its_ronaldo && board_value[2][1] == its_ronaldo) ||
        (board_value[0][2] == its_ronaldo && board_value[1][2] == its_ronaldo && board_value[2][2] == its_ronaldo)) {
        return true;
    }
    // diagonal
    if ((board_value[0][0] == its_ronaldo && board_value[1][1] == its_ronaldo && board_value[2][2] == its_ronaldo) ||
        (board_value[0][2] == its_ronaldo && board_value[1][1] == its_ronaldo && board_value[2][0] == its_ronaldo)) {
        return true;
    }

    else return false;
}

void new_Game() {
    for (int iX = 0; iX < 3; iX++) {
        for (int iY = 0; iY < 3; iY++) {
            board_value[iY][iX] = blank;
        }
    }
    player_Turn = its_messi;

}

bool nobody_Wins() {
    for (int iX = 0; iX < 3; iX++) {
        for (int iY = 0; iY < 3; iY++) {
            if (board_value[iY][iX] == blank) {
                return false;
            }
        }
    }
    return true;
}

