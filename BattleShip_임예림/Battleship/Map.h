#pragma once
#include "struct.h"
struct MapStruct 
{
	Map_Status shipMap;
	Map_Status StatusMap;
};


class Map
{
public:
	Map();
	~Map();

	void ChangeShipMap(Position pos, Map_Status status);
	void ChangeShipMap(Position pos, MapDataTypes shipType);
	void ChangeStatusMap(Position pos, Map_Status status);

	void ChangeMapHitStatus(Position pos, MapDataTypes shipType);
	void ChangeMapDestroyStatus(Position pos, MapDataTypes shipType);

	Map_Status GetShipMapStatus(Position pos);
	Map_Status GetMapStatus(Position pos);
	Map_Status GetMapStatus(char x, char y);

	int GetMapRow(){ return m_Rows; };
	int GetMapColumn(){ return m_Columns; };

	bool IsInMap(Position pos);

	void MapInit();

private:
	int m_Rows = MAPROW;
	int m_Columns = MAPCOL;

	MapStruct m_Map[MAPROW][MAPCOL];
};

