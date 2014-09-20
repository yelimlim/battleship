#include "stdafx.h"
#include "Aircraft.h"
#include "struct.h"


Aircraft::Aircraft()
{
	m_Type = MD_AIRCRAFT;
	m_Hp = AIRCRAFTLENGTH;
	m_Size = AIRCRAFTLENGTH;
	m_Name = "Aircraft";
}


Aircraft::~Aircraft()
{
}

AttackResult Aircraft::HitCheck(Position pos)
{
	AttackResult result = Ship::HitCheck(pos);
	
	return (result == AR_DESTROY_AIRCRAFT) ? AR_DESTROY_AIRCRAFT : result;
}