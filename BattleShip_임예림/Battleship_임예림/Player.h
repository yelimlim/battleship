#pragma once
#include "Ship.h"
#include "Map.h"
class Player
{
public:
	Player();
	~Player();

public:
	void Attack();
	void LocateShip();
	void SendToManager();

private:
	Ship* m_MyShip;
	Map m_MyMap;
};

