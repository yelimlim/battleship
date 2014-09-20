#pragma once

#define MAPROW 8
#define MAPCOL 8
#define MAX_DIRECTION 4



#define MAP1X 6
#define MAP1Y 4
#define MAP2X MAP1X+39
#define MAP2Y MAP1Y+13

#define SHIPLISTX	11
#define SHIPLISTY	MAP1Y+20
#define SHIPLISTGAP 2

#define LEFT		75      // 좌측방향키
#define RIGHT		77      // 우측방향키
#define UP			72      // 위쪽방향키
#define DOWN		80      // 아래방향키
#define ENTER		13
#define SPACEBAR	32

struct Position
{
	char x;
	char y;

};


enum Direction //배 방향
{
	NONE_DIRECTION,
	EAST,
	SOUTH,
	WEST,
	NORTH,
};

enum Map_Status
{
	NOTHING = 0,

	ON,

	A,
	B,
	C,
	D,

	ATTACK, //MISS
	MAP_HIT,
	MAP_DESTROY,

};

enum Color
{
	RED = 4,
	BRIGHTRED = 12,
	WHITE = 15
};

enum Arrow
{
	Arrow1 = '⇒'
};

enum WhatDraw
{
	ERASE,
	SQUARE,
	ECSE,
};

enum PlayerType
{
	HUMAN,
	Ai,
};

enum HowDoIAttack
{
	NOTFIND,
	ATTACKSURROUND,
	CHASEDIRECTION,
	CHASEOPPDIRECTION,
};

enum ShipShape
{
	COL,
	ROW,
};

enum ShipLength
{
	AIRCRAFTLENGTH = 5,
	BATTLESHIPLENGTH = 4,
	CRUISERLENGTH = 3,
	DESTROYERLENGTH = 2,
	MAX_LENGTH = AIRCRAFTLENGTH,
};