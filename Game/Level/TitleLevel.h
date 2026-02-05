#pragma once
#include "Level/Level.h"
#include "Math/Color.h"

#include <vector>

using namespace Wannabe;

class TitleLevel : public Level
{
	RTTI_DECLARATIONS(TitleLevel, Level)
public:
	TitleLevel();
	~TitleLevel();

	virtual void Draw() override;
private:
	//현재 활성화된 메뉴 아이템 인덱스.
	int curIndex = 0;

	// 선택된 아이템의 색상.
	Color m_SelectedColor = Color::Green;

	// 선택되지 않은 아이템의 색상.
	Color m_DeselectedColor = Color::White;
};


