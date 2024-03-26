#include "../include/main.h"

square_x_o player_Turn = blank;
square_x_o board_value[3][3] = { { blank , blank , blank },
                                { blank , blank , blank },
                                { blank , blank , blank } };


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
    MoveToEx(hdc, 556, 55, NULL);
    LineTo(hdc, 556, 745);
    MoveToEx(hdc, 788, 55, NULL);
    LineTo(hdc, 788, 745);
    // two horizontal ones
    MoveToEx(hdc, 330, 281, NULL);
    LineTo(hdc, 1020, 281);
    MoveToEx(hdc, 330, 513, NULL);
    LineTo(hdc, 1020, 513);

    SelectObject(hdc, hPenOld);
    DeleteObject(hLinePen);
}

bool place_Face(HWND hWnd, LPARAM lparam) {
    int iPosX = LOWORD(lparam);
    int iPosY = HIWORD(lparam);
    //check for valid move
    if (iPosX >=330 && iPosX <= 1020 ) {
        int iSqX = 0;
        int iSqY = 0;
        //get board values
        if (iPosX >= 330 && iPosX <= 556) {
            iSqX = 0;
        }
        else if (iPosX > 556 && iPosX <= 788) {
            iSqX = 1;
        }
        else if (iPosX > 788) {
            iSqX = 2;
        }
        if (iPosY <= 281) {
            iSqY = 0;
        }
        else if (iPosY > 281 && iPosY <= 513) {
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
        game = messi_won;
        return true;
    }
    //horizontal lines
    if ((board_value[0][0] == its_messi && board_value[1][0] == its_messi && board_value[2][0] == its_messi) ||
        (board_value[0][1] == its_messi && board_value[1][1] == its_messi && board_value[2][1] == its_messi) ||
        (board_value[0][2] == its_messi && board_value[1][2] == its_messi && board_value[2][2] == its_messi)) {
        game = messi_won;
        return true;
    }
    // diagonal
    if ((board_value[0][0] == its_messi && board_value[1][1] == its_messi && board_value[2][2] == its_messi) ||
        (board_value[0][2] == its_messi && board_value[1][1] == its_messi && board_value[2][0] == its_messi)) {
        game = messi_won;
        return true;
    }

    else return false;
}

bool winner_Ronaldo() {
    //vertical lines
    if ((board_value[0][0] == its_ronaldo && board_value[0][1] == its_ronaldo && board_value[0][2] == its_ronaldo) ||
        (board_value[1][0] == its_ronaldo && board_value[1][1] == its_ronaldo && board_value[1][2] == its_ronaldo) ||
        (board_value[2][0] == its_ronaldo && board_value[2][1] == its_ronaldo && board_value[2][2] == its_ronaldo)) {
        game = ronaldo_won;
        return true;
    }
    //horizontal lines
    if ((board_value[0][0] == its_ronaldo && board_value[1][0] == its_ronaldo && board_value[2][0] == its_ronaldo) ||
        (board_value[0][1] == its_ronaldo && board_value[1][1] == its_ronaldo && board_value[2][1] == its_ronaldo) ||
        (board_value[0][2] == its_ronaldo && board_value[1][2] == its_ronaldo && board_value[2][2] == its_ronaldo)) {
        game = ronaldo_won;
        return true;
    }
    // diagonal
    if ((board_value[0][0] == its_ronaldo && board_value[1][1] == its_ronaldo && board_value[2][2] == its_ronaldo) ||
        (board_value[0][2] == its_ronaldo && board_value[1][1] == its_ronaldo && board_value[2][0] == its_ronaldo)) {
        game = ronaldo_won;
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
    if (game == messi_won || game == ronaldo_won) {
        return false;
    }
    game = nobody_won;
    return true;
}

void show_Game_Buttons(HWND hWnd) {
    HWND new_Game_Button = GetDlgItem(hWnd, NEW_GAME_BTN);
    HWND messi_Won_Button = GetDlgItem(hWnd, MESSI_WON_BTN);
    HWND ronaldo_Won_Button = GetDlgItem(hWnd, RONALDO_WON_BTN);
    HWND nobody_Won_Button = GetDlgItem(hWnd, NOBODY_WON_BTN);

    if (game == no_game) {
        ShowWindow(new_Game_Button, SW_SHOW);
    }
    else {
        ShowWindow(new_Game_Button, SW_HIDE);
    }
    if (game == messi_won) {
        ShowWindow(messi_Won_Button, SW_SHOW);
    }
    else {
        ShowWindow(messi_Won_Button, SW_HIDE);
    }
    if (game == ronaldo_won) {
        ShowWindow(ronaldo_Won_Button, SW_SHOW);
    }
    else {
        ShowWindow(ronaldo_Won_Button, SW_HIDE);
    }
    if (game == nobody_won) {
        ShowWindow(nobody_Won_Button, SW_SHOW);
    }
    else {
        ShowWindow(nobody_Won_Button, SW_HIDE);
    }
}