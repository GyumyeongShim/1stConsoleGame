#pragma once

#include "Math/Vector2.h"

using namespace Wannabe;

class ICanPlayerMove
{
public:
	virtual bool CanMove(const Vector2& playerPos, const Vector2& nextPos) = 0;
};

