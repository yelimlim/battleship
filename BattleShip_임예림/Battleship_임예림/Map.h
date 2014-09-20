#pragma once
class Map
{
public:
	Map();
	~Map();
public:
	void Print();
	void chagePin();
private:
	int m_Map[8,8] = {};

};

