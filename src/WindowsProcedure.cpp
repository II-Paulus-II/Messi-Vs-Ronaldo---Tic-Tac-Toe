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

#include "../include/main.h"
#include <iostream>

#define BUTTON(name,PosX,PosY,DEFINITION) ::CreateWindow (L"BUTTON", name, WS_CHILD | WS_BORDER,\
                                                          PosX, PosY, 135, 50, hWnd,\
                                                          (HMENU)DEFINITION, NULL, NULL)

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
    case WM_LBUTTONDOWN:
    {
        if (game == new_game) {
            if (player_Turn == its_ronaldo) {
                bool ValidMove = place_Face(hWnd, lParam);
                if (ValidMove) {
                    player_Turn = its_messi;
                    InvalidateRect(hWnd, NULL, FALSE);
                }
            }
        }
        break;
    }
    case WM_RBUTTONDOWN:
    {
        if (game == new_game) {
            if (player_Turn == its_messi) {
                bool ValidMove = place_Face(hWnd, lParam);
                if (ValidMove) {
                    player_Turn = its_ronaldo;
                    InvalidateRect(hWnd, NULL, FALSE);
                }
            }
        }
        break;
    }
    case WM_CREATE:
        //CRASHES IF I HAVE THE MESSAGE BOX OUTSIDE THE SWITCH
        BUTTON(L"Tic Tac Toe", 462, 480, NEW_GAME_BTN);

        break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        Gdiplus::Graphics graphics(hdc);
        Gdiplus::Image MAINBACKGROUND(L"./data/mainbackground.png");
        Gdiplus::Image MESSI(L"./data/messi.png");
        Gdiplus::Image RONALDO(L"./data/ronaldo.png");
        Gdiplus::Image GAMEBACKGROUND(L"./data/gamebackground.png");
        Gdiplus::Image MESSIWINS(L"./data/messiwins.png");
        Gdiplus::Image RONALDOWINS(L"./data/ronaldowins.png");

        if (game == no_game) {
            show_New_Game_Button(hWnd);
            graphics.DrawImage(&MAINBACKGROUND, 0, 0, 1075, 825);

        }

        if (game == new_game) {
            graphics.DrawImage(&GAMEBACKGROUND, 0, 0);
            draw_Board(hdc);
            for (int iX = 0; iX < 3; iX++) {
                for (int iY = 0; iY < 3; iY++) {
                    int PosX = (iX * 260) + 275;
                    int PosY = iY * 260;
                    if (board_value[iX][iY] == its_messi) {
                        graphics.DrawImage(&MESSI, PosX, PosY, 250, 250);
                    }
                    else if (board_value[iX][iY] == its_ronaldo) {
                        graphics.DrawImage(&RONALDO, PosX, PosY, 250, 250);
                    }
                }
            }
            bool messi_wins = winner_Messi();
            if (messi_wins) {
                InvalidateRect(hWnd, NULL, FALSE);
            }
            bool ronaldo_wins = winner_Ronaldo();
            if (ronaldo_wins) {
                InvalidateRect(hWnd, NULL, FALSE);
            }
            bool nobody_won = nobody_Wins();
            if (nobody_won) {
                MessageBox(hWnd, _T("Nobody Won, Play Again!"), _T("Result"), MB_OK);
                new_Game();
                InvalidateRect(hWnd, NULL, FALSE);
            }
        }
        if (game == messi_won) {
            graphics.DrawImage(&MESSIWINS, 0, 0, 1075, 825);
        }
        if (game == ronaldo_won) {
            graphics.DrawImage(&RONALDOWINS, 0, 0, 1075, 825);
        }
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case ID_FILE_NEWGAME:
        {
            new_Game(); //make sure that the enum is filled out blank
            game = new_game;
            show_New_Game_Button(hWnd);
            InvalidateRect(hWnd, NULL, FALSE);
        }
        break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
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