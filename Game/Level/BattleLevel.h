#pragma once
#include "Level/Level.h"

using namespace Wannabe;

class BattleLevel : public Level
{
	enum class BattleState
	{
		Start, // 시작 연출
		CommandSelect, // 전투 메뉴 선택
		TurnCheck, // 행동 순서, 명령, 데미지 계산 // 정말 로직만 필요함
		Animation, // 스킬 이펙트, hp 감소연출, 상태 이상 표시
		Result //쓰러짐, 경험치, 배틀 종료 여부
	};

	RTTI_DECLARATIONS(BattleLevel, Level)

public:
	BattleLevel();
	~BattleLevel();

	void SetupBattle(std::vector<Actor*> vecPlayer, std::vector<Actor*> vecEnemy);

private:
	void Initialize(); // playani와 같은 것들을 진행한다.
	void PlayAni(); // 입장시 애니메이션 재생

	void Input(); // todo선택지를 입력받을 것
	virtual void Tick(float deltaTime); //로직에 따른 출력 및 행동을 보여주기 위해 사용
	virtual void Draw(); // 그리기용도

	void Draw_OutLine();

	void Phase_Start();
	void Phase_CommandSelect();
	void Phase_TurnCheck();
	void Phase_Animation();
	void Phase_Result();

	bool IsFinishBattle();
private:
	std::vector<Actor*> m_vecPlayerParty;
	std::vector<Actor*> m_vecEnemyParty;

	std::vector<Actor*> m_vecTurnOrder;//순서

	BattleState m_eBattleState;
};
