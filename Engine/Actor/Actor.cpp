#include "Actor.h"
#include "Util/Utill.h"
#include "Render/Renderer.h"

#include "Engine/Engine.h"

#include <iostream>
#include <windows.h>

namespace Wannabe
{
	Actor::Actor(const char* image, const Vector2& pos, Color color)
		:m_Pos(pos), m_Color(color)
	{
		m_iWidth = static_cast<int>(strlen(image));
		this->m_Image = new char[m_iWidth+1];
		strcpy_s(this->m_Image, m_iWidth + 1, image);
	}

	Actor::~Actor()
	{
		SafeDeleteArray(m_Image);
	}

	void Actor::BeginPlay()
	{
		//플래그 설정
		m_bHasBeganPlay = true;
	}

	void Actor::Tick(float deltaTime)
	{

	}

	void Actor::Draw()
	{
		//렌더러에 데이터 제출
		Renderer::Get().Submit(m_Image, m_Pos, m_Color, m_SortingOrder);
	}

	void Actor::Destroy()
	{
		m_bDestroyRequested = true;

		OnDestroy();
	}

	void Actor::OnDestroy()
	{
	}

	void Actor::QuitGame()
	{
		Engine::Get().QuitEngine();
	}

	bool Actor::TestIntersect(const Actor* const other)
	{
		//aabb
		//현재는 크기가 1이기때문에 x좌표만 고려하면 됨
		int xMin = m_Pos.x;
		int xMax = m_Pos.x + m_iWidth - 1;

		int otherxMin = other->GetPosition().x;
		int otherxMax = other->GetPosition().x + other->m_iWidth - 1;

		// 안 겹치는 조건 확인
		if (otherxMin > xMax) //내 오른쪽 좌표보다 더 오른쪾에 있는 경우
			return false;

		if (otherxMax < xMin) // 내 왼쪽 좌표보다 더 왼쪽에 있는 경우.
			return false;

		// y는 크기가 1이기 때문에 좌표가 같은지 여부만 확인.
		return m_Pos.y == other->m_Pos.y;
	}

	void Actor::ChangeImage(const char* newImage)
	{
		// 기존 메모리 해제.
		SafeDeleteArray(m_Image);

		// 새로운 문자열 복사.
		m_iWidth = static_cast<int>(strlen(newImage));
		m_Image = new char[m_iWidth + 1];
		strcpy_s(m_Image, m_iWidth + 1, newImage);
	}

	void Actor::SetPosition(const Vector2& pos)
	{
		//Renderer::Draw(m_Pos, ' '); //빈칸 그리기 요청

		//변경할 위치가 현재 위치가 같으면 건너띔
		if (m_Pos == pos)
			return;
		// 새로운 위치 설정
		m_Pos = pos;
	}
}