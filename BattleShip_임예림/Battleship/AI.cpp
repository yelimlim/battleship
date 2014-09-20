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
	//배 초기화
	m_MyShip[0] = new Aircraft();
	m_MyShip[1] = new BattleShip_();
	m_MyShip[2] = new Cruiser();
	m_MyShip[3] = new Destroyer(1);
	m_MyShip[4] = new Destroyer(2);

	//초기화
	m_Type = Ai;
	m_RemainShip = m_MyShip.size();
	
	//AI 만의 초기화
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

	//공격 상태에 따라 공격 방법 다름
	switch (m_HowDoIAttack)
	{
	//아무것도 못 찾았을 때
	case NOTFIND:
		pos = AttackNewPlace();
		break;
	//하나 찾아서 주위 공격해 볼 때
	case ATTACKSURROUND:
		pos = AttackSurround();
		break;
	//방향도 찾아서 추격할 때
	case CHASEDIRECTION:
		pos = AttackChase();
		break;
	//반대 방향으로 추격할 때
	case CHASEOPPDIRECTION:
		pos = AttackChase();
		break;
	}
	return pos;
	

}

void AI::SetAttackArray()
{
	//생성자를 위한 변수
	int x = 0 + 'a';
	int y = 0 + '1';

	//a1 부터 좌표 생성 후 옆으로 3칸씩 띄어서 배열에 저장
	for (int i = 0; i < _countof(m_AttackPosition); ++i)
	{
		m_AttackPosition[i] = new Position{ x, y };

		y = y + 3;

		//지도를 넘어 갈 경우 다음줄로 이동
		if (y - '1' > m_MyMap.GetMapRow() - 1)
		{
			x = x + 1;
			y = ((y - '1') % m_MyMap.GetMapRow()) + '1';
		}
	}

	//정렬을 위한 버퍼
	Position* buffer;

	//가운데 일수록 배열 앞에 오게끔 정렬
	for (int i = 1; i < _countof(m_AttackPosition); ++i)
	{
		int lessHitDegree = GetLessHitDegree(*m_AttackPosition[i]);

		for (int j = 0; j < i; ++j)
		{
			//앞에 있는 것과 비교해서 내가 더 적으면 재정렬
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

//가장자리인지 계산후 리턴
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

	//공격 상태와 result 값에 따라 앞으로의 상태 변화
	switch (m_HowDoIAttack)
	{
	case NOTFIND:
		//처음 찾은 경우
		if (result != AR_MISS)
		{
			m_HowDoIAttack = ATTACKSURROUND;
			m_FirstHitPosition = attackpos;
			m_Chasestack.push_back(attackpos);

			//추격 벡터 출력
			for (int i = 0; i < m_Chasestack.size(); ++i)
			{
				printf_s("%c%c ", m_Chasestack[i].x, m_Chasestack[i].y);
			}
			printf_s("\n");
			//getchar();
		}
		break;

	case ATTACKSURROUND:
		//추격 방향 찾은 경우
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

			//추격 벡터 출력
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
		//추격 방향 반대로 바꾸기
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

			//추격 벡터 출력
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
		//반대 방향까지 추격 완료한 경우
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

	//destroy 된 경우
	if (result != AR_HIT && result != AR_MISS)
	{
		ChaseStackCheck(result);
		//m_HowDoIAttack = NOTFIND;
	}
}

Position AI::AttackNewPlace()
{
	Position pos;

	// 미리 정한 공격 위치 배열 돌기
	for (int i = 0; i < _countof(m_AttackPosition); ++i) 
	{
		pos = *m_AttackPosition[i];

		//그 위치에 공격 안 했고 지도 위에 있으면 반환
		if (m_AttackMap.IsInMap(pos) && m_AttackMap.GetMapStatus(pos) == NOTHING) 
		{
			return pos;
		}
	}

	// 아니면 랜덤 반환
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

	//동서남북 주위의 좌표를 배열에 넣는다.
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

	//방향을 남은 좌표가 많은 순으로 재정렬한다.
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

	//재정렬한 배열을 돌면서 가능한 방향이면 리턴
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

	//위의 배열을 다 돌았는데도 리턴 못할 시
	//추격할 남은 좌표 확인 후 있으면 남은 좌표로 추격
	if (!m_Leftstack.empty())
	{
		//추격하기 전 추격 벡터 초기화
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
			//주위에 남은 좌표가 더 이상 없으면 벡터에서 삭제
			m_Leftstack.erase(m_Leftstack.begin());
		}

	}

	//위의 어느 조건도 걸리지 않으면 못 찾은 상태로 돌아감
	m_Chasestack.clear();
	m_HowDoIAttack = NOTFIND;

	return pos = AttackNewPlace();
}

//추격하기
Position AI::AttackChase()
{
	Position pos = m_LastHitPosition;

	//추격 방향에 따라 한 칸 전진한 후
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
		printf_s("방향이 없습니다,");
		getchar();
		break;
	}

	//공격가능하면 리턴
	if (m_AttackMap.IsInMap(pos) && m_AttackMap.GetMapStatus(pos) == NOTHING)
	{
		return pos;
	}

	//아니면 방향 바꿔서 추격
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
	//반대 방향 공격 까지 했는 데도 공격을 할 수 없으면 추격 중지
	else
	{
		ChaseStackCheck(AR_MISS);
		return pos = AttackShip();
	}


}

//안 맞을 확률 계산 : 가운데에서 얼마나 가까운지로
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

	//모서리면 확률을 터무니 없게 높여서 리턴
	if (pos.x == 'a' || pos.x == 'h' || pos.y == '1' || pos.y == '8')
	{
		return OVERDEGREE;
	}

	//가운데와 얼마나 먼지 가로 세로 길이 더해서 리턴
	return lessHitDegreeX + lessHitDegreeY;
}

