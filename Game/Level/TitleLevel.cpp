#include "TitleLevel.h"
#include "Core/Input.h"
#include "Game/Game.h"
#include "Render/Renderer.h"

#include <iostream>

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
	for (MenuItem*& item : m_vecItems)
	{
		delete item;
		item = nullptr;
	}

	m_vecItems.clear();
}

void TitleLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	//입력 처리 (방향키 위/아래키, 엔터, esc 사용)
	static int length = static_cast<int>(m_vecItems.size());
	if (Input::Get().GetKeyDown(VK_UP))
	{
		curIndex = (curIndex - 1 + length) % length;
	}
	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		curIndex = (curIndex + 1) % length;
	}
	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		m_vecItems[curIndex]->onSelected();
	}

	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		Game::Get().ToggleMenu(); // 메뉴 토글
		//인덱스 초기화
		curIndex = 0;
	}
}

void TitleLevel::Draw()
{
	//Renderer::Get().Submit(m_Image, m_Pos, m_Color, m_SortingOrder);

	for (int ix = 0; ix < static_cast<int>(m_vecItems.size()); ++ix)
	{
		Color txtColor = ix == curIndex ? m_SelectedColor : m_DeselectedColor;
		Renderer::Get().Submit(m_vecItems[ix]->text, Vector2(0, 2 + ix), txtColor);
		// 색상 설정
		//Util::SetConsoleTextColor(txtColor);
		// 텍스트 출력
		//std::cout << m_vecItems[ix]->text<<"\n";
	}
}
