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

#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include "Resource.hpp"
#include "Game.hpp"
using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Game.UserInterface.Init(hInstance);
	return Game.UserInterface.MessageLoop();
}
