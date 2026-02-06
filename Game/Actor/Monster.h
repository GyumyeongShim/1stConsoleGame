#pragma once
#include "Actor\Actor.h"

using namespace Wannabe;

class Monster :  public Actor
{
	RTTI_DECLARATIONS(Monster,Actor)
public:
	Monster();
	~Monster();

private:
};

