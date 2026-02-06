#include "Monster.h"

Monster::Monster()
	:super("M",Vector2::Zero,Color::Magenta)
{
	m_iHp = 10;
	m_iAtk = 1;
	m_iDef = 1;
	m_iTurnCnt = 1; // ++1 Max되면 공격 가능.

	m_iMaxTurnCnt = 10;
}

Monster::~Monster()
{
}
