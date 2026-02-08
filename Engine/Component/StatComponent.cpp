#include "StatComponent.h"
#include "Util/Utill.h"

#include <iostream>

using namespace Wannabe;

StatComponent::StatComponent()
{
}

StatComponent::StatComponent(const char* name, int hp, int MaxHp, int atk, int def, int maxTurnCnt)
: m_iHp(hp), m_iMaxHp(MaxHp), m_iAtk(atk), m_iDef(def), m_iTurnCnt(0), m_iMaxTurnCnt(maxTurnCnt)
{
	int iSize = static_cast<int>(strlen(name));
	this->m_chaName = new char[iSize + 1];

	strcpy_s(this->m_chaName, iSize + 1, name);
}

StatComponent::~StatComponent()
{
	SafeDeleteArray(m_chaName);
}

void StatComponent::Update(float deltaTime)
{
	m_iTurnCnt += static_cast<int>(deltaTime * 50);
	if (m_iTurnCnt > m_iMaxTurnCnt) m_iTurnCnt = m_iMaxTurnCnt;
}

void StatComponent::SetStatByData(StatData& data)
{
	data.iMaxHp = m_iMaxHp;
	data.iHp = m_iHp;
	data.iAtk = m_iAtk;
	data.iDef = m_iDef;

	data.iMaxExp = m_iMaxExp;
	data.iExp = m_iExp;

	data.iTurnCnt = m_iTurnCnt;
	data.iMaxTurnCnt = m_iMaxTurnCnt;
	data.chaName = m_chaName;
}

void StatComponent::ResetTurn()
{
	m_iTurnCnt = 0;
}

int StatComponent::CalcDamage(const StatComponent& target)
{
	int dmg = m_iAtk - target.m_iDef;
	if (dmg < 1)
		dmg = 1;

	return dmg;
}

void StatComponent::TakeDamage(int dmg)
{
	m_iHp -= dmg;
}

bool StatComponent::IsTurnMax()
{
	return m_iTurnCnt >= m_iMaxTurnCnt;
}

bool StatComponent::IsDead()
{
	if (m_iHp <= 0)
		return true;

	return false;
}
