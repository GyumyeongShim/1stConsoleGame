#include "Player.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Level/Level.h"

#include "Interface/ICanPlayerMove.h"

#include <iostream>
#include <Windows.h>

Player::Player(const Vector2& pos)
	: super("P", pos, Color::RightBlue)
{
	// 그리기 우선순위 높게 설정.
	m_SortingOrder = 10;
}

void Player::BeginPlay()
{
	super::BeginPlay();

	canPlayerMoveInterface = dynamic_cast<ICanPlayerMove*>(GetOwner());
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
		Vector2 newPos(GetPosition().x - 1, GetPosition().y);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPos))
		{
			SetPosition(newPos);
		}

		if (m_Pos.x < 0)
			m_Pos.x = 0;

	}
	if (Input::Get().GetKeyDown(VK_RIGHT))
	{
		// 오른쪽 이동 처리.
		Vector2 newPos(GetPosition().x + 1, GetPosition().y);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPos))
		{
			SetPosition(newPos);
		}
		//m_Pos.x += 1;
		//if (m_Pos.x + m_iWidth > Engine::Get().GetWidth())
		//	m_Pos.x -= 1;
	}
	if (Input::Get().GetKeyDown(VK_UP))
	{
		Vector2 newPos(GetPosition().x, GetPosition().y - 1);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPos))
		{
			SetPosition(newPos);
		}

		if (m_Pos.y < 0)
			m_Pos.y = 0;
	}
	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		Vector2 newPos(GetPosition().x, GetPosition().y + 1);
		if (canPlayerMoveInterface->CanMove(GetPosition(), newPos))
		{
			SetPosition(newPos);
		}
	}
}

void Player::Draw()
{
	super::Draw();
}
