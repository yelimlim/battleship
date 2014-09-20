#include "stdafx.h"
#include "AI.h"
#include "struct.h"
#include "Ship.h"
#include "Aircraft.h"
#include "BattleShip_.h"
#include "Cruiser.h"
#include "Destroyer.h"
#include "Map.h"
#include "Draw.h"
#include <iostream>
#include <time.h>
#include <conio.h>


AI::AI()
{
	//�� �ʱ�ȭ
	m_MyShip[0] = new Aircraft();
	m_MyShip[1] = new BattleShip_();
	m_MyShip[2] = new Cruiser();
	m_MyShip[3] = new Destroyer(1);
	m_MyShip[4] = new Destroyer(2);

	//�ʱ�ȭ
	m_Type = Ai;
	m_RemainShip = m_MyShip.size();
	
	//AI ���� �ʱ�ȭ
	m_HowDoIAttack = NOTFIND;
	m_RemainShipSize.clear();
	m_Chasestack.clear();
	m_Leftstack.clear();

	for (int i = 0; i < m_MyShip.size(); ++i)
	{
		m_RemainShipSize.push_back(m_MyShip[i]->GetSize());
	}
	m_HowBigAttackShip = m_RemainShipSize.front();
	m_HowSmallAttackShip = m_RemainShipSize.back();

	SetAttackArray();
}


AI::~AI()
{
}

Position AI::AttackShip()
{
	Position pos;

	//���� ���¿� ���� ���� ��� �ٸ�
	switch (m_HowDoIAttack)
	{
	//�ƹ��͵� �� ã���� ��
	case NOTFIND:
		pos = AttackNewPlace();
		break;
	//�ϳ� ã�Ƽ� ���� ������ �� ��
	case ATTACKSURROUND:
		pos = AttackSurround();
		break;
	//���⵵ ã�Ƽ� �߰��� ��
	case CHASEDIRECTION:
		pos = AttackChase();
		break;
	//�ݴ� �������� �߰��� ��
	case CHASEOPPDIRECTION:
		pos = AttackChase();
		break;
	}
	return pos;
	

}

void AI::SetAttackArray()
{
	//�����ڸ� ���� ����
	int x = 0 + 'a';
	int y = 0 + '1';

	//a1 ���� ��ǥ ���� �� ������ 3ĭ�� �� �迭�� ����
	for (int i = 0; i < _countof(m_AttackPosition); ++i)
	{
		m_AttackPosition[i] = new Position{ x, y };

		y = y + 3;

		//������ �Ѿ� �� ��� �����ٷ� �̵�
		if (y - '1' > m_MyMap.GetMapRow() - 1)
		{
			x = x + 1;
			y = ((y - '1') % m_MyMap.GetMapRow()) + '1';
		}
	}

	//������ ���� ����
	Position* buffer;

	//��� �ϼ��� �迭 �տ� ���Բ� ����
	for (int i = 1; i < _countof(m_AttackPosition); ++i)
	{
		int lessHitDegree = GetLessHitDegree(*m_AttackPosition[i]);

		for (int j = 0; j < i; ++j)
		{
			//�տ� �ִ� �Ͱ� ���ؼ� ���� �� ������ ������
			if (GetLessHitDegree(*m_AttackPosition[j]) > lessHitDegree)
			{
				buffer = m_AttackPosition[i];
				for (int k = i; k > j; --k)
				{
					m_AttackPosition[k] = m_AttackPosition[k - 1];
				}
				m_AttackPosition[j] = buffer;

				break;
			}
		}
	}
}

//�����ڸ����� ����� ����
bool AI::isedge(int number)
{
	if (!(m_AttackPosition[number]->x - 'a' > 0 
		&& m_AttackPosition[number]->x - 'a' < m_MyMap.GetMapRow() - 1
		&& m_AttackPosition[number]->y - '1' > 0 
		&& m_AttackPosition[number]->y - '1' < m_MyMap.GetMapColumn() - 1))
	{
		return true;
	}
	return false;
}