//인자로 들어온 방향에 남은 좌표 계산
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
		printf_s("방향이 없습니다");
		getchar();
		break;
	}

	return howMany;
}

//주위에 빈 좌표가 있는지 확인
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
	//기본적으로 플레이어 초기화 : 배랑 지도 등 초기화
	Player::PlayerInit();

	//AI 만의 초기화
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
	//result가 Destroy인 경우
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

		//남은 배 크기 벡터에서 지우기
		for (int i = 0; i < m_RemainShipSize.size(); ++i)
		{
			if (m_RemainShipSize[i] == popNum)
			{
				vector <int> ::iterator itr = m_RemainShipSize.begin() + i;
				m_RemainShipSize.erase(itr);
				break;
			}
		}

		//작은 배 큰 배 재설정
		if (!m_RemainShipSize.empty())
		{
			m_HowBigAttackShip = m_RemainShipSize.front();
			m_HowSmallAttackShip = m_RemainShipSize.back();
		}

		//추격 벡터 크기가 격추된 배보다 작을 경우 추격 벡터 초기화
		if (m_Chasestack.size() < popNum)
		{
			m_Chasestack.clear();
		}
		//아니면 격추 된 배 크기 만큼 벡터에서 삭제
		else if (m_ChaseDirecition == EAST || m_ChaseDirecition == SOUTH)
		{
			m_Chasestack.erase(m_Chasestack.end() - popNum, m_Chasestack.end());
		}
		else if (m_ChaseDirecition == WEST || m_ChaseDirecition == NORTH)
		{
			m_Chasestack.erase(m_Chasestack.begin(), m_Chasestack.begin() + popNum);
		}
	}

	//추격 벡터가 비어 있지 않으면 남은 원소 다른 벡터로 옮겨서 추격 좌표 따로 저장
	if (!m_Chasestack.empty())
	{
		m_Leftstack.insert(m_Leftstack.end(), m_Chasestack.begin(), m_Chasestack.end());

		m_Chasestack.clear();
	}
	
	//따로 저장한 추격 좌표가 남아 있으면 추격 좌표로 다시 추격
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
	
	//위의 조건들이 걸리지 않으면 못 찾은 상태로 돌아감
	m_HowDoIAttack = NOTFIND;
	m_Chasestack.clear();
	return;
	
}
