#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Level/Level.h"

#include <iostream>
#include <Windows.h>

Player::Player(const Vector2& pos)
	: super("P", pos, Color::RightBlue)
{
	// 그리기 우선순위 높게 설정.
	m_SortingOrder = 10;
}

const Vector2 Player::GetNextPos()
{
	return m_vNextPos;
}

void Player::BeginPlay()
{
	super::BeginPlay();
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	//esc키 처리
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitEngine();
		return;
	}

	//이동
	if (Input::Get().GetKeyDown(VK_LEFT))
	{
		m_Pos.x -= 1;
		if (m_Pos.x < 0)
			m_Pos.x = 0;

		m_vNextPos = m_Pos;
	}
	if (Input::Get().GetKeyDown(VK_RIGHT))
	{
		// 오른쪽 이동 처리.
		m_Pos.x += 1;
		if (m_Pos.x + m_iWidth > Engine::Get().GetWidth())
			m_Pos.x -= 1;

		m_vNextPos = m_Pos;
	}
	if (Input::Get().GetKeyDown(VK_UP))
	{
		m_Pos.y -= 1;
		if (m_Pos.y < 0)
			m_Pos.y = 0;

		m_vNextPos = m_Pos;
	}
	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		m_Pos.y += 1;
		if (m_Pos.y > Engine::Get().GetHeight())
			m_Pos.y -= 1;

		m_vNextPos = m_Pos;
	}
}

void Player::Draw()
{
	super::Draw();
}
