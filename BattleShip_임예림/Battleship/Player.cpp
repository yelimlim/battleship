#include "stdafx.h"
#include "Player.h"
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



Player::Player()
{
	// 배 초기화
	m_MyShip.push_back(new Aircraft());
	m_MyShip.push_back(new BattleShip_());
	m_MyShip.push_back(new Cruiser());
	m_MyShip.push_back(new Destroyer(1)); //MD_DESTROYER1
	m_MyShip.push_back(new Destroyer(2)); //MD_DESTROYER2

	// 초기화
	m_Type = HUMAN;
	m_RemainShip = m_MyShip.size();
}



Player::~Player()
{
	for (int i = 0; i < m_MyShip.size(); ++i)
	{
		delete m_MyShip[i];
		m_MyShip[i] = nullptr;
	}

	m_MyShip.clear();
}

//네트워크 연결 setshipPosition : 2,3번째 인자는 반환 인자
Position* Player::SetShipPosition(int shipNum, MapDataTypes& out_shipType, int& out_shipSize)
{
// 	Draw picaso;
// 
// 	Position mappos;
// 	for (int i = 0; i < m_MyMap.GetMapColumn(); ++i)
// 	{
// 		for (int j = 0; j < m_MyMap.GetMapRow(); ++j)
// 		{
// 			mappos.x = i + 'a';
// 			mappos.y = j + '0';
// 
// 			picaso.DrawMap1inside(mappos, m_MyMap.GetShipMapStatus(mappos));
// 		}
// 	}
// 
// 	for (int i = 0; i < _countof(m_MyShip); ++i)
// 	{
// 		picaso.WirteShipList(i,m_MyShip[i]->GetName());
// 	}
// 
// 	picaso.GoTo(SHIPLISTX - 3, SHIPLISTY);
// 	printf_s("⇒");
// 
// 	bool setship[5] = { false, };
// 
// 	for (int i = 0; i < _countof(m_MyShip); ++i)
// 	{ 
// 		
// 
// 		int shipkey = 0;
// 		int num = 0;
// 
// 		int shipNum = num / 2;
// 
// 		int x = SHIPLISTX - 3;
// 		int y = SHIPLISTY + num;
// 
// 
// 		while (shipkey != ENTER)
// 		{
// 			
// 
// 			shipkey = _getch();
// 
// 			if (shipkey == -32)
// 			{
// 				shipkey = _getch();
// 			}
// 
// 			picaso.GoTo(SHIPLISTX - 1, SHIPLISTY + 10);
// 			printf_s("                       ");
// 
// 			picaso.GoTo(x, y);
// 			printf_s(" ");
// 
// 			switch (shipkey)
// 			{
// 			case UP:
// 				num = (num - 2) % 10;
// 				break;
// 			case DOWN:
// 				num = (num + 2) % 10;
// 				break;
// 			}
// 
// 			if (num < 0)
// 			{
// 				num = 8;
// 			}
// 
// 			y = SHIPLISTY + num;
// 
// 			picaso.GoTo(x, y);
// 			printf_s("⇒");
// 
// 			if (setship[num/2] == true)
// 			{
// 				picaso.GoTo(SHIPLISTX-1, SHIPLISTY+10);
// 				printf_s("이미 배치한 배 입니다.");
// 				shipkey = 0; // 초기화
// 			}
// 
// 		}
// 
// 		setship[num / 2] = true;
// 
// 		picaso.GoTo(x, y);
// 		printf_s(" ");
// 
// 		shipNum = num / 2;
// 		bool setReady = false;
// 		Position pos;
// 		pos.x = 'a';
// 		pos.y = '0';
// 		Direction direct = EAST;
// 		Direction erasedirect = direct;
// 
// 		Position printpos = pos;
// 		Position erasepos = pos;
// 		for (int i = 0; i < m_MyShip[shipNum]->GetHp(); ++i)
// 		{
// 			picaso.DrawMap1inside(printpos, SQUARE);
// 			printpos.x = printpos.x + 1;
// 		}
// 
// 		int setkey = 0;
// 
// 		while (setReady == false)
// 		{
// 			setkey = _getch();
// 
// 			if (setkey == 224)
// 			{
// 				setkey = _getch();
// 			}
// 
// 			if (setkey == LEFT || setkey == RIGHT || setkey == DOWN || setkey == UP)
// 			{
// 				pos = PositionSetting(pos, setkey);
// 			}
// 			else if (setkey == SPACEBAR)
// 			{
// 				direct = DirectionSetting(direct,pos,shipNum);
// 			}
// 			else if (setkey == ENTER)
// 			{
// 				setReady = SettingCheck(pos, direct, shipNum);
// 			}
// 
// 			printpos = pos;
// 
// 
// 			for (int i = 0; i < m_MyShip[shipNum]->GetHp(); ++i)
// 			{
// 				picaso.DrawMap1inside(erasepos, m_MyMap.GetShipMapStatus(erasepos));
// 
// 				switch (erasedirect)
// 				{
// 				case EAST:
// 					erasepos.x = erasepos.x + 1;
// 					break;
// 				case WEST:
// 					erasepos.x = erasepos.x - 1;
// 					break;
// 				case SOUTH:
// 					erasepos.y = erasepos.y + 1;
// 					break;
// 				case NORTH:
// 					erasepos.y = erasepos.y - 1;
// 					break;
// 				}
// 				
// 			}
// 
// 			for (int i = 0; i < m_MyShip[shipNum]->GetHp(); ++i)
// 			{
// 				picaso.DrawMap1inside(printpos, SQUARE);
// 
// 				switch (direct)
// 				{
// 				case EAST:
// 					printpos.x = printpos.x + 1;
// 					break;
// 				case WEST:
// 					printpos.x = printpos.x - 1;
// 					break;
// 				case SOUTH:
// 					printpos.y = printpos.y + 1;
// 					break;
// 				case NORTH:
// 					printpos.y = printpos.y - 1;
// 					break;
// 				}
// 			}
// 
// 			erasepos = pos;
// 			erasedirect = direct;
// 
// 		}

	//true가 되면 배 배치 가능
	bool setReady = false;

	//배 처음 좌표
	Position pos;
	//배 방향
	Direction direct;

	while (setReady == false)
	{
		//좌표 값 받아서
		pos = PositionSetting();
		//지도 안에 들어가는지 확인하고
		direct = DirectionSetting(pos, shipNum);
		//겹치지 않는지 확인한다
		setReady = SettingCheck(pos, direct, shipNum);
	}

	for (int i = 0; i < m_MyShip[shipNum]->GetSize(); ++i)
	{
		//picaso.DrawMap1inside(pos, m_MyShip[shipNum]->GetShipType());

		//확정된 배 위치 배에 전달
		m_MyShip[shipNum]->AddPosition(pos);
		//그리고 맵 정보 수정
		m_MyMap.ChangeShipMap(pos, m_MyShip[shipNum]->GetShipType());

		switch (direct)
		{
		case EAST:
			pos.x = pos.x + 1;
			break;
		case SOUTH:
			pos.y = pos.y + 1;
			break;
		case WEST:
			pos.x = pos.x - 1;
			break;
		case NORTH:
			pos.y = pos.y - 1;
			break;
		default:
			printf_s("방향이 없습니다");
			getchar();
			break;
		}

	}

	//반환용 배 타입
	out_shipType = m_MyShip[shipNum]->GetShipType();
	//반환용 배 크기
	out_shipSize = m_MyShip[shipNum]->GetSize();

	//배 처음 좌표 반환
	return m_MyShip[shipNum]->GetShipPosition();
}

