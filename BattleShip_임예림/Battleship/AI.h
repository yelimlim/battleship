#pragma once
#include "Player.h"

#define OVERDEGREE 100
#define ATTACKPOSITION 22 //MapRow * 3 - 2
#define LESSHITCHANCE 3 * 4 - 2
#define CENTERNUM 3 //(MapRow - 1)/2

struct Predict
{
	Position pos;
	Direction direct;

};

class AI :
	public Player
{
public:
	AI();
	~AI();

	Position	AttackShip();
	void		TakeAttackResult(Position attackpos, AttackResult result);
	void		SetBigAttackSize(int size) { m_HowBigAttackShip = size; };
	void		SetSmallAttackSize(int size){ m_HowSmallAttackShip = size; };

	void		PlayerInit();

private:
	vector <int>	m_RemainShipSize;
	Position*		m_AttackPosition[ATTACKPOSITION];
	bool			m_AttackFree;
	int				m_HowBigAttackShip;
	int				m_HowSmallAttackShip;
	HowDoIAttack	m_HowDoIAttack;

	int				m_AttackRemainShip;

	Position			m_FirstHitPosition;
	Position			m_LastHitPosition;
	Direction			m_ChaseDirecition;
	vector <Position>	m_Chasestack;
	vector <Position>	m_Leftstack;

	void	SetAttackArray();
	int		GetLessHitDegree(Position pos);
	bool	isedge(int number);

	int	 HowManyLeft(Position pos, Direction direct);
	bool isFourDirectionFine(Position pos);
	bool isThereShipPossible(Position pos, ShipShape shape);
	bool AttackMapChek(int numOfDirect);
	void ChaseStackCheck(AttackResult result);

	void SetSmallBig();

	Position AttackNewPlace();
	Position AttackSurround();
	Position AttackChase();

	ShipShape DirectToShape(Direction direct);


};

