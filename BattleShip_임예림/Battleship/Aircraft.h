#pragma once
#include "Ship.h"
class Aircraft :
	public Ship
{
public:
	Aircraft();
	~Aircraft();

	AttackResult HitCheck(Position pos);
};

