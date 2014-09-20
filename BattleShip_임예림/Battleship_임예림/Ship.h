#pragma once
#include <string>
#include "struct.h"

enum ShipType
{
	SHIP_NONE,
	AIRCRAFT,
	BATTLESHIP,
	CRUISER,
	DESTROYER,
};

std::string result[] = { "HIT", "MISS", "DESTROY" };

class Ship
{
public:
	Ship();
	~Ship();

	void AddPosiotion(Position pos);
	std::string HitCheck(Position pos);
	int GetHP() { return m_Hp; }
	void Print();

protected:
	std::string m_Name;
	ShipType m_Type;
	Position m_ShipPosion;
	Direction m_ShipDirection;
	int m_Hp;
};

