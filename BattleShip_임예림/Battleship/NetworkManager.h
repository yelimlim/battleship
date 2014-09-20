#pragma once
#include "Player.h"
#include "ShipData.h"



class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

	Network network;
	ShipData shipdata;
	Player*	m_player;

	void GameRun();

private:
	void	GameStart();
	void	GameInit();

	void	ShipSetting();
	void	Error();
	Coord	PositionToCoord(Position pos);
};

