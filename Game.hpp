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
#include <vector>
#include "Resource.hpp"
#include "UserInterface.hpp"
#include "Human.hpp"
#include "Computer.hpp"
#include <iostream>
#include <thread>
using namespace std;

const int MAX_SIZE = 35;
const POINT Deltas[8] = {{-1, -1},
                         {-1, 0},
                         {-1, 1},
                         {0, -1},
                         {0, 1},
                         {1, -1},
                         {1, 0},
                         {1, 1}};
const int ChessSize = 32;

class GAME
{
public:
    thread GameThread;
    COMPUTER Player1;
    // HUMAN Player1;
    // COMPUTER Player2;
    HUMAN Player2;
    int Turn;
    USER_INTERFACE UserInterface;
    bool Playing;
    POINT LastChessPosition;
    int ChessBoard[MAX_SIZE][MAX_SIZE];
    int MapSize = 15;
    vector<POINT> PlayHistory;
    void StartPlaying();
    void StopPlaying();
    bool InBoard(POINT Point);
    POINT MovePoint(POINT OldPoint, POINT Delta, int length);
    int GetOthers(int Role);
    bool IsWin();
    bool IsFull();
    void PlaceChess(POINT Point, int Role = -1);
    void MouseMove(POINT Point);
    void MouseUp(POINT Point);
    void Save(string FileName);
    void Load(string FileName);
};

extern GAME Game;
