#pragma once
#include "Level/Level.h"
#include "Util/BattleCommand.h"

#include <queue>

using namespace Wannabe;

/*
시간 흐름 관리
게이지 업데이트
MaxTurn 감지
*/

/*
1.TurnCnt Check
m_vecTurnOrder에 만족한 Actor 추가
*****spd 스탯이 존재하면 해당 값으로 정렬

2.actor가 행동 선택
BattleCommand 생성

3. command 실행
*/

class UI_Dialogue;

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
	virtual void Tick(float deltaTime); //로직에 따른 출력 및 행동을 보여주기 위해 사용
	virtual void Draw(); // 그리기용도

private:
	void Initialize(); // playani와 같은 것들을 진행한다.
	void PlayAni(); // 입장시 애니메이션 재생

	void Input(); // todo선택지를 입력받을 것
	void Draw_OutLine();
	void Draw_Menu();
	void Draw_TargetMenu();

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

	std::vector<UI_Dialogue*> m_vecDialogue; // 메시지 표기, 재활용을 위해 사용.

	BattleState m_eBattleState;

	std::queue<BattleCommand*> m_queBattleCmd;

	int m_iCursorInx = 0; // 메뉴 커서
	int m_iTargetCursor = 0; // 타켓 커서, 최대 4마리까지...
};