void Player::SetShipPosition()
{
	//아무 값 없는 인자
	MapDataTypes shiptype;
	int shipSize;

	//각 배 배치
	for (int i = 0; i < m_MyShip.size(); ++i)
	{
		//2,3번째 인자는 네트워크 사용 때만 사용한다.
		SetShipPosition(i, shiptype, shipSize);
	}
}

//모든 배 출력
void Player::PrintShips()
{
	for (int i = 0; i < m_MyShip.size(); ++i) 
	{
		m_MyShip[i]->Print();
	}
}

Position Player::PositionSetting()
{
	//랜덤 배치
	Position pos;
	pos.x = rand()%m_MyMap.GetMapRow() + 'a';
	pos.y = rand()%m_MyMap.GetMapColumn() + '1';

	return pos;
}

Position Player::PositionSetting(Position pos, int setkey)
{
	switch (setkey)
	{
	case LEFT:
		--pos.x;
		break;
	case RIGHT:
		++pos.x;
		break;
	case DOWN:
		++pos.y;
		break;
	case UP:
		--pos.y;
		break;
	}

	return pos;
}

Direction Player::DirectionSetting(Position pos, int shipNum)
{
	//랜덤으로 좌표를 정하기 위해 만든 변수
	int directionNum;
	//재귀를 막기 위해 만든 배열
	bool rightdirectarray[MAX_DIRECTION] = { true, true, true, true };

	for (int i = 0; i < MAX_DIRECTION; ++i)
	{
		do
		{
			directionNum = rand() % MAX_DIRECTION + 1; //Direction 0 -> NONE 
		} while (!rightdirectarray[directionNum - 1]); // 했던 방향인가

		Direction direct = NumToDirect(directionNum);
		rightdirectarray[directionNum - 1] = false; // 한 방향은 체크

		//방향에 따라 맵에서 벗어났는지 체크 후 문제 없으면 반환
		switch (direct)
		{
		case EAST:
			if (pos.x - 'a' + m_MyShip[shipNum]->GetSize() - 1 < m_MyMap.GetMapRow())
			{
				return direct;
			}
			break;

		case WEST:
			if (pos.x - 'a' - m_MyShip[shipNum]->GetSize() + 1 > -1)
			{
				return direct;
			}
			break;

		case SOUTH:
			if (pos.y - '1' + m_MyShip[shipNum]->GetSize() - 1 < m_MyMap.GetMapColumn())
			{
				return direct;
			}
			break;

		case NORTH:
			if (pos.y - '1' - m_MyShip[shipNum]->GetSize() + 1 > -1)
			{
				return direct;
			}
			break;

		default:
			printf_s("방향이 없습니다");
			getchar();
			break;

		}
	}

	


}