void AI::TakeAttackResult(Position attackpos, AttackResult result)
{
	Player::TakeAttackResult(attackpos, result);

	//���� ���¿� result ���� ���� �������� ���� ��ȭ
	switch (m_HowDoIAttack)
	{
	case NOTFIND:
		//ó�� ã�� ���
		if (result != AR_MISS)
		{
			m_HowDoIAttack = ATTACKSURROUND;
			m_FirstHitPosition = attackpos;
			m_Chasestack.push_back(attackpos);

			//�߰� ���� ���
			for (int i = 0; i < m_Chasestack.size(); ++i)
			{
				printf_s("%c%c ", m_Chasestack[i].x, m_Chasestack[i].y);
			}
			printf_s("\n");
			//getchar();
		}
		break;

	case ATTACKSURROUND:
		//�߰� ���� ã�� ���
		if (result != AR_MISS)
		{
			if (m_ChaseDirecition == EAST || m_ChaseDirecition == SOUTH)
			{
				
				m_Chasestack.push_back(attackpos);
			}
			else if (m_ChaseDirecition == WEST || m_ChaseDirecition == NORTH)
			{
				vector <Position> ::iterator itr;
				itr = m_Chasestack.begin();
				m_Chasestack.insert(itr, attackpos);
			}

			//�߰� ���� ���
			for (int i = 0; i < m_Chasestack.size(); ++i)
			{
				printf_s("%c%c ", m_Chasestack[i].x, m_Chasestack[i].y);
			}
			printf_s("\n");
			//getchar();

			m_LastHitPosition = attackpos;
			m_HowDoIAttack = CHASEDIRECTION;
		}
		break;

	case CHASEDIRECTION:
		//�߰� ���� �ݴ�� �ٲٱ�
		if (result == AR_MISS)
		{
			m_HowDoIAttack = CHASEOPPDIRECTION;

			switch (m_ChaseDirecition)
			{
			case EAST:
				m_ChaseDirecition = WEST;
				break;
			case WEST:
				m_ChaseDirecition = EAST;
				break;
			case SOUTH:
				m_ChaseDirecition = NORTH;
				break;
			case NORTH:
				m_ChaseDirecition = SOUTH;
				break;
			}
		}
		else
		{
			if (m_ChaseDirecition == EAST || m_ChaseDirecition == SOUTH)
			{
				m_Chasestack.push_back(attackpos);
			}
			else if (m_ChaseDirecition == WEST || m_ChaseDirecition == NORTH)
			{
				vector <Position> ::iterator itr;
				itr = m_Chasestack.begin();
				m_Chasestack.insert(itr, attackpos);
			}

			//�߰� ���� ���
			for (int i = 0; i < m_Chasestack.size(); ++i)
			{
				printf_s("%c%c ", m_Chasestack[i].x, m_Chasestack[i].y);
			}
			printf_s("\n");
			//getchar();

			m_LastHitPosition = attackpos;
			m_HowDoIAttack = CHASEDIRECTION;
		}
		break;

	case CHASEOPPDIRECTION:
		//�ݴ� ������� �߰� �Ϸ��� ���
		if (result == AR_MISS)
		{
			ChaseStackCheck(result);
		}
		else
		{
			if (m_ChaseDirecition == EAST || m_ChaseDirecition == SOUTH)
			{
				m_Chasestack.push_back(attackpos);
			}
			else if (m_ChaseDirecition == WEST || m_ChaseDirecition == NORTH)
			{
				vector <Position> ::iterator itr;
				itr = m_Chasestack.begin();
				m_Chasestack.insert(itr, attackpos);
			}

			for (int i = 0; i < m_Chasestack.size(); ++i)
			{
				printf_s("%c%c ", m_Chasestack[i].x, m_Chasestack[i].y);
			}
			printf_s("\n");
			//getchar();

			m_LastHitPosition = attackpos;
			m_HowDoIAttack = CHASEDIRECTION;
		}
		break;
	}

	//destroy �� ���
	if (result != AR_HIT && result != AR_MISS)
	{
		ChaseStackCheck(result);
		//m_HowDoIAttack = NOTFIND;
	}
}

Position AI::AttackNewPlace()
{
	Position pos;

	// �̸� ���� ���� ��ġ �迭 ����
	for (int i = 0; i < _countof(m_AttackPosition); ++i) 
	{
		pos = *m_AttackPosition[i];

		//�� ��ġ�� ���� �� �߰� ���� ���� ������ ��ȯ
		if (m_AttackMap.IsInMap(pos) && m_AttackMap.GetMapStatus(pos) == NOTHING) 
		{
			return pos;
		}
	}

	// �ƴϸ� ���� ��ȯ
	do
	{
		pos.x = rand() % m_MyMap.GetMapColumn() + 'a'; 
		pos.y = rand() % m_MyMap.GetMapRow() + '1';
	} while (m_AttackMap.IsInMap(pos) && m_AttackMap.GetMapStatus(pos) != NOTHING);

	return pos;
	

}

