#include "stdafx.h"
#include "Cruiser.h"
#include "struct.h"


Cruiser::Cruiser()
{
	m_Hp = CRUISERLENGTH;
	m_Size = CRUISERLENGTH;
	m_Name = "Cruiser";
	m_Type = MD_CRUISER;
}


Cruiser::~Cruiser()
{
}

AttackResult Cruiser::HitCheck(Position pos)
{
	AttackResult result = Ship::HitCheck(pos);

	return (result == AR_DESTROY_AIRCRAFT) ? AR_DESTROY_CRUISER : result;
}
