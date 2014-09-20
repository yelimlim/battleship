#include <string>
#include "stdafx.h"
#include "Ship.h"
#include "struct.h"


Ship::Ship()
{
	//�ʱ�ȭ
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
	//���̸� ���
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

void Ship::AddPosition(Position pos) //�� ��ġ
{
	//�� �迭 ĭ�� position ����
	for (int i = 0; i < m_Size; ++i)
	{
		if (m_ShipPosition[i].x == 0)
		{
			m_ShipPosition[i] = pos;
			break;
		}
	}
}

//AddPosition �����ε� : Position x y ���� �Է� �� �� �ֵ���
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
	//�ʱ�ȭ
	m_Hp = m_Size;

	for (int i = 0; i < m_Size; ++i)
	{
		m_ShipPosition[i].x = 0;
		m_ShipPosition[i].y = 0;
	}
}


