#include "../include/main.h"

extern square_x_o player_Turn = blank;
extern square_x_o board_value[3][3] = { { blank , blank , blank },
                                { blank , blank , blank },
                                { blank , blank , blank } };


void render_First_Scene(HDC hdc) {
    /*HDC hdcMem = CreateCompatibleDC(hdc); //
    SelectObject(hdcMem, messi);
    int PosX = 100;
    int PosY = 200;

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

    HDC hdcMemA = CreateCompatibleDC(hdc); //
    SelectObject(hdcMemA, ronaldo);
    PosX = 400;
    PosY = 200;

    BitBlt(
        hdc,
        PosX,
        PosY,
        250,
        250,
        hdcMemA,
        0,
        0,
        SRCCOPY);

    SelectObject(hdcMemA, ronaldo);
    DeleteObject(hdcMemA); */
}

void draw_Board(HDC hdc) {

    //Draw Board
    HPEN hPenOld;
    // Draw the board lines
    HPEN hLinePen;
    COLORREF qLineColor;
    qLineColor = RGB(255, 255, 255);
    hLinePen = CreatePen(PS_SOLID, 6, qLineColor);
    hPenOld = (HPEN)SelectObject(hdc, hLinePen);
    // Draw two vertical lines
    MoveToEx(hdc, 532, 0, NULL);
    LineTo(hdc, 532, 767);
    MoveToEx(hdc, 792, 0, NULL);
    LineTo(hdc, 792, 767);
    // two horizontal ones
    MoveToEx(hdc, 275, 257, NULL);
    LineTo(hdc, 1050, 257);
    MoveToEx(hdc, 275, 517, NULL);
    LineTo(hdc, 1050, 517);

    SelectObject(hdc, hPenOld);
    DeleteObject(hLinePen);
}

bool place_Face(HWND hWnd, LPARAM lparam) {
    int iPosX = LOWORD(lparam);
    int iPosY = HIWORD(lparam);
    //check for valid move
    if (iPosX >=275 && iPosX <= 1040 ) {
        int iSqX;
        int iSqY;
        //get board values
        if (iPosX >= 275 && iPosX <= 532) {
            iSqX = 0;
        }
        else if (iPosX > 532 && iPosX <= 792) {
            iSqX = 1;
        }
        else if (iPosX > 792) {
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
        //assign board values
        if ((player_Turn == its_messi) &&
            (iSqX < 3) && (iSqY < 3) &&
            (board_value[iSqX][iSqY] == blank))
        {
            board_value[iSqX][iSqY] = its_messi;
            return true;
        }
        else if ((player_Turn == its_ronaldo) &&
            (iSqX < 3) && (iSqY < 3) &&
            (board_value[iSqX][iSqY] == blank))
        {
            board_value[iSqX][iSqY] = its_ronaldo;
            return true;
        }
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

void show_New_Game_Button(HWND hWnd) {
    HWND new_Game_Button = GetDlgItem(hWnd, NEW_GAME_BTN);

    if (!start_Game) {
        ShowWindow(new_Game_Button, SW_SHOW);
    }
    else {
        ShowWindow(new_Game_Button, SW_HIDE);
    }
}