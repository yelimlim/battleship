// Battleship.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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

	//��Ʈ��ũ �κ�..
// 	try
// 	{
// 		Network::Initialize();
// 	}
// 	catch (Network::Exception)
// 	{
// 		puts("�ʱ�ȭ ���� ������ �߻��߽��ϴ�.");
// 		return -1;
// 	}
// 
// 	NetworkManager nM;
// 	nM.GameRun();

	//��ü������ ���� ������
	srand(unsigned int(time(NULL)));

	GameManager gM;
	
	gM.GameRun(1000);

	getchar();
	getchar();
	return 0;
}

