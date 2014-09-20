// Battleship_�ӿ���.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <string>
#include <time.h>
#pragma warning(disable:4996)
#include <iostream>
#include <vector>
#include "Aircraft.h"
#include "struct.h"

std::vector<std::string>ships;



int _tmain(int argc, _TCHAR* argv[])
{

	Aircraft aircaft;


	aircaft.AddPosiotion();
	aircaft.GetHP();
	

	ships.push_back("Aircraft");
	ships.push_back("Battleship1");
	ships.push_back("Battleship2");
	ships.push_back("Cruiser");
	ships.push_back("Destroyer1");
	ships.push_back("Destroyer2");

	//scanf("%s", coordinate);

	int random;
	int ship;
	srand((unsigned int)time(NULL));

	
	

	while (!ships.empty()){
		std::string coordinate;

		std::cin >> coordinate;

		std::cout << std::endl;
		
		random = rand() % 3;

		int ran_ship = rand() % ships.size();

		switch (random)
		{
		case 0:

			printf_s("%s ���ߵǾ����ϴ�\n", ships[ran_ship].c_str());

			ships.erase(ships.begin() + ran_ship);

			printf_s("�����ִ� ��: ");

			for (int i = 0; i < ships.size(); i++){
				printf_s("%s ", ships[i].c_str());
			}

			std::cout << std::endl;
			break;

		case 1:
			printf_s("���������ϴ�\n");
			break;

		case 2:
			printf_s("�¾ҽ��ϴ�\n");
			break;
		}

	}

	printf_s("Game Over");

	getchar();

	return 0;
}

