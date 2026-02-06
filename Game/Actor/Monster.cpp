#include "Monster.h"

Monster::Monster()
	:super("M",Vector2::Zero,Color::Magenta)
{
	m_eStat.m_iLv = 1;
	m_eStat.m_iHp = 10;
	m_eStat.m_iAtk = 1;
	m_eStat.m_iExp = 2;
	m_eStat.m_iTurnCnt = 1;
	m_eStat.m_iMaxTurnCnt = 5;
}

Monster::~Monster()
{
}
