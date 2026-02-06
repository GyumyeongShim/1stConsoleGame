#include "Effect_BattleStart.h"
#include "Engine/Engine.h"
// 효과 재생에 사용할 문자열 시퀀스 (일종의 애니메이션 프레임).
static const Effect_BattleStart::EffectFrame sequence[] =
{
	//Effect_BattleStart::EffectFrame("   B   ", 0.1f, Color::Red),
	//Effect_BattleStart::EffectFrame("  BA  ", 0.1f, Color::Yellow),
	//Effect_BattleStart::EffectFrame(" BAT  ", 0.1f, Color::Green),
	//Effect_BattleStart::EffectFrame("BATTLE!", 0.3f, Color::Red),
	//Effect_BattleStart::EffectFrame("BATTLE!", 0.3f, Color::Yellow),
	//Effect_BattleStart::EffectFrame("BATTLE!", 0.3f, Color::Green)

	//B
	Effect_BattleStart::EffectFrame("____ ", 0.1f, Color::Red,Vector2(23,10)),
	Effect_BattleStart::EffectFrame("_   _", 0.1f, Color::Red,Vector2(23,11)),
	Effect_BattleStart::EffectFrame("____ ", 0.1f, Color::Red,Vector2(23,12)),
	Effect_BattleStart::EffectFrame("_   _", 0.1f, Color::Red,Vector2(23,13)),
	Effect_BattleStart::EffectFrame("____ ", 0.1f, Color::Red,Vector2(23,14)),



	//ba
	Effect_BattleStart::EffectFrame("____ ", 0.1f, Color::Yellow,Vector2(23,10)),
	Effect_BattleStart::EffectFrame("_   _", 0.1f, Color::Yellow,Vector2(23,11)),
	Effect_BattleStart::EffectFrame("____ ", 0.1f, Color::Yellow,Vector2(23,12)),
	Effect_BattleStart::EffectFrame("_   _", 0.1f, Color::Yellow,Vector2(23,13)),
	Effect_BattleStart::EffectFrame("____ ", 0.1f, Color::Yellow,Vector2(23,14)),

	Effect_BattleStart::EffectFrame(" ___ ", 0.1f, Color::Yellow,Vector2(28,10)),
	Effect_BattleStart::EffectFrame("_   _", 0.1f, Color::Yellow,Vector2(28,11)),
	Effect_BattleStart::EffectFrame("_____", 0.1f, Color::Yellow,Vector2(28,12)),
	Effect_BattleStart::EffectFrame("_   _", 0.1f, Color::Yellow,Vector2(28,13)),
	Effect_BattleStart::EffectFrame("_   _", 0.1f, Color::Yellow,Vector2(28,14))

	////bat
	//Effect_BattleStart::EffectFrame("____ ", 0.1f, Color::Red),
	//Effect_BattleStart::EffectFrame("_   _", 0.1f, Color::Red),
	//Effect_BattleStart::EffectFrame("____ ", 0.1f, Color::Red),
	//Effect_BattleStart::EffectFrame("_   _", 0.1f, Color::Red),
	//Effect_BattleStart::EffectFrame("____ ", 0.1f, Color::Red),

	//Effect_BattleStart::EffectFrame(" ___ ", 0.1f, Color::Red),
	//Effect_BattleStart::EffectFrame("_   _", 0.1f, Color::Red),
	//Effect_BattleStart::EffectFrame("_____", 0.1f, Color::Red),
	//Effect_BattleStart::EffectFrame("_   _", 0.1f, Color::Red),
	//Effect_BattleStart::EffectFrame("_   _", 0.1f, Color::Red),



	//(23,10),(24,10),(25,10),(26,10)        -> ####
	//(23,11),(27,11)                        -> #   #
	//(23,12),(24,12),(25,12),(26,12)        -> ####
	//(23,13),(27,13)                        -> #   #
	//(23,14),(24,14),(25,14),(26,14)        -> ####

	//(28,10),(29,10),(30,10)                ->  ###
	//(28,11),(32,11)                        -> #   #
	//(28,12),(29,12),(30,12),(31,12),(32,12)-> #####
	//(28,13),(32,13)                        -> #   #
	//(28,14),(32,14)                        -> #   #

	//(34,10),(35,10),(36,10),(37,10),(38,10) -> #####
	//(36,11)                                 ->   #
	//(36,12)                                 ->   #
	//(36,13)                                 ->   #
	//(36,14)                                 ->   #

	//(34,10),(35,10),(36,10),(37,10),(38,10) -> #####
	//(36,11)                                 ->   #
	//(36,12)                                 ->   #
	//(36,13)                                 ->   #
	//(36,14)                                 ->   #

	//(46,10)								  -> #
	//(46,11)								  -> #
	//(46,12)								  -> #
	//(46,13)								  -> #
	//(46,14),(47,14),(48,14),(49,14),(50,14) -> #####
	
	//(52,10),(53,10),(54,10),(55,10),(56,10) -> #####
	//(52,11)                                 -> #
	//(52,12),(53,12),(54,12),(55,12)         -> ####
	//(52,13)                                 -> #
	//(52,14),(53,14),(54,14),(55,14),(56,14) -> #####
};

Effect_BattleStart::Effect_BattleStart(const Vector2& position)
	: super(sequence[0].frame, position, Color::Red)
{
	// x 위치 고정.
	//int effectFrameImageLength = 8;
	//this->m_Pos.x = position.x < 0 ? effectFrameImageLength + position.x : position.x;
	//this->m_Pos.x = position.x + effectFrameImageLength > Engine::Get().GetWidth() ?
	//	position.x - effectFrameImageLength : position.x;

	m_Pos = { 35,12 }; //강제로 중앙값을 입력

	// 애니메이션 시퀀스 개수 구하기.
	m_iEffectSequenceCnt = sizeof(sequence) / sizeof(sequence[0]);

	// 다음 애니메이션까지 대기할 시간.
	m_tTimer.SetTargerTime(sequence[0].playTime);

	// 색상 설정.
	m_Color = sequence[0].color;

	m_SortingOrder = 10;
}

void Effect_BattleStart::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 애니메이션 재생을 위한 타이머 업데이트.
	m_tTimer.Tick(deltaTime);
	if (!m_tTimer.IsTimeOut())
	{
		return;
	}

	// 애니메이션 재생 끝났는지 확인.
	// 끝났으면 삭제.
	if (m_iCurSequenceIdx == m_iEffectSequenceCnt - 1)
	{
		Destroy();
		return;
	}

	// 타이머 리셋.
	m_tTimer.Reset();

	// 이펙트 프레임 업데이트.
	++m_iCurSequenceIdx;

	// 다음 시퀀스에서 재생할 시간으로 타이머 재설정.
	m_tTimer.SetTargerTime(sequence[m_iCurSequenceIdx].playTime);

	// 애니메이션 프레임에 사용할 문자열을 액터에 복사.
	ChangeImage(sequence[m_iCurSequenceIdx].frame);
	m_Pos = sequence[m_iCurSequenceIdx].Pos;

	// 색상 설정.
	m_Color = sequence[m_iCurSequenceIdx].color;
}
