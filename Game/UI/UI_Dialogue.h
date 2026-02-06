#pragma once
#include "Actor\Actor.h"
#include "Util/Utill.h"
#include "Util/Timer.h"

using namespace Wannabe;

class UI_Dialogue : public Actor
{
	RTTI_DECLARATIONS(UI_Dialogue, Actor)
public:
	UI_Dialogue(const char* txt, const Vector2 pos, Color color);

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
private:
	void Checktxt(); //데미지,경험치 등 특별한 문자들은 다른 색상으로 표기할 수 있게 체크
};

