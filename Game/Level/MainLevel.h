#pragma once
#include "Level/Level.h"
#include "Math/Vector2.h"

using namespace Wannabe;

/*
* todo
* 메인 레벨에서 해야할것
* map, player, 인카운트, 전투
*/

class MainLevel : public Level
{
	RTTI_DECLARATIONS(MainLevel, Level)
public:
	MainLevel();
	~MainLevel();

	//이벤트 함수 오버라이드
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

private:
	void Initialize();
	void LoadMap(const char* filename); // 맵 만들기

	// 오브젝트와 충돌 처리
	// 해당 오브젝트한테 invoke 또는 reactOn 시킨다.
	void CheckCollision();
	//virtual bool CanMove(const Vector2& playerPos, const Vector2& nextPos) override;

private:
	Vector2 m_vPlayerStartPos;
};

