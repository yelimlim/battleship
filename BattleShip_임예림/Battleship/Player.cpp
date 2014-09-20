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
	// �� �ʱ�ȭ
	m_MyShip.push_back(new Aircraft());
	m_MyShip.push_back(new BattleShip_());
	m_MyShip.push_back(new Cruiser());
	m_MyShip.push_back(new Destroyer(1)); //MD_DESTROYER1
	m_MyShip.push_back(new Destroyer(2)); //MD_DESTROYER2

	// �ʱ�ȭ
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

//��Ʈ��ũ ���� setshipPosition : 2,3��° ���ڴ� ��ȯ ����
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
// 	printf_s("��");
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
// 			printf_s("��");
// 
// 			if (setship[num/2] == true)
// 			{
// 				picaso.GoTo(SHIPLISTX-1, SHIPLISTY+10);
// 				printf_s("�̹� ��ġ�� �� �Դϴ�.");
// 				shipkey = 0; // �ʱ�ȭ
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

	//true�� �Ǹ� �� ��ġ ����
	bool setReady = false;

	//�� ó�� ��ǥ
	Position pos;
	//�� ����
	Direction direct;

	while (setReady == false)
	{
		//��ǥ �� �޾Ƽ�
		pos = PositionSetting();
		//���� �ȿ� ������ Ȯ���ϰ�
		direct = DirectionSetting(pos, shipNum);
		//��ġ�� �ʴ��� Ȯ���Ѵ�
		setReady = SettingCheck(pos, direct, shipNum);
	}

	for (int i = 0; i < m_MyShip[shipNum]->GetSize(); ++i)
	{
		//picaso.DrawMap1inside(pos, m_MyShip[shipNum]->GetShipType());

		//Ȯ���� �� ��ġ �迡 ����
		m_MyShip[shipNum]->AddPosition(pos);
		//�׸��� �� ���� ����
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
			printf_s("������ �����ϴ�");
			getchar();
			break;
		}

	}

	//��ȯ�� �� Ÿ��
	out_shipType = m_MyShip[shipNum]->GetShipType();
	//��ȯ�� �� ũ��
	out_shipSize = m_MyShip[shipNum]->GetSize();

	//�� ó�� ��ǥ ��ȯ
	return m_MyShip[shipNum]->GetShipPosition();
}

void Player::SetShipPosition()
{
	//�ƹ� �� ���� ����
	MapDataTypes shiptype;
	int shipSize;

	//�� �� ��ġ
	for (int i = 0; i < m_MyShip.size(); ++i)
	{
		//2,3��° ���ڴ� ��Ʈ��ũ ��� ���� ����Ѵ�.
		SetShipPosition(i, shiptype, shipSize);
	}
}

//��� �� ���
void Player::PrintShips()
{
	for (int i = 0; i < m_MyShip.size(); ++i) 
	{
		m_MyShip[i]->Print();
	}
}

Position Player::PositionSetting()
{
	//���� ��ġ
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
	//�������� ��ǥ�� ���ϱ� ���� ���� ����
	int directionNum;
	//��͸� ���� ���� ���� �迭
	bool rightdirectarray[MAX_DIRECTION] = { true, true, true, true };

	for (int i = 0; i < MAX_DIRECTION; ++i)
	{
		do
		{
			directionNum = rand() % MAX_DIRECTION + 1; //Direction 0 -> NONE 
		} while (!rightdirectarray[directionNum - 1]); // �ߴ� �����ΰ�

		Direction direct = NumToDirect(directionNum);
		rightdirectarray[directionNum - 1] = false; // �� ������ üũ

		//���⿡ ���� �ʿ��� ������� üũ �� ���� ������ ��ȯ
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
			printf_s("������ �����ϴ�");
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

		//���� ��� Ÿ�� ��ȯ�Ͽ� hitcheck
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

		//hit�� destroy �� ��� 
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

		//miss�� �ƴ� ��� �ٷ� ����
		if (result != AR_MISS)
		{
			return result;
		}
	}

	//�ݺ����� ���� ������ miss�� �����
	printf_s("MISS\n");
	m_MyMap.ChangeStatusMap(pos, ATTACK);
	return AR_MISS;
}

bool Player::SettingCheck(Position pos, Direction direct, int shipNum)
{
	//���Ƿ� ������ ��ǥ�� �������� �̸� ������ ���� ��ģ�� ������ false ��ȯ
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
			printf_s("������ �����ϴ�");
			getchar();
			break;
		}

	}

	//�ϳ��� �� ��ġ�� true ��ȯ
	return true;
	
}

void Player::PlayerInit()
{
	//�� �ʱ�ȭ
	for (int i = 0; i < m_MyShip.size(); ++i)
	{
		m_MyShip[i]->shipInit();
	}

	//�ʱ�ȭ
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

	//destroy �� ���
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
		printf_s("�� ���� ���� ��");
		getchar();
		break;
	}
}


