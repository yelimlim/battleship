#pragma once
#include "Ship.h"
class Destroyer :
	public Ship
{
public:
	Destroyer();
	Destroyer(int shipNum);
	~Destroyer();

	AttackResult HitCheck(Position pos);
};

