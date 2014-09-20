#include "stdafx.h"
#include "Draw.h"
#include <windows.h>
#include <conio.h>

#define MAPONEWIDTH 2
#define MAPSIZE 15 // MAPONEWIDE*2-1
#define MAPHEIGHT MAPSIZE*1
#define MAPWIDE MAPSIZE*2+2
#define MAPHLINENUM 9
#define MAPHLINEWIDE MAPONEWIDTH*2

#define MAPROOMNUM 8





Draw::Draw()
{
}


Draw::~Draw()
{
}

void Draw::GoTo(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Draw::GoTo(Position pos)
{
	GoTo(pos.x, pos.y);
}

void Draw::SetLetterColor(Color color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Draw::DrawMap()
{
	GoTo(MAP1X, MAP1Y);
	printf_s("┏");
	for (int i = 0; i < MAPSIZE; ++i)
	{
		if ((i+1) % MAPONEWIDTH == 0)
		{
			printf_s("┳");
		}
		else
		{
			printf_s("━");
		}
		
	}

	printf_s("┓"); // 여기 까지 맨 윗 줄 그리기

	for (int i = 0; i < MAPSIZE; ++i)
	{
		GoTo(MAP1X, MAP1Y+1 + i);

		if ((i + 1) % MAPONEWIDTH == 0)
		{
			printf_s("┣");

			for (int j = 0; j < MAPSIZE; ++j)
			{
				printf_s("━"); // 가로줄 그리기
			}
		}
		else
		{
			printf_s("┃");
		}
	} // 맨 왼쪽 줄 + 가로줄 그리기

	for (int i = 1; i < MAPHLINENUM-1; ++i)
	{
		for (int j = 0; j < MAPSIZE; ++j)
		{
			GoTo(MAP1X+i*MAPHLINEWIDE, MAP1Y+1 + j);

			if ((j + 1) % MAPONEWIDTH == 0)
			{
				printf_s("╋"); // 중간 십자가
			}
			else
			{
				printf_s("┃");
			}
		}
	} //세로줄 그리기
	

	for (int i = 0; i < MAPSIZE; ++i)
	{
		GoTo(MAP1X + MAPWIDE, MAP1Y+1 + i);

		if ((i + 1) % MAPONEWIDTH == 0)
		{
			printf_s("┫");
		}
		else
		{
			printf_s("┃");
		}
	} // 맨 오른쪽 줄 


	GoTo(MAP1X, MAP1Y + 1 + MAPHEIGHT);
	printf_s("┗");

	for (int i = 0; i < MAPSIZE; ++i)
	{
		if ((i + 1) % MAPONEWIDTH == 0)
		{
			printf_s("┻");
		}
		else
		{
			printf_s("━");
		}

	}

	printf_s("┛"); // 여기까지 맨 밑줄 그리기

	
	GoTo(MAP2X, MAP2Y);
	printf_s("┏");
	for (int i = 0; i < MAPSIZE; ++i)
	{
		if ((i + 1) % MAPONEWIDTH == 0)
		{
			printf_s("┳");
		}
		else
		{
			printf_s("━");
		}

	}

	printf_s("┓"); // 여기 까지 맨 윗 줄 그리기

	for (int i = 0; i < MAPSIZE; ++i)
	{
		GoTo(MAP2X, MAP2Y+1 + i);

		if ((i + 1) % MAPONEWIDTH == 0)
		{
			printf_s("┣");

			for (int j = 0; j < MAPSIZE; ++j)
			{
				printf_s("━"); // 가로줄 그리기
			}
		}
		else
		{
			printf_s("┃");
		}
	} // 맨 왼쪽 줄 + 가로줄 그리기

	for (int i = 1; i < MAPHLINENUM - 1; ++i)
	{
		for (int j = 0; j < MAPSIZE; ++j)
		{
			GoTo(MAP2X + i*MAPHLINEWIDE, MAP2Y+1 + j);

			if ((j + 1) % MAPONEWIDTH == 0)
			{
				printf_s("╋"); // 중간 십자가
			}
			else
			{
				printf_s("┃");
			}
		}
	} //세로줄 그리기


	for (int i = 0; i < MAPSIZE; ++i)
	{
		GoTo(MAP2X + MAPWIDE, MAP2Y+1 + i);

		if ((i + 1) % MAPONEWIDTH == 0)
		{
			printf_s("┫");
		}
		else
		{
			printf_s("┃");
		}
	} // 맨 오른쪽 줄 


	GoTo(MAP2X, MAP2Y+1 + MAPHEIGHT);
	printf_s("┗");

	for (int i = 0; i < MAPSIZE; ++i)
	{
		if ((i + 1) % MAPONEWIDTH == 0)
		{
			printf_s("┻");
		}
		else
		{
			printf_s("━");
		}

	}

	printf_s("┛"); // 여기까지 맨 밑줄 그리기


}

void Draw::DrawWillBeShip(int shipHp, Position pos, Direction direct)
{
	int addX = (pos.x-'a') * 4;
	int addY = (pos.y-'0') * 2;

	switch (direct)
	{
	case EAST:

		for (int i = 0; i < shipHp; ++i)
		{

			addX = (pos.x - 'a') * 4;
			GoTo(MAP1X + 2 + addX, MAP1Y + 1+addY);
			printf_s("■");
			pos.x = pos.x + 1;
		}
		break;

	case WEST:

		for (int i = 0; i < shipHp; ++i)
		{
			addX = (pos.x - 'a') * 4;
			GoTo(MAP1X + 2 + addX, MAP1Y + 1+addY);
			printf_s("■");
			pos.x = pos.x - 1;
		}
		break;

	case SOUTH:

		for (int i = 0; i < shipHp; ++i)
		{
			addY = (pos.y - '0') * 2;
			GoTo(MAP1X + 2+addX, MAP1Y + 1 + addY);
			printf_s("■");
			pos.y = pos.y + 1;
		}
		break;

	case NORTH:

		for (int i = 0; i < shipHp; ++i)
		{
			addY = (pos.y - '0') * 2;
			GoTo(MAP1X + 2+addX, MAP1Y + 1 + addY);
			printf_s("■");
			pos.y = pos.y - 1;
		}
		break;

	default:
		break;
	}
}

void Draw::WirteShipList(int num, std::string shipName)
{
	GoTo(SHIPLISTX, SHIPLISTY+num*2);
	printf_s("%s", shipName.c_str());

}

void Draw::EraseWillBeShip(int shipHp, Position pos, Direction direct)
{
	int addX = (pos.x - 'a') * 4;
	int addY = (pos.y - '0') * 2;

	switch (direct)
	{
	case EAST:

		for (int i = 0; i < shipHp; ++i)
		{

			addX = (pos.x - 'a') * 4;
			GoTo(MAP1X + 2 + addX, MAP1Y + 1);
			printf_s(" ");
			pos.x = pos.x + 1;
		}
		break;

	case WEST:

		for (int i = 0; i < shipHp; ++i)
		{
			addX = (pos.x - 'a') * 4;
			GoTo(MAP1X + 2 + addX, MAP1Y + 1);
			printf_s(" ");
			pos.x = pos.x - 1;
		}
		break;

	case SOUTH:

		for (int i = 0; i < shipHp; ++i)
		{
			addY = (pos.y - '0') * 2;
			GoTo(MAP1X + 2, MAP1Y + 1 + addY);
			printf_s(" ");
			pos.y = pos.y + 1;
		}
		break;

	case NORTH:

		for (int i = 0; i < shipHp; ++i)
		{
			addY = (pos.y - '0') * 2;
			GoTo(MAP1X + 2, MAP1Y + 1 + addY);
			printf_s(" ");
			pos.y = pos.y - 1;
		}
		break;

	default:
		break;
	}
}

void Draw::DrawMap1inside(Position pos, WhatDraw shape)
{
	int AddX = (pos.x - 'a') * 4;
	int AddY = (pos.y - '0') * 2;
	GoTo(MAP1X + 2 + AddX, MAP1Y + 1 + AddY);

	switch (shape)
	{
	case ERASE:
		printf_s(" ");
		break;
	case SQUARE:
		printf_s("■");
		break;

	case ECSE:
		printf_s("Ⅹ");
	}
	
}

void Draw::DrawMap1inside(Position pos, MapDataTypes shipType)
{
	int AddX = (pos.x - 'a') * 4;
	int AddY = (pos.y - '0') * 2;
	GoTo(MAP1X + 2 + AddX, MAP1Y + 1 + AddY);

	switch (shipType)
	{
	case MD_AIRCRAFT:
		printf_s("Ａ");
		break;
	case MD_BATTLESHIP:
		printf_s("B");
		break;
	case MD_CRUISER:
		printf_s("C");
		break;
	}

	if (shipType == MD_DESTROYER1 || shipType == MD_DESTROYER2)
	{
		printf_s("D");
	}
}

void Draw::DrawMap1inside(Position pos, Map_Status status)
{
	int AddX = (pos.x - 'a') * 4;
	int AddY = (pos.y - '0') * 2;
	GoTo(MAP1X + 2 + AddX, MAP1Y + 1 + AddY);

	switch (status)
	{
	case NOTHING:
		printf_s(" ");
		break;
	case A:
		printf_s("Ａ");
		break;
	case B:
		printf_s("B");
		break;
	case C:
		printf_s("C");
		break;
	case D:
		printf_s("D");
		break;
	}
}

void Draw::DrawMap2inside(Position pos, WhatDraw shape)
{
	int AddX = (pos.x - 'a') * 4;
	int AddY = (pos.y - '0') * 2;
	GoTo(MAP2X + 2 + AddX, MAP2Y + 1 + AddY);

	switch (shape)
	{
	case ERASE:
		printf_s(" ");
		break;
	case SQUARE:
		printf_s("■");
		break;

	case ECSE:
		printf_s("Ⅹ");
	}
}

void Draw::DrawMap2inside(Position pos, Map_Status status)
{
	int AddX = (pos.x - 'a') * 4;
	int AddY = (pos.y - '0') * 2;
	GoTo(MAP1X + 2 + AddX, MAP1Y + 1 + AddY);

	switch (status)
	{
	case NOTHING:
		printf_s(" ");
		break;
	case A:
		printf_s("Ａ");
		break;
	case B:
		printf_s("B");
		break;
	case C:
		printf_s("C");
		break;
	case D:
		printf_s("D");
		break;
	}
}

void Draw::SetLetterColor(Map_Status status)
{
	switch (status)
	{
	case NOTHING:
		SetLetterColor(WHITE);
		break;
	case MAP_HIT:
		SetLetterColor(BRIGHTRED);
		break;
	case MAP_DESTROY:
		SetLetterColor(RED);
		break;
	default:
		SetLetterColor(WHITE);
		break;
	}
}
