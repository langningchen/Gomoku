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

#pragma once
#include "Resource.hpp"
class USER_INTERFACE
{
public:
    POINT Delta = {6, 49};
    POINT ChessBoardPosition = {20, 40};
    HBRUSH Brush;
    HFONT Font;
    HACCEL Accelerator;

    HANDLE PictureHandle;
    HDC DrawDestination;
    HDC DrawSource;
    HINSTANCE MainInstance;
    HWND MainWindow;
    HWND Output;

    HWND OptionsWindow;
    HWND SizeGroupBox;
    HWND SizeStatic;
    HWND SizeInput;
    HWND FirstPlayerGroupBox;
    HWND FirstPlayerComputer;
    HWND FirstPlayerHuman;
    HWND SecondPlayerGroupBox;
    HWND SecondPlayerComputer;
    HWND SecondPlayerHuman;
    HWND Submit;

    void Draw(POINT Point, int Index);
    void DrawAll();
    void EnableMenu(int ID);
    void DisableMenu(int ID);

    void Init(HINSTANCE hInstance);
    WPARAM MessageLoop();
    void ResizeWindow(int MapSize);

    void CreateInterface();
    void MenuCommand(int ID);
    void DestroyInterface();

    void CreateOptionsInterface(HWND hwnd);
    void OptionsSave();
};
