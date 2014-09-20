#pragma once
#include "Ship.h"
class BattleShip_ :
	public Ship
{
public:
	BattleShip_();
	~BattleShip_();

	AttackResult HitCheck(Position pos);
};


