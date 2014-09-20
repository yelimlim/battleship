#include "stdafx.h"
#include "Destroyer.h"
#include "struct.h"


Destroyer::Destroyer()
{
	m_Hp = DESTROYERLENGTH;
	m_Size = DESTROYERLENGTH;
	m_Name = "Destroyer";
	m_Type = MD_DESTROYER1;

}

Destroyer::Destroyer(int shipNum)
{
	// 생성자 오버로드 : Destroyer 끼리 구분을 위해 / 네트워크 연결을 위해 
	this->Destroyer::Destroyer();

	if (shipNum == 1)
	{
		m_Type = MD_DESTROYER1;
	}
	else if (shipNum == 2)
	{
		m_Type = MD_DESTROYER2;
	}
}



Destroyer::~Destroyer()
{
}

AttackResult Destroyer::HitCheck(Position pos)
{
	AttackResult result = Ship::HitCheck(pos);

	return (result == AR_DESTROY_AIRCRAFT) ? AR_DESTROY_DESTROYER : result;
}
