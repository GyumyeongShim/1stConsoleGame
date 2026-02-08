#pragma once
#include "Common/Common.h"

namespace Wannabe
{
    struct StatData
    {
        int iMaxHp;
        int iHp;
        int iAtk;
        int iDef;

        int iMaxExp;
        int iExp;

        int iTurnCnt;
        int iMaxTurnCnt;
        char* chaName = nullptr;
    };

    class WANNABE_API StatComponent
    {
    public:
        StatComponent();
        StatComponent(const char* name, int hp = 10, int Maxhp = 10,int atk = 2, int def = 1, int maxTurnCnt = 10);
        ~StatComponent();

        void Update(float deltaTime);

        void SetStatByData(StatData& data);
        bool IsTurnMax();
        bool IsDead();
        void ResetTurn();
        int CalcDamage(const StatComponent& target);
        void TakeDamage(int dmg);

    private:
        int m_iHp;
        int m_iMaxHp;
        int m_iAtk;
        int m_iDef;

        int m_iExp;
        int m_iMaxExp;

        int m_iTurnCnt;
        int m_iMaxTurnCnt;
        char* m_chaName = nullptr;
    };
}