Position AI::AttackSurround()
{
	Position pos;
	Direction direct;

	//�������� ������ ��ǥ�� �迭�� �ִ´�.
	Position fourDirectionPos[MAX_DIRECTION];

	fourDirectionPos[0].x = m_FirstHitPosition.x + 1; // EAST
	fourDirectionPos[0].y = m_FirstHitPosition.y;


	fourDirectionPos[1].x = m_FirstHitPosition.x; //SOUTH
	fourDirectionPos[1].y = m_FirstHitPosition.y + 1;

	fourDirectionPos[2].x = m_FirstHitPosition.x - 1; //WEST
	fourDirectionPos[2].y = m_FirstHitPosition.y;

	fourDirectionPos[3].x = m_FirstHitPosition.x; //NORTH
	fourDirectionPos[3].y = m_FirstHitPosition.y - 1;

	Direction turnDirect[4] = { EAST, SOUTH, WEST, NORTH };

	//������ ���� ��ǥ�� ���� ������ �������Ѵ�.
	for (int i = 0; i < _countof(fourDirectionPos); ++i)
	{
		pos = fourDirectionPos[i];
		direct = NumToDirect(i + 1);

		for (int j = 1; j < i; ++j)
		{
			direct = (Direction)(j + 1);

			if (HowManyLeft(pos, direct) > HowManyLeft(fourDirectionPos[j], direct))
			{
				Direction buffer = turnDirect[i];
				for (int k = i; k > j; --k)
				{
					turnDirect[k] = turnDirect[k - 1];
				}
				turnDirect[j] = buffer;
			}
		}
		
	}

	//�������� �迭�� ���鼭 ������ �����̸� ����
	for (int i = 0; i < _countof(fourDirectionPos); ++i)
	{
		pos = fourDirectionPos[turnDirect[i] - 1];
		direct = turnDirect[i];

		if (m_AttackMap.IsInMap(pos) && m_AttackMap.GetMapStatus(pos) == NOTHING)
		{
			m_ChaseDirecition = direct;
			return pos;
		}
	}

	//���� �迭�� �� ���Ҵµ��� ���� ���� ��
	//�߰��� ���� ��ǥ Ȯ�� �� ������ ���� ��ǥ�� �߰�
	if (!m_Leftstack.empty())
	{
		//�߰��ϱ� �� �߰� ���� �ʱ�ȭ
		m_Chasestack.clear();

		for (int i = 0; i < m_Leftstack.size(); ++i)
		{
			if (isFourDirectionFine(m_Leftstack[i]))
			{
				m_FirstHitPosition = m_Leftstack[i];
				m_Chasestack.push_back(m_Leftstack[i]);
				m_Leftstack.erase(m_Leftstack.begin());
				m_HowDoIAttack = ATTACKSURROUND;

				return pos = AttackSurround();
			}
			//������ ���� ��ǥ�� �� �̻� ������ ���Ϳ��� ����
			m_Leftstack.erase(m_Leftstack.begin());
		}

	}

	//���� ��� ���ǵ� �ɸ��� ������ �� ã�� ���·� ���ư�
	m_Chasestack.clear();
	m_HowDoIAttack = NOTFIND;

	return pos = AttackNewPlace();
}

//�߰��ϱ�
Position AI::AttackChase()
{
	Position pos = m_LastHitPosition;

	//�߰� ���⿡ ���� �� ĭ ������ ��
	switch (m_ChaseDirecition)
	{
	case EAST:
		pos.x++;
		break;

	case SOUTH:
		pos.y++;
		break;

	case WEST:
		pos.x--;
		break;

	case NORTH:
		pos.y--;
		break;

	default:
		printf_s("������ �����ϴ�,");
		getchar();
		break;
	}

	//���ݰ����ϸ� ����
	if (m_AttackMap.IsInMap(pos) && m_AttackMap.GetMapStatus(pos) == NOTHING)
	{
		return pos;
	}

	//�ƴϸ� ���� �ٲ㼭 �߰�
	if (m_HowDoIAttack == CHASEDIRECTION)
	{
		m_HowDoIAttack = CHASEOPPDIRECTION;

		switch (m_ChaseDirecition)
		{
		case EAST:
			m_ChaseDirecition = WEST;
			break;
		case WEST:
			m_ChaseDirecition = EAST;
			break;
		case SOUTH:
			m_ChaseDirecition = NORTH;
			break;
		case NORTH:
			m_ChaseDirecition = SOUTH;
			break;
		}

		return pos = AttackChase(); 
	}
	//�ݴ� ���� ���� ���� �ߴ� ���� ������ �� �� ������ �߰� ����
	else
	{
		ChaseStackCheck(AR_MISS);
		return pos = AttackShip();
	}


}

