#pragma once
#include "Actor\Actor.h"

using namespace Wannabe;

class Monster :  public Actor
{
	RTTI_DECLARATIONS(Monster,Actor)
public:
	Monster();
	~Monster();

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

private:
};

