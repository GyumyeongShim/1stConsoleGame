#pragma once
#include "Actor/Actor.h"

using namespace Wannabe;

class Bush : public Actor
{
	RTTI_DECLARATIONS(Bush, Actor)

public:
	Bush(const Vector2& pos);
	// 대미지 받았을 때 처리할 함수.
	void OnDamaged();
};
