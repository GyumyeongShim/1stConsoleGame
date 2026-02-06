#pragma once
#include "Actor\Actor.h"

using namespace Wannabe;

class Monster :  public Actor
{
	RTTI_DECLARATIONS(Monster,Actor)
public:
	Monster();
	~Monster();

private:
	//to do 임시로 스탯 개념
	int m_iHp = 10;
	int m_iAtk = 1;
	int m_iDef = 1;
	int m_iTurnCnt = 1; // ++1 Max되면 공격 가능.

	int m_iMaxTurnCnt = 10;
};

