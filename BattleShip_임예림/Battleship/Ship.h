#pragma once
#include <string>
#include "struct.h"

class Ship
{
public:
	Ship();
	~Ship();
	
	void			AddPosition(Position pos);
	void			AddPosition(char x, char y);
	AttackResult	HitCheck(Position pos);
	void			Print();
	
	int			GetHp(){ return m_Hp; }; //Hp ���
	int			GetSize() { return m_Size; }; //Size ���
	std::string	GetName(){ return m_Name; }; //�̸� ���
	Position*	GetShipPosition(){ return m_ShipPosition; };
	MapDataTypes	GetShipType(){ return m_Type; };
	void		ResetPosition();

	void		shipInit();

protected:
	std::string m_Name;
	int			m_Size;
	int			m_Hp;
	

	MapDataTypes	m_Type;

	Position		m_ShipPosition[5];
};

