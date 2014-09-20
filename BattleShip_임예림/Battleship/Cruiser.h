#pragma once
#include "Ship.h"
class Cruiser :
	public Ship
{
public:
	Cruiser();
	~Cruiser();

	AttackResult HitCheck(Position pos);
};

