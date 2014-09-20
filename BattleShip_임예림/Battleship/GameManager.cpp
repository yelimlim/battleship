#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"
#include "AI.h"
#include "Draw.h"
#include <iostream>


GameManager::GameManager()
{
	// 플레이어 설정
	m_Players.push_back(new Player()); 
	m_Players.push_back(new AI());

	// 이긴 수 초기화 : AI가 이긴 수만 잰다.
	m_Win = 0; 
}


GameManager::~GameManager()
{
	// 플레이어 삭제
	for (int i = 0; i < m_Players.size(); ++i) 
	{
		delete m_Players[i];
		m_Players[i] = nullptr;
	}

	m_Players.clear(); 
}

//게임 초기화
void GameManager::GameInit()
{
	// 턴 초기화 : AI 턴수만 잰다.
	m_Turn = 0;

	for (int i = 0; i < m_Players.size(); ++i)
	{
		
		if (m_Players[i]->GetType() == Ai)
		{
			// AI 초기화
			AI* ai = (AI*)m_Players[i];
			ai->PlayerInit();
		}
		else
		{
			//Player 초기화
			m_Players[i]->PlayerInit();
		}
		//배 배치
		m_Players[i]->SetShipPosition();
 		printf_s("\n");
		//배 출력
 		m_Players[i]->PrintShips();
	}

	//턴 정하기
	//맨 처음 플레이어가 공격
	m_AttackTurn = 0;
	//그 다음은 방어
	m_DefendTurn = 1;

	//getchar();
}

//게임 시작
void GameManager::GameStrat()
{
	srand((unsigned int)time(NULL));

	//Draw picaso;

	//둘 중 배가 없는 플레이어 생길 때까지
	while (GameOverCondition() == false)
	{
		printf_s("AttackTurn Player%d\n", m_AttackTurn + 1);

 		Position attackpos;
// 		attackpos.x = 0 + 'a';
// 		attackpos.y = 0 + '0';

		//배 공격
		if (m_Players[m_AttackTurn]->GetType() == Ai)
		{
			AI* ai = (AI*)m_Players[m_AttackTurn];
			attackpos = ai->AttackShip();
			m_Turn++;
		}
		else
		{
			attackpos = m_Players[m_AttackTurn]->AttackShip();
		}

		printf_s("%c%c\n", attackpos.x, attackpos.y);

		AttackResult result = m_Players[m_DefendTurn]->HitCheck(attackpos);
		
		//getchar();

		if (m_Players[m_AttackTurn]->GetType() == Ai)
		{
			AI* ai = (AI*)m_Players[m_AttackTurn];
			ai->TakeAttackResult(attackpos, result);
		}
		else
		{
			m_Players[m_AttackTurn]->TakeAttackResult(attackpos, result);
		}

		if (result != AR_MISS && result != AR_HIT)
		{
			m_Players[m_DefendTurn]->DestroyShip();

 			printf_s("%d %d\n", m_Players[0]->GetRemainShipNum(), m_Players[1]->GetRemainShipNum());
 			//getchar();
		}
		
		//턴 교체
		TurnChange();
	}
	printf_s("GAME OVER\n");
}

//게임 완료 조건 확인
bool GameManager::GameOverCondition()
{
	bool isGameover = false;

	//지금은 AI(플레이어 0) 이긴 수만 계산한다.
	if (m_Players[0]->GetRemainShipNum() < 1)
	{
		m_Win++;
	}

	for (int i = 0; i < m_Players.size(); ++i)
	{
		if (m_Players[i]->GetRemainShipNum() < 1)
		{
			printf_s("Player%d win", (i + 1) % 2);
			printf_s("Player%d lose\n", i);
			isGameover = true;
		}
	}

	
	return isGameover;
}

//턴 교체
void GameManager::TurnChange()
{
	m_AttackTurn = (m_AttackTurn + 1) % 2;
	m_DefendTurn = (m_DefendTurn + 1) % 2;
}

void GameManager::GameRun(int turn)
{
	//평균 턴
	int avgturn = 0;

	//인자로 받은 만큼 돌린다
	for (int i = 0; i < turn; ++i)
	{
		//초기화
		GameInit();
		//시작
		GameStrat();
		avgturn = avgturn + m_Turn;
	}

	avgturn = avgturn / turn;

	printf_s("Turn: %d\n", avgturn);

	printf_s("Win: %d\n", m_Win);
}