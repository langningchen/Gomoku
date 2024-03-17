/**********************************************************************
Gomoku: Play Gomoku with AI powered computer!
Copyright (C) 2024  langningchen

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
**********************************************************************/

#include "UserInterface.hpp"
#include "Game.hpp"
#include "time.h"
#include <stdio.h>
void USER_INTERFACE::Draw(POINT Point, int Index)
{
    StretchBlt(DrawDestination,
               ChessBoardPosition.x + Point.x * ChessSize + Delta.x, ChessBoardPosition.y + Point.y * ChessSize + Delta.y,
               ChessSize, ChessSize,
               DrawSource,
               0, Index * ChessSize, ChessSize, ChessSize, SRCCOPY);
}
void USER_INTERFACE::DrawAll()
{
    for (int x = 0; x < Game.MapSize; x++)
        for (int y = 0; y < Game.MapSize; y++)
            Draw((POINT){x, y}, Game.ChessBoard[x][y]);
}
void USER_INTERFACE::EnableMenu(int ID)
{
    EnableMenuItem(GetMenu(MainWindow), ID, MF_ENABLED | MF_BYCOMMAND);
}
void USER_INTERFACE::DisableMenu(int ID)
{
    EnableMenuItem(GetMenu(MainWindow), ID, MF_GRAYED | MF_BYCOMMAND);
}

