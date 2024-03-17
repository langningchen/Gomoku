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

#include "Human.hpp"
#include "Game.hpp"
POINT HUMAN::Play()
{
    PlayPoint = {-1, -1};
    while (PlayPoint.x == -1 && PlayPoint.y == -1 && Game.Playing)
        Sleep(100);
    return PlayPoint;
}
void HUMAN::MouseMove(POINT Point)
{
    Game.UserInterface.DrawAll();
    if (Game.InBoard(Point) && Game.ChessBoard[Point.x][Point.y] == ROLE_BLANK)
    {
        if (MyRole == ROLE_BLACK)
            Game.UserInterface.Draw(Point, 3);
        else
            Game.UserInterface.Draw(Point, 4);
    }
}
void HUMAN::MouseUp(POINT Point)
{
    if (Game.InBoard(Point) && Game.ChessBoard[Point.x][Point.y] == ROLE_BLANK)
        PlayPoint = Point;
}
