#include "stdafx.h"
#include "Map.h"
#include <memory.h>


Map::Map()
{
	memset(m_Map,0,sizeof(m_Map));
}


Map::~Map()
{
}

void Map::ChangeShipMap(Position pos, Map_Status status)
{
	//char 좌표를 int 좌표로
	int mapX = pos.x - 'a';
	int mapY = pos.y - '1';

	//지도 위에 올리기
	m_Map[mapX][mapY].shipMap = status;

}

void Map::ChangeShipMap(Position pos, MapDataTypes shipType)
{
	//배 타입에 따라
	switch (shipType)
	{
	case MD_DESTROYER1:
	case MD_DESTROYER2:
		ChangeShipMap(pos, D);
		break;

	case MD_CRUISER:
		ChangeShipMap(pos, C);
		break;
	case MD_BATTLESHIP:
		ChangeShipMap(pos, B);
		break;
	case MD_AIRCRAFT:
		ChangeShipMap(pos, A);
		break;
	default:
		break;
	}
}

Map_Status Map::GetShipMapStatus(Position pos)
{
	int mapX = pos.x - 'a';
	int mapY = pos.y - '1';

	return (Map_Status)m_Map[mapX][mapY].shipMap;
}

Map_Status Map::GetMapStatus(char x, char y)
{
	Position pos;
	pos.x = x;
	pos.y = y;

	return GetMapStatus(pos);
}

Map_Status Map::GetMapStatus(Position pos)
{
	int mapX = pos.x - 'a';
	int mapY = pos.y - '1';

	return (Map_Status)m_Map[mapX][mapY].StatusMap;
}

void Map::ChangeStatusMap(Position pos, Map_Status status)
{
	int mapX = pos.x - 'a';
	int mapY = pos.y - '1';

	m_Map[mapX][mapY].StatusMap = status;
}

void Map::MapInit()
{
	memset(m_Map, 0, sizeof(m_Map));
}

bool Map::IsInMap(Position pos)
{
	if (pos.x - 'a' > m_Rows - 1 || pos.x - 'a'< 0)
	{
		return false;
	}

	if (pos.y - '1' > m_Columns - 1 || pos.y - '1' < 0)
	{
		return false;
	}

	return true;
}

