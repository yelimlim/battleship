#include <string>
#include "stdafx.h"
#include "Ship.h"
#include "struct.h"


Ship::Ship()
{
	//초기화
	m_Hp = 0;
	m_Size = 0;
	m_Name = "";
	m_Type = MD_NONE;

	for (int i = 0; i < MAX_LENGTH; ++i)
	{
		m_ShipPosition[i].x = 0;
		m_ShipPosition[i].y = 0;
	}
}


Ship::~Ship()
{
}

void Ship::Print()
{
	//배이름 출력
	printf_s("%s : ", m_Name.c_str());

	for (int i = 0; i < m_Size; ++i)
	{
		if (m_ShipPosition != 0)
		{
			printf_s("%c%c ", m_ShipPosition[i].x, m_ShipPosition[i].y);
		}
	}
	printf_s("\n");
};

void Ship::AddPosition(Position pos) //배 배치
{
	//빈 배열 칸에 position 저장
	for (int i = 0; i < m_Size; ++i)
	{
		if (m_ShipPosition[i].x == 0)
		{
			m_ShipPosition[i] = pos;
			break;
		}
	}
}

//AddPosition 오버로딩 : Position x y 따로 입력 할 수 있도록
void Ship::AddPosition(char x, char y)
{
	Position pos;

	pos.x = x;
	pos.y = y;

	AddPosition(pos);
}

void Ship::ResetPosition()
{
	for (int i = 0; i < m_Size; ++i)
	{
		m_ShipPosition[i].x = 0;
		m_ShipPosition[i].y = 0;
	}
}

AttackResult Ship::HitCheck(Position pos)
{
	AttackResult result = AR_MISS;

	for (int i = 0; i < m_Size; ++i)
	{
		if (m_ShipPosition[i].x == pos.x&&m_ShipPosition[i].y==pos.y)
		{
			m_Hp--;
			result = AR_HIT;

			if (m_Hp == 0)
			{
				result = AR_DESTROY_AIRCRAFT;
			}
			
		}
		
	}

	return result;
}

void Ship::shipInit()
{
	//초기화
	m_Hp = m_Size;

	for (int i = 0; i < m_Size; ++i)
	{
		m_ShipPosition[i].x = 0;
		m_ShipPosition[i].y = 0;
	}
}


