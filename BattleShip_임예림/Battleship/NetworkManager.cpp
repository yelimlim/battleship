#include "stdafx.h"
#include "NetworkManager.h"
#include "Player.h"
#include "AI.h"
#include "ShipData.h"


NetworkManager::NetworkManager()
{
	ErrorType error;

	m_player = new AI();

	try
	{
		network.Connect("10.73.42.117",9000);
	}
	catch (Network::Exception ex)
	{
		switch (ex)
		{
		case Network::NETWORK_ERROR:
			puts("������ ���ῡ �����߽��ϴ�.");
			break;
		case Network::PARAMETER_ERROR:
			puts("�Լ��� �μ��� �߸��Ǿ����ϴ�.");
			break;
		}
		return;
	}
	puts("���� ����!");

	
	error = network.SubmitName(L"Mong",141071);

	if (error == ET_DUPLICATED_NAME)
	{
		puts("�̹� �����ϴ� �̸��Դϴ�.");
		return;
	}



}


NetworkManager::~NetworkManager()
{
}

void NetworkManager::GameStart()
{
	PacketType type;
	ErrorType error;
	bool gameOver = false;

	Position attackpos;
	Position hitpos;

	while (!gameOver)
	{
		error = network.GetPacketType(&type);

		switch (type)
		{
		case PKT_SC_ERROR:
			if (error == ET_OPPOSITION_DISCONNECTED)
				puts("������ ������ ���������ϴ�.");
			else
				puts("�� �� ���� �����Դϴ�.");
			return;
			break;
		case PKT_SC_MY_TURN:
		{
			while (true)
			{
				if (m_player->GetType() == Ai)
				{
					AI* ai = (AI*)m_player;
					attackpos = ai->AttackShip();
				}
				else
				{
					attackpos = m_player->AttackShip();
				}

				printf_s("%c%c\n", attackpos.x, attackpos.y);

				error = network.SubmitAttack(PositionToCoord(attackpos));

				if (error == ET_INVALID_ATTACK)
					puts("��ȿ���� ���� ���� ��ġ�Դϴ�.");
				else
					break;
			}
		}
			break;
		case PKT_SC_ATTACK_RESULT:
		{
			Network::AttackResultData result;
			result = network.GetAttackResult();
			if (result.isMine)
			{
				puts("���� ���:");

				printf_s("%c%c ", result.pos.mX + 'a', result.pos.mY + '1');

				switch (result.attackResult)
				{
				case AR_DESTROY_AIRCRAFT:
					printf_s("Result: DESTROY_AIRCRAFT\n");
					break;
				case AR_DESTROY_BATTLESHIP:
					printf_s("Result: DESTROY_BATTLESHIP\n");
					break;
				case AR_DESTROY_CRUISER:
					printf_s("Result: DESTROY_CRUISER\n");
					break;
				case AR_DESTROY_DESTROYER:
					printf_s("Result: DESTROY_DESTROYER\n");
					break;
				case AR_HIT:
					printf_s("Result: HIT");
					break;
				case AR_MISS:
					printf_s("Result: MISS");
					break;

				}


				if (m_player->GetType() == Ai)
				{
					AI* ai = (AI*)m_player;
					ai->TakeAttackResult(attackpos, result.attackResult);
				}
				else
				{
					m_player->TakeAttackResult(attackpos, result.attackResult);
				}

			}
			else
			{
				puts("�ǰ� ���:");
				hitpos.x = result.pos.mX + 'a';
				hitpos.y = result.pos.mY + '1';

				m_player->HitCheck(hitpos);
				printf_s("%c%c", hitpos.x, hitpos.y);
			}
		}
			break;
		case PKT_SC_GAME_OVER:
		{
			Network::GameResultData gameresult;
			gameresult = network.GetGameResult();

			if (gameresult.isWinner)
				puts("�¸�!!!");
			else
				puts("�й�...");
			printf_s("�� ��: %d\n", gameresult.turns);
			gameOver = true;
		}
			break;
		default:
			throw Network::UNEXPECTED_PACKET;
			break;
		}

	}


}

void NetworkManager::GameInit()
{
	if (m_player->GetType() == Ai)
	{
		AI* ai = (AI*) m_player;
		ai->PlayerInit();
	}
	else
	{
		m_player->PlayerInit();
	}
	
}

void NetworkManager::GameRun()
{
	PacketType type;

	Network::GameStartData gameStartData;
	puts("���� ���� �����");
	network.WaitForStart(&gameStartData);
	wprintf_s(L"��Ī�Ǿ����ϴ�. ���� �̸�: %s, �й�: %d\n", gameStartData.oppositionName, gameStartData.oppositionStudentID);

	bool allOver = false;

	while (!allOver)
	{
		
		GameInit();
		ShipSetting();

		try
		{
			GameStart();
			network.GetPacketType(&type);

			if (type == PKT_SC_NEXT_GAME)
			{
				puts("���� ������ �غ����ּ���.");
				
			}
			else if (type == PKT_SC_ALL_OVER)
			{
				Network::FinalResultData finalresult;
				finalresult = network.GetFinalResult();
				puts("��� ����");
				printf_s("�¸� Ƚ��: %d, ��� �� ��: %.1f", finalresult.winCount, finalresult.avgTurns);

				allOver = true;
			}
			else
			{
				throw Network::UNEXPECTED_PACKET;
			}
		}
		catch (Network::Exception ex)
		{
			switch (ex)
			{
			case Network::NETWORK_ERROR:
				puts("��Ʈ��ũ�� ������ �߻��߽��ϴ�.");
				break;
			case Network::SERVER_CLOSED:
				puts("�������� ������ ���������ϴ�.");
				break;
			case Network::PARAMETER_ERROR:
				puts("�Լ��� �μ��� �߸��Ǿ����ϴ�.");
				break;
			case Network::UNEXPECTED_PACKET:
				puts("�������� �߸��� ������ ���۵Ǿ����ϴ�.");
				break;
			default:
				break;
			}
		}
		
	}
}

Coord NetworkManager::PositionToCoord(Position pos)
{
	Coord crd = Coord(pos.x, pos.y);

	return crd;
}

void NetworkManager::ShipSetting()
{
	ErrorType error;
	Position* shipPosition = nullptr;
	MapDataTypes shipType;
	char mapdata[MAP_SIZE];
	int shipSize;

	for (int i = 0; i < 5; ++i)
	{
		shipPosition = m_player->SetShipPosition(i, shipType, shipSize);

		for (int j = 0; j < shipSize; ++j)
		{
			Coord crd = PositionToCoord(shipPosition[j]);
			shipdata.SetShipCoord(shipType, j, crd);
			//printf_s("������");
		}
	}

	

	shipdata.ToMapData(mapdata);

	while (true)
	{
		error = network.SubmitMap(mapdata);
		if (error == ET_INVALID_MAP)
		{
			puts("��ȿ���� ���� �� �������Դϴ�.");
		}
		else
		{
			break;
		}
	}

	printf_s("\n");
	m_player->PrintShips();

}
