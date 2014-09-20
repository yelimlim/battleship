#pragma once
#include "struct.h"
#include <string>
class Draw
{
public:
	Draw();
	~Draw();

	void GoTo(int x, int y);
	void GoTo(Position pos);

	void DrawMap();
	void WirteShipList(int num, std::string shipName);
	void DrawMap1inside(Position pos, Map_Status status);
	void DrawMap2inside(Position pos, Map_Status status);
	void DrawMap1inside(Position pos, WhatDraw shape);
	void DrawMap2inside(Position pos, WhatDraw shape);
	void DrawMap1inside(Position pos, MapDataTypes shipType);
	void DrawWillBeShip(int shipHp, Position pos, Direction direct);
	void EraseWillBeShip(int shipHp, Position pos, Direction direct);

	void SetLetterColor(Map_Status status);
	void SetLetterColor(Color color);

private:
	
};

