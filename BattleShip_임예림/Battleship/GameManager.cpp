#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"
#include "AI.h"
#include "Draw.h"
#include <iostream>


GameManager::GameManager()
{
	// �÷��̾� ����
	m_Players.push_back(new Player()); 
	m_Players.push_back(new AI());

	// �̱� �� �ʱ�ȭ : AI�� �̱� ���� ���.
	m_Win = 0; 
}


GameManager::~GameManager()
{
	// �÷��̾� ����
	for (int i = 0; i < m_Players.size(); ++i) 
	{
		delete m_Players[i];
		m_Players[i] = nullptr;
	}

	m_Players.clear(); 
}

//���� �ʱ�ȭ
void GameManager::GameInit()
{
	// �� �ʱ�ȭ : AI �ϼ��� ���.
	m_Turn = 0;

	for (int i = 0; i < m_Players.size(); ++i)
	{
		
		if (m_Players[i]->GetType() == Ai)
		{
			// AI �ʱ�ȭ
			AI* ai = (AI*)m_Players[i];
			ai->PlayerInit();
		}
		else
		{
			//Player �ʱ�ȭ
			m_Players[i]->PlayerInit();
		}
		//�� ��ġ
		m_Players[i]->SetShipPosition();
 		printf_s("\n");
		//�� ���
 		m_Players[i]->PrintShips();
	}

	//�� ���ϱ�
	//�� ó�� �÷��̾ ����
	m_AttackTurn = 0;
	//�� ������ ���
	m_DefendTurn = 1;

	//getchar();
}

//���� ����
void GameManager::GameStrat()
{
	srand((unsigned int)time(NULL));

	//Draw picaso;

	//�� �� �谡 ���� �÷��̾� ���� ������
	while (GameOverCondition() == false)
	{
		printf_s("AttackTurn Player%d\n", m_AttackTurn + 1);

 		Position attackpos;
// 		attackpos.x = 0 + 'a';
// 		attackpos.y = 0 + '0';

		//�� ����
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
		
		//�� ��ü
		TurnChange();
	}
	printf_s("GAME OVER\n");
}

//���� �Ϸ� ���� Ȯ��
bool GameManager::GameOverCondition()
{
	bool isGameover = false;

	//������ AI(�÷��̾� 0) �̱� ���� ����Ѵ�.
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

//�� ��ü
void GameManager::TurnChange()
{
	m_AttackTurn = (m_AttackTurn + 1) % 2;
	m_DefendTurn = (m_DefendTurn + 1) % 2;
}

void GameManager::GameRun(int turn)
{
	//��� ��
	int avgturn = 0;

	//���ڷ� ���� ��ŭ ������
	for (int i = 0; i < turn; ++i)
	{
		//�ʱ�ȭ
		GameInit();
		//����
		GameStrat();
		avgturn = avgturn + m_Turn;
	}

	avgturn = avgturn / turn;

	printf_s("Turn: %d\n", avgturn);

	printf_s("Win: %d\n", m_Win);
}