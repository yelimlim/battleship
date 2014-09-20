#include "stdafx.h"
#include "BattleShip_.h"
#include "struct.h"


BattleShip_::BattleShip_()
{
	m_Hp = BATTLESHIPLENGTH;
	m_Size = BATTLESHIPLENGTH;
	m_Name = "BattleShip";
	m_Type = MD_BATTLESHIP;
}


BattleShip_::~BattleShip_()
{
}

AttackResult BattleShip_::HitCheck(Position pos)
{
	AttackResult result = Ship::HitCheck(pos);

	return (result == AR_DESTROY_AIRCRAFT) ? AR_DESTROY_BATTLESHIP : result;
}
