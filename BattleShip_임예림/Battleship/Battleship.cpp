// Battleship.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Battleship.h"
#include "Player.h"
#include "GameManager.h"
#include "Draw.h"
#include "NetworkManager.h"

#define ATTACKPOSITION 22 //MapRow * 3 - 2
#define LESSHITCHANCE 3 * 4 - 2


int _tmain(int argc, _TCHAR* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//Player* test = new Player();
	//system("mode con:cols=85 lines=39");

// 	Draw picaso;
// 
// 	picaso.GoTo(MAP1X + 2, MAP1Y - 1);
// 	printf_s("MY MAP");
// 	picaso.GoTo(MAP2X + 22, MAP2Y + 17);
// 	printf_s("ENEMY MAP");
// 	picaso.DrawMap();

	//네트워크 부분..
// 	try
// 	{
// 		Network::Initialize();
// 	}
// 	catch (Network::Exception)
// 	{
// 		puts("초기화 도중 문제가 발생했습니다.");
// 		return -1;
// 	}
// 
// 	NetworkManager nM;
// 	nM.GameRun();

	//자체적으로 게임 돌리기
	srand(unsigned int(time(NULL)));

	GameManager gM;
	
	gM.GameRun(1000);

	getchar();
	getchar();
	return 0;
}

