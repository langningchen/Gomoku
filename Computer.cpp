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

#include "Computer.hpp"
#include "Game.hpp"
void COMPUTER::Match(int Role, int Left[5], int Right[5], const char LeftType[5], const char RightType[5], int &Output)
{
    bool Matched = true;
    for (int i = 3; Matched && i >= 0; i--)
    {
        if (LeftType[3 - i] == 'X' && Left[i] != Role)
            Matched = false;
        if (LeftType[3 - i] == ' ' && Left[i] != ROLE_BLANK)
            Matched = false;
    }
    for (int i = 0; Matched && i < 4; i++)
    {
        if (RightType[i] == 'X' && Right[i] != Role)
            Matched = false;
        if (RightType[i] == ' ' && Right[i] != ROLE_BLANK)
            Matched = false;
    }
    if (Matched)
        Output++;
}
int COMPUTER::GetScore(POINT Point, int Role)
{
    int Win5 = 0;
    int Alive4 = 0;
    int Die4 = 0;
    int Die4_Low = 0;
    int Alive3 = 0;
    int Alive3_Low = 0;
    int Die3 = 0;
    int Alive2 = 0;
    int Alive2_Low = 0;
    int Die2 = 0;
    for (int Direction = 0; Direction < 4; Direction++)
    {
        int ConnectedLength = 1;
        POINT ConnectedLeft, ConnectedRight, NewPosition;
        int Left[4], Right[4];
        NewPosition = Game.MovePoint(Point, Deltas[Direction], -1);
        ConnectedLeft = Point;
        while (Game.InBoard(NewPosition) && Game.ChessBoard[NewPosition.x][NewPosition.y] == Role)
        {
            ConnectedLeft = NewPosition;
            NewPosition = Game.MovePoint(NewPosition, Deltas[Direction], -1);
            ConnectedLength++;
        }
        NewPosition = Game.MovePoint(Point, Deltas[Direction], 1);
        ConnectedRight = Point;
        while (Game.InBoard(NewPosition) && Game.ChessBoard[NewPosition.x][NewPosition.y] == Role)
        {
            ConnectedRight = NewPosition;
            NewPosition = Game.MovePoint(NewPosition, Deltas[Direction], 1);
            ConnectedLength++;
        }
        for (int i = 0; i < 4; i++)
        {
            NewPosition = Game.MovePoint(ConnectedLeft, Deltas[Direction], -(i + 1));
            if (Game.InBoard(NewPosition))
                Left[i] = Game.ChessBoard[NewPosition.x][NewPosition.y];
            else
                Left[i] = Game.GetOthers(Role);
            NewPosition = Game.MovePoint(ConnectedRight, Deltas[Direction], i + 1);
            if (Game.InBoard(NewPosition))
                Right[i] = Game.ChessBoard[NewPosition.x][NewPosition.y];
            else
                Right[i] = Game.GetOthers(Role);
        }
        if (ConnectedLength == 5)
        {
            Match(Role, Left, Right, "?????", "?????", Win5);
        }
        else if (ConnectedLength == 4)
        {
            Match(Role, Left, Right, "??? ", " ???", Alive4);
            Match(Role, Left, Right, "??? ", "????", Die4);
            Match(Role, Left, Right, "????", " ???", Die4);
        }
        else if (ConnectedLength == 3)
        {
            Match(Role, Left, Right, "??X ", "????", Die4_Low);
            Match(Role, Left, Right, "????", " X??", Die4_Low);

            Match(Role, Left, Right, "??  ", " ???", Alive3);
            Match(Role, Left, Right, "??? ", "  ??", Alive3);

            Match(Role, Left, Right, "??  ", "????", Die3);
            Match(Role, Left, Right, "??? ", " ???", Die3);
            Match(Role, Left, Right, "????", "  ??", Die3);
        }
        else if (ConnectedLength == 2)
        {
            Match(Role, Left, Right, "?XX ", " XX?", Die4_Low);

            Match(Role, Left, Right, "? X ", " ???", Alive3_Low);
            Match(Role, Left, Right, "??? ", " X ?", Alive3_Low);

            Match(Role, Left, Right, "? X ", "????", Alive3);
            Match(Role, Left, Right, "????", " X ?", Alive3);

            Match(Role, Left, Right, "?X  ", "????", Die3);
            Match(Role, Left, Right, "??X ", " ???", Die3);
            Match(Role, Left, Right, "??? ", " X??", Die3);
            Match(Role, Left, Right, "????", "  X?", Die3);

            Match(Role, Left, Right, "?   ", " ???", Alive2);
            Match(Role, Left, Right, "??  ", "  ??", Alive2);
            Match(Role, Left, Right, "??? ", "   ?", Alive2);

            Match(Role, Left, Right, "?   ", "????", Die2);
            Match(Role, Left, Right, "????", "   ?", Die2);
        }
        else if (ConnectedLength == 1)
        {
            Match(Role, Left, Right, "XXX ", "????", Die4_Low);
            Match(Role, Left, Right, "????", " XXX", Die4_Low);

            Match(Role, Left, Right, " XX ", " ???", Alive3_Low);
            Match(Role, Left, Right, "??? ", " XX ", Alive3_Low);

            Match(Role, Left, Right, "?XX ", " ???", Die3);
            Match(Role, Left, Right, "??? ", " XX?", Die3);
            Match(Role, Left, Right, "XX  ", "????", Die3);
            Match(Role, Left, Right, " XX ", "????", Die3);
            Match(Role, Left, Right, "????", " XX ", Die3);
            Match(Role, Left, Right, "????", "  XX", Die3);
            Match(Role, Left, Right, "X X ", "????", Die3);
            Match(Role, Left, Right, "????", " X X", Die3);

            Match(Role, Left, Right, "? X ", "  ??", Alive2_Low);
            Match(Role, Left, Right, "??  ", " X ?", Alive2_Low);
            Match(Role, Left, Right, " X  ", " ???", Alive2_Low);
            Match(Role, Left, Right, "  X ", " ???", Alive2_Low);
            Match(Role, Left, Right, "??? ", " X  ", Alive2_Low);
            Match(Role, Left, Right, "??? ", "  X ", Alive2_Low);

            Match(Role, Left, Right, "?X  ", " ???", Die2);
            Match(Role, Left, Right, "??X ", "  ??", Die2);
            Match(Role, Left, Right, "??  ", " X??", Die2);
            Match(Role, Left, Right, "??? ", "  X?", Die2);
            Match(Role, Left, Right, "X   ", "????", Die2);
            Match(Role, Left, Right, " X  ", "????", Die2);
            Match(Role, Left, Right, "  X ", "????", Die2);
            Match(Role, Left, Right, "????", " X  ", Die2);
            Match(Role, Left, Right, "????", "  X ", Die2);
            Match(Role, Left, Right, "????", "   X", Die2);
        }
    }
    if (Win5 >= 1)
        return 14;
    if (Alive4 >= 1)
        return 13;
    if (Die4 >= 2)
        return 13;
    if (Die4 >= 1 && Alive3 >= 1)
        return 13;
    if (Alive3 >= 2)
        return 12;
    if (Die3 >= 1 && Alive3 >= 1)
        return 11;
    if (Die4 >= 1)
        return 10;
    if (Die4_Low >= 1)
        return 9;
    if (Alive3 >= 1)
        return 8;
    if (Alive3_Low >= 1)
        return 7;
    if (Alive2 >= 2)
        return 6;
    if (Alive2 >= 1)
        return 5;
    if (Alive2_Low >= 1)
        return 4;
    if (Die3 >= 1)
        return 3;
    if (Die2 >= 1)
        return 2;
    return 1;
}
POINT COMPUTER::Play()
{
    if (Game.PlayHistory.size() == 0)
        return (POINT){(Game.MapSize - 1) / 2, (Game.MapSize - 1) / 2};
    Sleep(500);
    POINT MyPosition, EnemyPosition;
    int MyPositionMyScore = 0;
    int MyPositionEnemyScore = 0;
    int EnemyPositionMyScore = 0;
    int EnemyPositionEnemyScore = 0;
    for (int x = 0; x < Game.MapSize; x++)
        for (int y = 0; y < Game.MapSize; y++)
            if (Game.ChessBoard[x][y] == ROLE_BLANK)
            {
                POINT NewPosition;
                NewPosition.x = x;
                NewPosition.y = y;
                int NewMyScore = GetScore(NewPosition, MyRole);
                int NewEnemyScore = GetScore(NewPosition, Game.GetOthers(MyRole));
                if ((NewMyScore > MyPositionMyScore) ||
                    (NewMyScore == MyPositionMyScore && NewEnemyScore > MyPositionEnemyScore))
                {
                    MyPosition = NewPosition;
                    MyPositionMyScore = NewMyScore;
                    MyPositionEnemyScore = NewEnemyScore;
                }
                if ((NewEnemyScore > EnemyPositionEnemyScore) ||
                    (NewEnemyScore == EnemyPositionEnemyScore && NewMyScore > EnemyPositionMyScore))
                {
                    EnemyPosition = NewPosition;
                    EnemyPositionMyScore = NewMyScore;
                    EnemyPositionEnemyScore = NewEnemyScore;
                }
            }
    return MyPositionMyScore >= EnemyPositionEnemyScore ? MyPosition : EnemyPosition;
}
void COMPUTER::MouseMove(POINT Point) {}
void COMPUTER::MouseUp(POINT Point) {}