Direction Player::DirectionSetting(Direction direct, Position pos, int shipNum)
{
	Direction willDirect;

	if (direct + 1 == 5)
	{
		willDirect = EAST;
	}
	else
	{
		willDirect = (Direction)(direct + 1);
	}


	switch (willDirect)
	{
	case EAST:
		if (pos.x - 'a' + m_MyShip[shipNum]->GetHp() > m_MyMap.GetMapRow())
		{
			willDirect = DirectionSetting(willDirect,pos, shipNum);
		}

		break;

	case WEST:
		if (pos.x - 'a' + 1 - m_MyShip[shipNum]->GetHp() < 0)
		{
			willDirect = DirectionSetting(willDirect, pos, shipNum);
		}

		break;

	case SOUTH:
		if (pos.y - '1' + m_MyShip[shipNum]->GetHp() > m_MyMap.GetMapColumn())
		{
			willDirect = DirectionSetting(willDirect, pos, shipNum);
		}

		break;

	case NORTH:
		if (pos.y - '1' + 1 - m_MyShip[shipNum]->GetHp() < 0)
		{
			willDirect = DirectionSetting(willDirect, pos, shipNum);
		}

		break;

	default:
		break;

	}

	return willDirect;
}

Position Player::AttackShip()
{
	srand((unsigned int)time(NULL));

	Position pos;
	do
	{
		pos.x = rand() % m_AttackMap.GetMapRow() + 'a';
		pos.y = rand() % m_AttackMap.GetMapColumn() + '1';
	} while (m_AttackMap.GetMapStatus(pos) != NOTHING);

	m_AttackMap.ChangeStatusMap(pos,ATTACK);

	return pos;
}
Position Player::AttackShip(Position pos)
{
	Draw picaso;

	Position mappos;
	for (int i = 0; i < m_MyMap.GetMapColumn(); ++i)
	{
		for (int j = 0; j < m_MyMap.GetMapRow(); ++j)
		{
			mappos.x = i + 'a';
			mappos.y = j + '1';
			picaso.SetLetterColor(m_MyMap.GetMapStatus(mappos));
			picaso.DrawMap1inside(mappos, m_MyMap.GetShipMapStatus(mappos));
			picaso.SetLetterColor(WHITE);
			picaso.SetLetterColor(m_AttackMap.GetMapStatus(mappos));
			picaso.DrawMap2inside(mappos, m_AttackMap.GetShipMapStatus(mappos));
			picaso.SetLetterColor(WHITE);
		}
	}

	picaso.DrawMap2inside(pos, SQUARE);

	Position erasepos = pos;
	int attackkey = 0;

	while (m_AttackMap.GetMapStatus(pos) == ATTACK || attackkey != ENTER)
	{
		attackkey = _getch();

		if (attackkey == 224)
		{
			attackkey = _getch();
		}

		switch (attackkey)
		{
		case LEFT:
			pos.x--;
			break;
		case RIGHT:
			pos.x++;
			break;
		case UP:
			pos.y--;
			break;
		case DOWN:
			pos.y++;
			break;
		}

		picaso.SetLetterColor(m_AttackMap.GetMapStatus(erasepos));
		picaso.DrawMap2inside(mappos, m_AttackMap.GetMapStatus(erasepos));
		picaso.SetLetterColor(WHITE);
		picaso.DrawMap2inside(pos, SQUARE);
		erasepos = pos;

	}

	picaso.DrawMap2inside(pos, ECSE);

	m_AttackMap.ChangeStatusMap(pos, ATTACK);

	return pos;
}