//�� ���� Ȯ�� ��� : ������� �󸶳� ���������
int AI::GetLessHitDegree(Position pos)
{
	int lessHitDegreeX = 4 - (pos.x - 'a');
	int lessHitDegreeY = 4 - (pos.y - '1');

	if (lessHitDegreeX < 0)
	{
		lessHitDegreeX = lessHitDegreeX * (-1);
	}

	if (lessHitDegreeY < 0)
	{
		lessHitDegreeY = lessHitDegreeY * (-1);
	}

	//�𼭸��� Ȯ���� �͹��� ���� ������ ����
	if (pos.x == 'a' || pos.x == 'h' || pos.y == '1' || pos.y == '8')
	{
		return OVERDEGREE;
	}

	//����� �󸶳� ���� ���� ���� ���� ���ؼ� ����
	return lessHitDegreeX + lessHitDegreeY;
}

//���ڷ� ���� ���⿡ ���� ��ǥ ���
int AI::HowManyLeft(Position pos, Direction direct)
{
	int howMany = 1;

	switch (direct)
	{
	case EAST:
		pos.x = pos.x + 1;

		for (int i = 0; i < m_AttackMap.GetMapRow(); ++i)
		{
			if (!m_AttackMap.IsInMap(pos) || m_AttackMap.GetMapStatus(pos) != NOTHING)
			{
				return howMany;
			}
			pos.x = pos.x + 1;
			howMany++;
		}
		break;
	case SOUTH:
		pos.y = pos.y + 1;

		for (int i = 0; i < m_AttackMap.GetMapColumn(); ++i)
		{
			if (!m_AttackMap.IsInMap(pos) || m_AttackMap.GetMapStatus(pos) != NOTHING)
			{
				return howMany;
			}
			pos.y = pos.y + 1;
			howMany++;
		}
		break;
	case WEST:
		pos.x = pos.x - 1;

		for (int i = 0; i < m_AttackMap.GetMapRow(); ++i)
		{
			if (!m_AttackMap.IsInMap(pos) || m_AttackMap.GetMapStatus(pos) != NOTHING)
			{
				return howMany;
			}
			pos.x = pos.x - 1;
			howMany++;
		}
		break;

	case NORTH:
		pos.y = pos.y - 1;

		for (int i = 0; i < m_AttackMap.GetMapColumn(); ++i)
		{
			if (!m_AttackMap.IsInMap(pos) || m_AttackMap.GetMapStatus(pos) != NOTHING)
			{
				return howMany;
			}
			pos.y = pos.y - 1;
			howMany++;
		}
		break;

	default:
		printf_s("������ �����ϴ�");
		getchar();
		break;
	}

	return howMany;
}

//������ �� ��ǥ�� �ִ��� Ȯ��
bool AI::isFourDirectionFine(Position pos)
{
	if (HowManyLeft(pos, EAST) > 0)
	{
		return true;
	}

	if (HowManyLeft(pos, WEST) > 0)
	{
		return true;
	}
	if (HowManyLeft(pos, SOUTH) > 0)
	{
		return true;
	}

	if (HowManyLeft(pos, NORTH) > 0)
	{
		return true;
	}

	return false;
}

bool AI::isThereShipPossible(Position pos, ShipShape shape)
{
	if (shape == COL)
	{
		if (HowManyLeft(pos, NORTH) + HowManyLeft(pos, SOUTH) - 1 > m_HowSmallAttackShip - 1)
		{
			return true;
		}
	}
	else if (shape == ROW)
	{
		if (HowManyLeft(pos, EAST) + HowManyLeft(pos, WEST) - 1 > m_HowSmallAttackShip - 1)
		{
			return true;
		}
	}

	return false;
}

ShipShape AI::DirectToShape(Direction direct)
{
	if (direct == EAST || direct == WEST)
	{
		return ROW;
	}
	else if (direct == NORTH || direct == SOUTH)
	{
		return COL;
	}
}

