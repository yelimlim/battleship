#pragma once
#include <string>
#include "Ship.h"
#include "struct.h"
#include "Map.h"

class Aircraft;
class BattleShip_;
class Cruiser;
class Destroyer;

class Player
{

public:
	Player();
	~Player();

	Position*		SetShipPosition(int shipNum, MapDataTypes& out_shipType, int& out_shipSize);
	void			SetShipPosition();
	Position		AttackShip();
	Position		AttackShip(Position pos);
	AttackResult	HitCheck(Position pos);
	void			TakeAttackResult(Position attackpos, AttackResult result);
	void			PrintShips();

	PlayerType	GetType() { return m_Type; };

	void		DestroyShip(){ m_RemainShip--; };
	int			GetRemainShipNum(){ return m_RemainShip; };
	void		CheckMySmallBigShipSize();
	int			GetBigSize();
	int			GetSmallSize();
	void		PlayerInit();

protected:

	PlayerType		m_Type;
	vector <Ship*>	m_MyShip;
	Position*		m_ShipPosition[5];
	int				m_RemainShip;
	Map				m_MyMap;
	Map				m_AttackMap;
	

	Position	PositionSetting();
	Position	PositionSetting(Position pos, int setkey);
	Direction	DirectionSetting(Position pos, int shipNum);
	Direction	DirectionSetting(Direction direct, Position pos, int shipNum);
	bool		SettingCheck(Position pos, Direction direct, int shipNum);

	Direction	NumToDirect(int directNum);

};

