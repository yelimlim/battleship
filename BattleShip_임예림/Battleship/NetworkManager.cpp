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
			puts("서버와 연결에 실패했습니다.");
			break;
		case Network::PARAMETER_ERROR:
			puts("함수의 인수가 잘못되었습니다.");
			break;
		}
		return;
	}
	puts("접속 성공!");

	
	error = network.SubmitName(L"Mong",141071);

	if (error == ET_DUPLICATED_NAME)
	{
		puts("이미 존재하는 이름입니다.");
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
				puts("상대방의 접속이 끊어졌습니다.");
			else
				puts("알 수 없는 에러입니다.");
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
					puts("유효하지 않은 공격 위치입니다.");
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
				puts("공격 결과:");

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
				puts("피격 결과:");
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
				puts("승리!!!");
			else
				puts("패배...");
			printf_s("턴 수: %d\n", gameresult.turns);
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
	puts("게임 시작 대기중");
	network.WaitForStart(&gameStartData);
	wprintf_s(L"매칭되었습니다. 상대방 이름: %s, 학번: %d\n", gameStartData.oppositionName, gameStartData.oppositionStudentID);

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
				puts("다음 게임을 준비해주세요.");
				
			}
			else if (type == PKT_SC_ALL_OVER)
			{
				Network::FinalResultData finalresult;
				finalresult = network.GetFinalResult();
				puts("모두 종료");
				printf_s("승리 횟수: %d, 평균 턴 수: %.1f", finalresult.winCount, finalresult.avgTurns);

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
				puts("네트워크에 문제가 발생했습니다.");
				break;
			case Network::SERVER_CLOSED:
				puts("서버와의 연결이 끊어졌습니다.");
				break;
			case Network::PARAMETER_ERROR:
				puts("함수의 인수가 잘못되었습니다.");
				break;
			case Network::UNEXPECTED_PACKET:
				puts("서버에서 잘못된 정보가 전송되었습니다.");
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
			//printf_s("여까지");
		}
	}

	

	shipdata.ToMapData(mapdata);

	while (true)
	{
		error = network.SubmitMap(mapdata);
		if (error == ET_INVALID_MAP)
		{
			puts("유효하지 않은 맵 데이터입니다.");
		}
		else
		{
			break;
		}
	}

	printf_s("\n");
	m_player->PrintShips();

}
