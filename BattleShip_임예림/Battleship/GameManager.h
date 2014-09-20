#pragma once
#include "struct.h"
#include "Player.h"
#include <string>
class GameManager
{
	

public:
	GameManager();
	~GameManager();

	
	void GameRun(int turn);

private:

	vector <Player*> m_Players;
	int		m_AttackTurn;
	int		m_DefendTurn;

	int		m_Win;

	int		m_Turn;

	
	void GameStrat();
	void GameInit();

	void TurnChange();
	bool GameOverCondition();
	
};

