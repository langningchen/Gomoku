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
#include <string>
using namespace std;
class COMPUTER
{
private:
    void Match(int Role, int Left[5], int Right[5], const char LeftType[5], const char RightType[5], int &Output);
    int GetScore(POINT Point, int Role);

public:
    int MyRole;
    string Name = "Computer";
    POINT Play();
    void MouseMove(POINT Point);
    void MouseUp(POINT Point);
};
