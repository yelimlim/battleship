#include "stdafx.h"
#include "Ship.h"
#include <string>


Ship::Ship()
{
	m_Hp = 0;
	m_Name = "";
	m_Type = SHIP_NONE;
	m_ShipPosion = { 0, 0 };
	m_ShipDirection = DIRECTION_NONE;
}


Ship::~Ship()
{
}

std::string Ship::HitCheck(Position pos)
{
	for (int i = 0; i < m_Hp; i++)
	{
		if (m_ShipDirection == EAST)
		{
			if (m_ShipPosion.y == pos.y)
			{
				if (m_ShipPosion.x + i == pos.x)
				{
					m_Hp--;
					return "HIT";
				}

			}

		}
		else if (m_ShipDirection == WEST)
		{
			if (m_ShipPosion.y == pos.y)
			{
				if (m_ShipPosion.x - i == pos.x)
				{
					m_Hp--;
					return "HIT";
				}

			}

		}
		else if (m_ShipDirection == NORTH)
		{
			if (m_ShipPosion.x == pos.x)
			{
				if (m_ShipPosion.y + i == pos.y)
				{
					m_Hp--;
					return "HIT";
				}

			}

		}
		else if (m_ShipDirection == SOUTH)
		{
			if (m_ShipPosion.x == pos.x)
			{
				if (m_ShipPosion.y - i == pos.y)
				{
					m_Hp--;
					return "HIT";
				}

			}

		}
	}

	return "MISS";
}

void Ship::AddPosiotion(Position pos)
{

}

void Ship::Print()
{

}
