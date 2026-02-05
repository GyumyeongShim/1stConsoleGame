#pragma once
#include "Math/Vector2.h"
#include "Math/Color.h"

#include <vector>


// 콘솔이라서 일단 싱글톤으로 데이터를 받고 엔진쪽 로직에 얹혀 가는 방식으로 생각해보자.
namespace Wannabe
{
	class Actor;

	class WANNABE_API BattleManager
	{
		enum class BattleState
		{
			Start, // 시작 연출
			CommandSelect, // input할 선택지 나누기
			TurnCheck, // 행동 순서, 명령, 데미지 계산 // 정말 로직만 필요함
			Animation, // 스킬 이펙트, hp 감소연출, 상태 이상 표시
			Result //쓰러짐, 경험치, 배틀 종료 여부
		};
	public:
		BattleManager();
		BattleManager(std::vector<Actor*> vecPlayer, std::vector<Actor*> vecEnemy);
		~BattleManager();
		void Start(); // 전투를 진행함

	private:
		void Initialize(); // playani와 같은 것들을 진행한다.
		void PlayAni(); // 입장시 애니메이션 재생

		void Input(); // todo선택지를 입력받을 것
		void Update(float deltaTime); //로직에 따른 출력 및 행동을 보여주기 위해 사용
		void Draw(); // 그리기용도

	private:
		std::vector<Actor*> m_vecPlayerParty;
		std::vector<Actor*> m_vecEnemyParty;

		BattleState m_eBattleState;
	};
}

