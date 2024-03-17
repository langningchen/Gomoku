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

#include "Game.hpp"
void GAME::StartPlaying()
{
    memset(ChessBoard, 0, sizeof(ChessBoard));
    PlayHistory.clear();
    Playing = true;
    Player1.MyRole = ROLE_BLACK;
    Player2.MyRole = ROLE_WHITE;
    UserInterface.DisableMenu(IDC_MENU_NEW_GAME);
    UserInterface.DisableMenu(IDC_MENU_LOAD);
    UserInterface.DisableMenu(IDC_MENU_OPTIONS);
    UserInterface.EnableMenu(IDC_MENU_END_GAME);
    GameThread = thread(
        [this]()
        {
            while (1)
            {
                Turn = GetOthers(Turn);
                SetWindowText(UserInterface.Output, ((Turn == ROLE_BLACK ? Player1.Name : Player2.Name) + "'s turn").c_str());
                PlaceChess(Turn == ROLE_BLACK ? Player1.Play() : Player2.Play());
                UserInterface.DrawAll();
                if (!Playing)
                    return;
                if (IsWin())
                {
                    StopPlaying();
                    SetWindowText(UserInterface.Output, ((Turn == ROLE_BLACK ? Player1.Name : Player2.Name) + " win").c_str());
                    return;
                }
                if (IsFull())
                {
                    StopPlaying();
                    SetWindowText(UserInterface.Output, "Draw");
                    return;
                }
            }
        });
    GameThread.detach();
}
void GAME::StopPlaying()
{
    Playing = false;
    UserInterface.EnableMenu(IDC_MENU_NEW_GAME);
    UserInterface.EnableMenu(IDC_MENU_LOAD);
    UserInterface.EnableMenu(IDC_MENU_OPTIONS);
    UserInterface.DisableMenu(IDC_MENU_END_GAME);
}
bool GAME::InBoard(POINT Point)
{
    return Point.x >= 0 && Point.x < MapSize && Point.y >= 0 && Point.y < MapSize;
}
POINT GAME::MovePoint(POINT OldPoint, POINT Delta, int length)
{
    return {OldPoint.x + Delta.x * length, OldPoint.y + Delta.y * length};
}
int GAME::GetOthers(int Role)
{
    return (Role == ROLE_BLACK) ? ROLE_WHITE : ROLE_BLACK;
}
bool GAME::IsWin()
{
    for (int Direction = 0; Direction < 8; Direction++)
    {
        int ConnectedCount = 0;
        for (int j = -4; j <= 4; j++)
        {
            POINT NewPoint = MovePoint(LastChessPosition, Deltas[Direction], j);
            if (InBoard(NewPoint) &&
                ChessBoard[NewPoint.x][NewPoint.y] == ChessBoard[LastChessPosition.x][LastChessPosition.y])
                ConnectedCount++;
            else
                ConnectedCount = 0;
            if (ConnectedCount == 5)
            {
                return true;
            }
        }
    }
    return false;
}
bool GAME::IsFull()
{
    for (int i = 0; i < MapSize; i++)
        for (int j = 0; j < MapSize; j++)
            if (ChessBoard[i][j] == ROLE_BLANK)
                return false;
    return true;
}
void GAME::PlaceChess(POINT Point, int Role)
{
    if (Role == -1)
        Role = Turn;
    if (Point.x == -1 && Point.y == -1)
        return;
    LastChessPosition = Point;
    ChessBoard[Point.x][Point.y] = Role;
    PlayHistory.push_back(Point);
}
void GAME::MouseMove(POINT Point)
{
    if (Playing)
    {
        if (Turn == ROLE_BLACK)
            Player1.MouseMove(Point);
        else
            Player2.MouseMove(Point);
    }
}
void GAME::MouseUp(POINT Point)
{
    if (Playing)
    {
        if (Turn == ROLE_BLACK)
            Player1.MouseUp(Point);
        else
            Player2.MouseUp(Point);
    }
}
void GAME::Save(string FileName)
{
    FILE *File = fopen(FileName.c_str(), "wb");
    if (File == nullptr)
    {
        MessageBox(NULL, "Can not open file", "Error", MB_ICONERROR);
        return;
    }
    fwrite(&MapSize, sizeof(MapSize), 1, File);
    int HistorySize = PlayHistory.size();
    fwrite(&HistorySize, sizeof(HistorySize), 1, File);
    for (int i = 0; i < HistorySize; i++)
        fwrite(&PlayHistory[i], sizeof(PlayHistory[i]), 1, File);
    fclose(File);
}
void GAME::Load(string FileName)
{
    FILE *File = fopen(FileName.c_str(), "rb");
    if (File == nullptr)
    {
        MessageBox(NULL, "Can not open file", "Error", MB_ICONERROR);
        return;
    }
    Game.StopPlaying();
    fread(&MapSize, sizeof(MapSize), 1, File);
    UserInterface.ResizeWindow(MapSize);
    Game.StartPlaying();
    int HistorySize = 0;
    fread(&HistorySize, sizeof(HistorySize), 1, File);
    for (int i = 0; i < HistorySize; i++)
    {
        POINT Position;
        fread(&Position, sizeof(Position), 1, File);
        Game.PlaceChess(Position, i % 2 == 0 ? ROLE_BLACK : ROLE_WHITE);
    }
    fclose(File);
    Turn = HistorySize % 2;
}

GAME Game;