void USER_INTERFACE::Init(HINSTANCE hInstance)
{
    Brush = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
    Font = CreateFont(17, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial");
    Accelerator = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR));

    WNDCLASSEX WindowsClassMain;
    WNDCLASSEX WindowsClassOptions;
    Game.UserInterface.MainInstance = hInstance;

    memset(&WindowsClassMain, 0, sizeof(WindowsClassMain));
    WindowsClassMain.cbSize = sizeof(WNDCLASSEX);
    WindowsClassMain.lpfnWndProc = [](HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) -> LRESULT CALLBACK
    {
        switch (Message)
        {
        case WM_CREATE:
        {
            Game.UserInterface.CreateInterface();
            Game.UserInterface.DrawDestination = GetWindowDC(hwnd);
            break;
        }
        case WM_MOVE:
        case WM_SIZE:
        {
            Game.UserInterface.DrawAll();
            break;
        }
        case WM_COMMAND:
        {
            Game.UserInterface.MenuCommand(wParam);
            break;
        }
        case WM_CTLCOLORSTATIC:
        {
            return (INT_PTR)Game.UserInterface.Brush;
        }
        case WM_MOUSEMOVE:
        {
            POINT Point = {(LOWORD(lParam) - Game.UserInterface.ChessBoardPosition.x) / ChessSize,
                           (HIWORD(lParam) - Game.UserInterface.ChessBoardPosition.y) / ChessSize};
            Game.MouseMove(Point);
            break;
        }
        case WM_LBUTTONUP:
        {
            POINT Point = {(LOWORD(lParam) - Game.UserInterface.ChessBoardPosition.x) / ChessSize,
                           (HIWORD(lParam) - Game.UserInterface.ChessBoardPosition.y) / ChessSize};
            Game.MouseUp(Point);
            break;
        }
        case WM_DESTROY:
        {
            Game.UserInterface.DestroyInterface();
            PostQuitMessage(0);
            break;
        }
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
        }
        return 0;
    };
    WindowsClassMain.hInstance = MainInstance;
    WindowsClassMain.hCursor = LoadCursor(nullptr, IDC_ARROW);
    WindowsClassMain.lpszMenuName = "ID_MAIN_MENU";

    WindowsClassMain.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    WindowsClassMain.lpszClassName = "MainWindow";
    WindowsClassMain.hIcon = LoadIcon(nullptr, MAKEINTRESOURCE(IDI_RESOURCE_ICON));
    WindowsClassMain.hIconSm = LoadIcon(nullptr, MAKEINTRESOURCE(IDI_RESOURCE_ICON));

    if (!RegisterClassEx(&WindowsClassMain))
    {
        MessageBox(nullptr, "Main window registration failed", "Error", MB_ICONERROR);
        return;
    }

    memset(&WindowsClassOptions, 0, sizeof(WindowsClassOptions));
    WindowsClassOptions.cbSize = sizeof(WNDCLASSEX);
    WindowsClassOptions.lpfnWndProc = [](HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) -> LRESULT CALLBACK
    {
        switch (Message)
        {
        case WM_CREATE:
        {
            Game.UserInterface.CreateOptionsInterface(hwnd);
            break;
        }
        case WM_COMMAND:
        {
            switch (wParam)
            {
            case OPTIONS_FIRST_COMPUTER:
            {
#warning
                break;
            }
            case OPTIONS_FIRST_PLAYER:
            {
#warning
                break;
            }
            case OPTIONS_SECOND_COMPUTER:
            {
#warning
                break;
            }
            case OPTIONS_SECOND_PLAYER:
            {
#warning
                break;
            }
            case OPTIONS_SAVE:
            {
                Game.UserInterface.OptionsSave();
                break;
            }
            }
        }
        case WM_CTLCOLORSTATIC:
        {
            return (INT_PTR)Game.UserInterface.Brush;
        }
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
        }
        return 0;
    };
    WindowsClassOptions.hInstance = hInstance;
    WindowsClassOptions.hCursor = LoadCursor(nullptr, IDC_ARROW);

    WindowsClassOptions.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    WindowsClassOptions.lpszClassName = "OptionsWindow";
    WindowsClassOptions.hIcon = LoadIcon(nullptr, MAKEINTRESOURCE(IDI_RESOURCE_ICON));
    WindowsClassOptions.hIconSm = LoadIcon(nullptr, MAKEINTRESOURCE(IDI_RESOURCE_ICON));

    if (!RegisterClassEx(&WindowsClassOptions))
    {
        MessageBox(nullptr, "Options window registration failed", "Error", MB_ICONERROR);
        return;
    }

    srand(time(nullptr));

    MainWindow = CreateWindowEx(WS_EX_CLIENTEDGE, "MainWindow", "Gomoku", WS_VISIBLE | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, Delta.x + ChessBoardPosition.x + Game.MapSize * ChessSize + 20, Delta.y + ChessBoardPosition.y + Game.MapSize * ChessSize + 20, nullptr, nullptr, hInstance, nullptr);
    if (MainWindow == nullptr)
    {
        MessageBox(nullptr, "Main window creation failed", "Error", MB_ICONERROR);
        return;
    }
}
WPARAM USER_INTERFACE::MessageLoop()
{
    MSG WindowsMessage;
    while (GetMessage(&WindowsMessage, nullptr, 0, 0) > 0)
    {
        if (!TranslateAccelerator(MainWindow, Accelerator, &WindowsMessage))
        {
            TranslateMessage(&WindowsMessage);
            DispatchMessage(&WindowsMessage);
        }
    }
    return WindowsMessage.wParam;
}
void USER_INTERFACE::CreateInterface()
{
    Output = CreateWindow("static", "Gomoku", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_CENTERIMAGE, 20, 20, 160, 20, MainWindow, nullptr, Game.UserInterface.MainInstance, nullptr);
    SendMessage(Output, WM_SETFONT, (WPARAM)Font, 0);

    PictureHandle = LoadBitmap(MainInstance, MAKEINTRESOURCE(IDB_RESOURCE_IMAGE));
    if (PictureHandle == nullptr)
    {
        MessageBox(MainWindow, "Can not load image resource", "Error", MB_ICONERROR);
        exit(0);
    }
    DrawSource = CreateCompatibleDC(DrawDestination);
    SelectObject(DrawSource, (HBITMAP)PictureHandle);
}
void USER_INTERFACE::MenuCommand(int ID)
{
    switch (LOWORD(ID))
    {
    case IDC_MENU_NEW_GAME:
    {
        Game.StartPlaying();
        DrawAll();
        break;
    }
    case IDC_MENU_END_GAME:
    {
        Game.StopPlaying();
        break;
    }
    case IDC_MENU_LOAD:
    {
        OPENFILENAME FileName;
        char FileNameBuffer[256];
        memset(&FileName, 0, sizeof(FileName));
        memset(FileNameBuffer, 0, sizeof(FileNameBuffer));
        FileName.lStructSize = sizeof(FileName);
        FileName.hwndOwner = MainWindow;
        FileName.lpstrFilter = "Gomoku Save File (*.gbs)\0*.gbs\0All Files (*.*)\0*.*\0";
        FileName.lpstrFile = FileNameBuffer;
        FileName.nMaxFile = sizeof(FileNameBuffer);
        FileName.lpstrDefExt = "gbs";
        FileName.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
        if (GetOpenFileName(&FileName))
            Game.Load(FileNameBuffer);
        break;
    }
    case IDC_MENU_SAVE:
    {
        OPENFILENAME FileName;
        char FileNameBuffer[256];
        memset(&FileName, 0, sizeof(FileName));
        memset(FileNameBuffer, 0, sizeof(FileNameBuffer));
        FileName.lStructSize = sizeof(FileName);
        FileName.hwndOwner = MainWindow;
        FileName.lpstrFilter = "Gomoku Save File (*.gbs)\0*.gbs\0All Files (*.*)\0*.*\0";
        FileName.lpstrFile = FileNameBuffer;
        FileName.nMaxFile = sizeof(FileNameBuffer);
        FileName.lpstrDefExt = "gbs";
        FileName.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
        if (GetSaveFileName(&FileName))
            Game.Save(FileNameBuffer);
        break;
    }
    case IDC_MENU_OPTIONS:
    {
        OptionsWindow = CreateWindowEx(WS_EX_CLIENTEDGE, "OptionsWindow", "Options", WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 260, 360, nullptr, nullptr, MainInstance, nullptr);
        if (OptionsWindow == nullptr)
        {
            MessageBox(nullptr, "Options window creation failed", "Error", MB_ICONERROR);
            return;
        }
        break;
    }
    case IDC_MENU_EXIT:
    {
        SendMessage(MainWindow, WM_CLOSE, 0, 0);
        break;
    }
    case IDC_MENU_ABOUT:
    {
        MessageBox(MainWindow, "Written by @langningchen on Github in C++", "About", MB_ICONINFORMATION);
    }
    }
}
void USER_INTERFACE::DestroyInterface()
{
    DeleteObject(Font);
    DeleteObject(PictureHandle);
    DeleteDC(DrawSource);
    ReleaseDC(MainWindow, DrawDestination);
}
void USER_INTERFACE::CreateOptionsInterface(HWND hwnd)
{
    OptionsWindow = hwnd;
    SizeGroupBox = CreateWindow("button", "Size option", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 20, 20, 200, 70, OptionsWindow, nullptr, MainInstance, nullptr);
    SizeStatic = CreateWindow("static", "Map size", WS_CHILD | WS_VISIBLE, 30, 40, 180, 20, OptionsWindow, nullptr, MainInstance, nullptr);
    SizeInput = CreateWindow("edit", "", WS_CHILD | WS_VISIBLE | ES_NUMBER, 30, 60, 180, 20, OptionsWindow, (HMENU)OPTIONS_SIZE, MainInstance, nullptr);
    FirstPlayerGroupBox = CreateWindow("button", "First Player", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 20, 110, 200, 70, OptionsWindow, nullptr, MainInstance, nullptr);
    FirstPlayerComputer = CreateWindow("button", "Computer", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 30, 130, 180, 20, OptionsWindow, (HMENU)OPTIONS_FIRST_COMPUTER, MainInstance, nullptr);
    FirstPlayerHuman = CreateWindow("button", "Human", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 30, 150, 180, 20, OptionsWindow, (HMENU)OPTIONS_FIRST_PLAYER, MainInstance, nullptr);
    SecondPlayerGroupBox = CreateWindow("button", "Second Player", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 20, 200, 200, 70, OptionsWindow, nullptr, MainInstance, nullptr);
    SecondPlayerComputer = CreateWindow("button", "Computer", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 30, 220, 180, 20, OptionsWindow, (HMENU)OPTIONS_SECOND_COMPUTER, MainInstance, nullptr);
    SecondPlayerHuman = CreateWindow("button", "Human", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 30, 240, 180, 20, OptionsWindow, (HMENU)OPTIONS_SECOND_PLAYER, MainInstance, nullptr);
    Submit = CreateWindow("button", "Save", WS_CHILD | WS_VISIBLE, 100, 280, 40, 20, OptionsWindow, (HMENU)OPTIONS_SAVE, MainInstance, nullptr);

    SendMessage(SizeGroupBox, WM_SETFONT, (WPARAM)Font, 0);
    SendMessage(SizeStatic, WM_SETFONT, (WPARAM)Font, 0);
    SendMessage(SizeInput, WM_SETFONT, (WPARAM)Font, 0);
    SendMessage(FirstPlayerGroupBox, WM_SETFONT, (WPARAM)Font, 0);
    SendMessage(FirstPlayerComputer, WM_SETFONT, (WPARAM)Font, 0);
    SendMessage(FirstPlayerHuman, WM_SETFONT, (WPARAM)Font, 0);
    SendMessage(SecondPlayerGroupBox, WM_SETFONT, (WPARAM)Font, 0);
    SendMessage(SecondPlayerComputer, WM_SETFONT, (WPARAM)Font, 0);
    SendMessage(SecondPlayerHuman, WM_SETFONT, (WPARAM)Font, 0);
    SendMessage(Submit, WM_SETFONT, (WPARAM)Font, 0);

    char Buffer[MAX_PATH];
    memset(Buffer, 0, sizeof(Buffer));
    itoa(Game.MapSize, Buffer, 10);
    SetWindowText(SizeInput, (LPSTR)Buffer);
    if (Game.Player1.Name == "Computer")
        SendMessage(FirstPlayerComputer, BM_SETCHECK, BST_CHECKED, 0);
    else
        SendMessage(FirstPlayerHuman, BM_SETCHECK, BST_CHECKED, 0);
    if (Game.Player2.Name == "Computer")
        SendMessage(SecondPlayerComputer, BM_SETCHECK, BST_CHECKED, 0);
    else
        SendMessage(SecondPlayerHuman, BM_SETCHECK, BST_CHECKED, 0);
}
void USER_INTERFACE::OptionsSave()
{
    char Buffer[MAX_PATH];
    memset(Buffer, 0, sizeof(Buffer));
    GetWindowText(SizeInput, (LPSTR)Buffer, MAX_PATH);
    int NewMapSize = atoi(Buffer);
    if (NewMapSize < 5)
    {
        SetWindowText(SizeInput, "5");
        MessageBox(OptionsWindow, "Set to the minimal map size 5", "Information", MB_ICONINFORMATION);
        NewMapSize = 5;
    }
    else if (NewMapSize > 30)
    {
        SetWindowText(SizeInput, "30");
        MessageBox(OptionsWindow, "Set to the maximal map size 30", "Information", MB_ICONINFORMATION);
        NewMapSize = 30;
    }
    Game.MapSize = NewMapSize;

    ResizeWindow(Game.MapSize);
    SendMessage(OptionsWindow, WM_CLOSE, 0, 0);
}
void USER_INTERFACE::ResizeWindow(int MapSize)
{
    SetWindowPos(MainWindow, nullptr, 0, 0, Delta.x + ChessBoardPosition.x + MapSize * ChessSize + 20, Delta.y + ChessBoardPosition.y + MapSize * ChessSize + 20, SWP_NOMOVE);
}
