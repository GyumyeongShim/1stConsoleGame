#include "Level.h"
#include "Actor/Actor.h"

namespace Wannabe
{
	Level::Level()
	{
	}

	Level::~Level()
	{
		//메모리 정리
		for (Actor*& actor : m_vecActors)
		{
			if (actor)
			{
				delete actor;
				actor = nullptr;
			}
		}

		//배열 초기화
		m_vecActors.clear();
	}

	void Level::BeginPlay()
	{
		// 액터에 이벤트 흘리기
		for (Actor* actor : m_vecActors)
		{
			// 게임 진행 도중에 생성된 경우에도 진행해야하니까.
			//고정된 형태로 한다면 필요 없을 수 있음.
			if (actor->HasBeganPlay())
				continue;

			actor->BeginPlay();
		}
	}

	void Level::Tick(float deltaTime)
	{
		// 액터에 이벤트 흘리기
		for (Actor* actor : m_vecActors)
		{
			actor->Tick(deltaTime);
		}
	}

	void Level::Draw()
	{
		//// 액터에 이벤트 흘리기
		//for (Actor* actor : m_vecActors)
		//{
		//	//같은 위치에 다른 액터가 있는지 확인하기 위함
		//	Actor* search = nullptr;
		//	for (Actor* otherActor : m_vecActors)
		//	{
		//		if(actor == otherActor)
		//			continue;

		//		if (actor->GetPosition() == otherActor->GetPosition())
		//		{
		//			//정렬 순서 비교
		//			if (actor->GetSortingOrder() < otherActor->GetSortingOrder())
		//			{
		//				search = otherActor;
		//				break;
		//			}
		//		}	
		//	}

		//	//같은 위치에 우선 순위 높은 다른 액터가 있으면 안그림
		//	if (search)
		//		continue;

		//	actor->Draw();
		//}
		for (Actor* const actor : m_vecActors)
		{
			if (actor->IsActive() == false)
				continue;

			actor->Draw();
		}
	}

	void Level::AddNewActor(Actor* newActor)
	{
		//todo 프레임 처리 고려 안하고 작업한 것이라 수정 필요함
		m_vecAddRequestedActors.emplace_back(newActor);

		//오너쉽 설정
		newActor->SetOwner(this);
	}

	void Level::ProcessAddAndDestroyActors()
	{
		//추가 먼저하면 loop가 많아진 상태로 도니까
		// 제거 처리
		for(int ix=0;ix<static_cast<int>(m_vecActors.size());)
		{
			//제거 요청된 액터라면
			if (m_vecActors[ix]->IsDestroyRequested())
			{
				delete m_vecActors[ix];
				m_vecActors.erase(m_vecActors.begin() + ix);
				continue;
			}

			++ix;
		}

		//추가 처리
		if (m_vecAddRequestedActors.empty() == true)
			return;

		for(Actor* const actor : m_vecAddRequestedActors)
		{
			m_vecActors.emplace_back(actor);
		}

		m_vecAddRequestedActors.clear();
	}
}