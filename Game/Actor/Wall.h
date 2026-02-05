#pragma once
#include "Actor/Actor.h"

using namespace Wannabe;

class Wall : public Actor
{
	RTTI_DECLARATIONS(Wall, Actor)
public:
	Wall(const Vector2& pos);

private:
};