AttackResult Player::HitCheck(Position pos)
{
// 	Draw picaso;

	for (int i = 0; i < m_MyShip.size(); ++i)
	{
		AttackResult result = AR_NONE;
		MapDataTypes shipType = m_MyShip[i]->GetShipType();

		//각각 배로 타입 변환하여 hitcheck
		if (shipType == MD_AIRCRAFT)
		{
			Aircraft* aircraft = (Aircraft*)m_MyShip[i];
			result = aircraft->HitCheck(pos);
		}
		else if (shipType == MD_BATTLESHIP)
		{
			BattleShip_* battleship = (BattleShip_*)m_MyShip[i];
			result = battleship->HitCheck(pos);
		}
		else if (shipType == MD_CRUISER)
		{
			Cruiser* cruiser = (Cruiser*)m_MyShip[i];
			result = cruiser->HitCheck(pos);
		}
		else if(shipType == MD_DESTROYER1 || shipType == MD_DESTROYER2)
		{
			Destroyer* destroyer = (Destroyer*)m_MyShip[i];
			result = destroyer->HitCheck(pos);
		}

		//hit나 destroy 인 경우 
		switch (result)
		{
		case AR_HIT:
			printf_s("HIT\n");
			m_MyMap.ChangeStatusMap(pos, MAP_HIT);
			break;
		case AR_DESTROY_AIRCRAFT:
			m_MyMap.ChangeStatusMap(pos, MAP_DESTROY);
			printf_s("AIRCREFT DESTROY\n");
			break;
		case AR_DESTROY_BATTLESHIP:
			m_MyMap.ChangeStatusMap(pos, MAP_DESTROY);
			printf_s("BATTLESHIP DESTROY\n");
			
			break;
		case AR_DESTROY_CRUISER:
			m_MyMap.ChangeStatusMap(pos, MAP_DESTROY);
			printf_s("CRUISER DESTROY\n");
			
			break;
		case AR_DESTROY_DESTROYER:
			m_MyMap.ChangeStatusMap(pos, MAP_DESTROY);
			printf_s("DESTROYER DESTROY\n");
			break;
		default:
			break;
		}

		//miss가 아닌 경우 바로 리턴
		if (result != AR_MISS)
		{
			return result;
		}
	}

	//반복문을 빠져 나오면 miss인 경우임
	printf_s("MISS\n");
	m_MyMap.ChangeStatusMap(pos, ATTACK);
	return AR_MISS;
}

bool Player::SettingCheck(Position pos, Direction direct, int shipNum)
{
	//임의로 정해진 좌표와 방향으로 미리 대입해 보고 겹친다 싶으면 false 반환
	for (int i = 0; i < m_MyShip[shipNum]->GetSize(); ++i)
	{
		if (m_MyMap.GetShipMapStatus(pos) != NOTHING)
		{
			return false;
		}

		switch (direct)
		{
		case EAST:
			pos.x = pos.x + 1;
			break;
		case SOUTH:
			pos.y = pos.y + 1;
			break;
		case WEST:
			pos.x = pos.x - 1;
			break;
		case NORTH:
			pos.y = pos.y - 1;
			break;
		default:
			printf_s("방향이 없습니다");
			getchar();
			break;
		}

	}

	//하나도 안 겹치면 true 반환
	return true;
	
}

void Player::PlayerInit()
{
	//배 초기화
	for (int i = 0; i < m_MyShip.size(); ++i)
	{
		m_MyShip[i]->shipInit();
	}

	//초기화
	m_MyMap.MapInit();
	m_AttackMap.MapInit();
	m_RemainShip = m_MyShip.size();

}

void Player::TakeAttackResult(Position attackpos, AttackResult result)
{
	switch (result)
	{
	case AR_MISS:
		m_AttackMap.ChangeStatusMap(attackpos, ATTACK);
		break;

	case AR_HIT:
		m_AttackMap.ChangeStatusMap(attackpos, MAP_HIT);
		break;
	}

	//destroy 인 경우
	if (result != AR_HIT && result != AR_MISS)
	{
		m_AttackMap.ChangeStatusMap(attackpos, MAP_HIT);
	}


}

Direction Player::NumToDirect(int directNum)
{
	switch (directNum)
	{
	case 1:
		return EAST;
		break;

	case 2:
		return SOUTH;
		break;

	case 3:
		return WEST;
		break;

	case 4:
		return NORTH;
		break;

	default:
		printf_s("잘 못된 방향 값");
		getchar();
		break;
	}
}


