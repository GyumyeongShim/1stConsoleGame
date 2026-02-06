#pragma once
#include "Actor\Actor.h"
#include "Util/Utill.h"
#include "Util/Timer.h"

using namespace Wannabe;
                             
class Effect_BattleStart : public Actor
{
	RTTI_DECLARATIONS(Effect_BattleStart, Actor)

	struct EffectFrame
	{
		EffectFrame(const char* frame, float playTime = 0.05f, Color color = Color::Red, Vector2 pos = Vector2::Zero)
			: playTime(playTime), color(color), Pos(pos)
		{
			// 문자열 설정.
			size_t length = strlen(frame) + 1;
			this->frame = new char[length];
			strcpy_s(this->frame, length, frame);
		}

		~EffectFrame()
		{
			SafeDeleteArray(frame);
		}

		// 문자열 변수 (화면에 보여줄 문자열).
		char* frame = nullptr;

		// 재생 시간.
		float playTime = 0.0f;

		// 색상.
		Color color = Color::White;
		Vector2 Pos = Vector2::Zero;
	};

public:
	Effect_BattleStart(const Vector2& position);

	virtual void Tick(float deltaTime) override;

private:
	// 시퀀스 문자열 수(배열 원소 수).
	int m_iEffectSequenceCnt = 0;

	// 현재 보여지는 시퀀스 인덱스.
	int m_iCurSequenceIdx = 0;

	// 애니메이션 재생에 사용할 타이머.
	// 시퀀스 사이에 시간 계산용.
	Timer m_tTimer;
};

//      ____        _   _   _      
//     |  _ \      | | | | | |     
//     | |_) | __ _| |_| |_| | ___ 
//     |  _ < / _` | __| __| |/ _ \
//     | |_) | (_| | |_| |_| |  __/
//     |____/ \__,_|\__|\__|_|\___|
//                                 
//    