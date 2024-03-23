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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {

    case WM_LBUTTONDOWN:
    {
        if (start_Game) {
            bool ValidMove = place_Messi(hWnd, lParam);
            if (ValidMove) {
                player_Turn = its_ronaldo;
            }
            else {
                MessageBox(hWnd, _T("Invalid Move"), _T("Error"), MB_OK);
            }
            // Repaint the window after the update
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    }
    case WM_RBUTTONDOWN:
    {
        if (start_Game) {
            bool ValidMove = place_Ronaldo(lParam);
            if (ValidMove) {
                player_Turn = its_messi;
            }
            else {
                MessageBox(hWnd, _T("Invalid Move"), _T("Error"), MB_OK);
            }
            // Repaint the window after the update
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    }
    case WM_CREATE:
        //CRASHES IF I HAVE THE MESSAGE BOX OUTSIDE THE SWITCH

        break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        if (!start_Game) {

            RECT rc;
            GetClientRect(hWnd, &rc);

            SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT));
            SetBkMode(hdc, TRANSPARENT);
            SetTextColor(hdc, RGB(255, 0, 0));

            std::wstring strOut = L"Hello World!"; // or wstring if you have unicode set
            DrawText(hdc, strOut.c_str(), strOut.length(), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }

        if (start_Game) {
            draw_Board(hdc);
            ***REMOVED***
            for (int iX = 0; iX < 3; iX++) {
                for (int iY = 0; iY < 3; iY++) {
                    if (board_value[iX][iY] == its_messi) {
                        draw_Messi(hdc, iX, iY);
                    }
                }
            }
            for (int iX = 0; iX < 3; iX++) {
                for (int iY = 0; iY < 3; iY++) {
                    if (board_value[iX][iY] == its_ronaldo) {
                        draw_Ronaldo(hdc, iX, iY);
                    }
                }
            }
            bool messi_wins = winner_Messi();
            if (messi_wins) {
                MessageBox(hWnd, _T("Messi"), _T("Messi"), MB_OK);
                new_Game();
                InvalidateRect(hWnd, NULL, TRUE);
            }
            bool ronaldo_wins = winner_Ronaldo();
            if (ronaldo_wins) {
                MessageBox(hWnd, _T("Ronaldo"), _T("Ronaldo"), MB_OK);
                new_Game();
                InvalidateRect(hWnd, NULL, TRUE);
            }
            bool nobody_won = nobody_Wins();
            if (nobody_won) {
                MessageBox(hWnd, _T("Nobody"), _T("Nobody"), MB_OK);
                new_Game();
                InvalidateRect(hWnd, NULL, TRUE);
            }
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
            start_Game = true;
            InvalidateRect(hWnd, NULL, TRUE);
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