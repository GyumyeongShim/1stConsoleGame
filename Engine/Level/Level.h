#pragma once

#include "Common/RTTI.h"
#include "Math/Vector2.h"
#include <vector>

namespace Wannabe
{
	class Actor;

	// 레벨에 있는 모든 액터 관리
	class WANNABE_API Level : public RTTI
	{
		RTTI_DECLARATIONS(Level, RTTI);

	public:
		Level();
		virtual ~Level();

		//게임 플레이 이벤트
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		//액터 추가 함수
		void AddNewActor(Actor* newActor); //전방선언을 여기서 해버림

		//액터 배열 접근자
		void ProcessAddAndDestroyActors();

	protected:
		//액터 배열
		std::vector<Actor*> m_vecActors;

		//실행 중 추가 요청된 액터의 배열
		std::vector<Actor*> m_vecAddRequestedActors;
	};
}