bool AI::AttackMapChek(int numOfDirect)
{
	Position pos;

	for (int i = 0; i < m_AttackMap.GetMapColumn(); ++i)
	{
		for (int j = 0; j < m_AttackMap.GetMapRow(); ++j)
		{
			pos.x = i + 'a';
			pos.y = j + '1';

			if (m_AttackMap.GetMapStatus(pos) == NOTHING && !isFourDirectionFine(pos))
			{
				return false;
			}
		}
	}

	return true;
}

void AI::PlayerInit()
{
	//�⺻������ �÷��̾� �ʱ�ȭ : ��� ���� �� �ʱ�ȭ
	Player::PlayerInit();

	//AI ���� �ʱ�ȭ
	m_HowDoIAttack = NOTFIND;
	m_RemainShipSize.clear();
	m_Chasestack.clear();
	m_Leftstack.clear();
	
	m_RemainShipSize.clear();
	for (int i = 0; i < m_MyShip.size(); ++i)
	{
		m_RemainShipSize.push_back(m_MyShip[i]->GetSize());
	}
	m_HowBigAttackShip = m_RemainShipSize.front();
	m_HowSmallAttackShip = m_RemainShipSize.back();

	SetAttackArray();
}

void AI::ChaseStackCheck(AttackResult result)
{
	//result�� Destroy�� ���
	if (result != AR_MISS && result != AR_HIT)
	{
		int popNum;

		switch (result)
		{
		case AR_DESTROY_AIRCRAFT:
			popNum = 5;
			break;
		case AR_DESTROY_BATTLESHIP:
			popNum = 4;
			break;
		case AR_DESTROY_CRUISER:
			popNum = 3;
			break;
		case AR_DESTROY_DESTROYER:
			popNum = 2;
			break;
		}

		//���� �� ũ�� ���Ϳ��� �����
		for (int i = 0; i < m_RemainShipSize.size(); ++i)
		{
			if (m_RemainShipSize[i] == popNum)
			{
				vector <int> ::iterator itr = m_RemainShipSize.begin() + i;
				m_RemainShipSize.erase(itr);
				break;
			}
		}

		//���� �� ū �� �缳��
		if (!m_RemainShipSize.empty())
		{
			m_HowBigAttackShip = m_RemainShipSize.front();
			m_HowSmallAttackShip = m_RemainShipSize.back();
		}

		//�߰� ���� ũ�Ⱑ ���ߵ� �躸�� ���� ��� �߰� ���� �ʱ�ȭ
		if (m_Chasestack.size() < popNum)
		{
			m_Chasestack.clear();
		}
		//�ƴϸ� ���� �� �� ũ�� ��ŭ ���Ϳ��� ����
		else if (m_ChaseDirecition == EAST || m_ChaseDirecition == SOUTH)
		{
			m_Chasestack.erase(m_Chasestack.end() - popNum, m_Chasestack.end());
		}
		else if (m_ChaseDirecition == WEST || m_ChaseDirecition == NORTH)
		{
			m_Chasestack.erase(m_Chasestack.begin(), m_Chasestack.begin() + popNum);
		}
	}

	//�߰� ���Ͱ� ��� ���� ������ ���� ���� �ٸ� ���ͷ� �Űܼ� �߰� ��ǥ ���� ����
	if (!m_Chasestack.empty())
	{
		m_Leftstack.insert(m_Leftstack.end(), m_Chasestack.begin(), m_Chasestack.end());

		m_Chasestack.clear();
	}
	
	//���� ������ �߰� ��ǥ�� ���� ������ �߰� ��ǥ�� �ٽ� �߰�
	if (!m_Leftstack.empty())
	{
		for (int i = 0; i < m_Leftstack.size(); ++i)
		{
			if (isFourDirectionFine(m_Leftstack[i]))
			{
				m_FirstHitPosition = m_Leftstack[i];
				m_Chasestack.push_back(m_Leftstack[i]);
				m_Leftstack.erase(m_Leftstack.begin());
				m_HowDoIAttack = ATTACKSURROUND;
				return;
			}
			m_Leftstack.erase(m_Leftstack.begin());
		}
	}
	
	//���� ���ǵ��� �ɸ��� ������ �� ã�� ���·� ���ư�
	m_HowDoIAttack = NOTFIND;
	m_Chasestack.clear();
	return;
	
}
