#include "Effect_BattleStart.h"
#include "Engine/Engine.h"

//현재 한줄씩 나오고 있어서 이슈임
// 한글자씩 나올 수 있게 수정이 필요함
//위 아래가 고려 없이 일단 나오고 있음

// B
static const char* B_LINE1 = "########";
static const char* B_LINE2 = "#       #";
static const char* B_LINE3 = "########";
static const char* B_LINE4 = "#       #";
static const char* B_LINE5 = "########";

// A
static const char* A_LINE1 = " ###### ";
static const char* A_LINE2 = "#      #";
static const char* A_LINE3 = "########";
static const char* A_LINE4 = "#      #";
static const char* A_LINE5 = "#      #";

// T
static const char* T_LINE1 = "#######";
static const char* T_LINE2 = "  ##  ";
static const char* T_LINE3 = "  ##  ";
static const char* T_LINE4 = "  ##  ";
static const char* T_LINE5 = "  ##  ";

// L
static const char* L_LINE1 = "##    ";
static const char* L_LINE2 = "##    ";
static const char* L_LINE3 = "##    ";
static const char* L_LINE4 = "##    ";
static const char* L_LINE5 = "#######";

// E
static const char* E_LINE1 = "#######";
static const char* E_LINE2 = "##     ";
static const char* E_LINE3 = "###### ";
static const char* E_LINE4 = "##     ";
static const char* E_LINE5 = "#######";

static const Effect_BattleStart::EffectFrame sequence[] =
{
    // Letter B (Red)
    Effect_BattleStart::EffectFrame(B_LINE1, 0.05f, Color::Red, Vector2(23,10)),
    Effect_BattleStart::EffectFrame(B_LINE2, 0.05f, Color::Red, Vector2(23,11)),
    Effect_BattleStart::EffectFrame(B_LINE3, 0.05f, Color::Red, Vector2(23,12)),
    Effect_BattleStart::EffectFrame(B_LINE4, 0.05f, Color::Red, Vector2(23,13)),
    Effect_BattleStart::EffectFrame(B_LINE5, 0.05f, Color::Red, Vector2(23,14)),

    // Letter A (Yellow)
    Effect_BattleStart::EffectFrame(A_LINE1, 0.05f, Color::Yellow, Vector2(28,10)),
    Effect_BattleStart::EffectFrame(A_LINE2, 0.05f, Color::Yellow, Vector2(28,11)),
    Effect_BattleStart::EffectFrame(A_LINE3, 0.05f, Color::Yellow, Vector2(28,12)),
    Effect_BattleStart::EffectFrame(A_LINE4, 0.05f, Color::Yellow, Vector2(28,13)),
    Effect_BattleStart::EffectFrame(A_LINE5, 0.05f, Color::Yellow, Vector2(28,14)),

    // First T (Green)
    Effect_BattleStart::EffectFrame(T_LINE1, 0.05f, Color::Green, Vector2(34,10)),
    Effect_BattleStart::EffectFrame(T_LINE2, 0.05f, Color::Green, Vector2(34,11)),
    Effect_BattleStart::EffectFrame(T_LINE3, 0.05f, Color::Green, Vector2(34,12)),
    Effect_BattleStart::EffectFrame(T_LINE4, 0.05f, Color::Green, Vector2(34,13)),
    Effect_BattleStart::EffectFrame(T_LINE5, 0.05f, Color::Green, Vector2(34,14)),

    // Second T (Red)
    Effect_BattleStart::EffectFrame(T_LINE1, 0.05f, Color::Red, Vector2(40,10)),
    Effect_BattleStart::EffectFrame(T_LINE2, 0.05f, Color::Red, Vector2(40,11)),
    Effect_BattleStart::EffectFrame(T_LINE3, 0.05f, Color::Red, Vector2(40,12)),
    Effect_BattleStart::EffectFrame(T_LINE4, 0.05f, Color::Red, Vector2(40,13)),
    Effect_BattleStart::EffectFrame(T_LINE5, 0.05f, Color::Red, Vector2(40,14)),

    // Letter L (Yellow)
    Effect_BattleStart::EffectFrame(L_LINE1, 0.05f, Color::Yellow, Vector2(46,10)),
    Effect_BattleStart::EffectFrame(L_LINE2, 0.05f, Color::Yellow, Vector2(46,11)),
    Effect_BattleStart::EffectFrame(L_LINE3, 0.05f, Color::Yellow, Vector2(46,12)),
    Effect_BattleStart::EffectFrame(L_LINE4, 0.05f, Color::Yellow, Vector2(46,13)),
    Effect_BattleStart::EffectFrame(L_LINE5, 0.05f, Color::Yellow, Vector2(46,14)),

    // Letter E (Green)
    Effect_BattleStart::EffectFrame(E_LINE1, 0.05f, Color::Green, Vector2(52,10)),
    Effect_BattleStart::EffectFrame(E_LINE2, 0.05f, Color::Green, Vector2(52,11)),
    Effect_BattleStart::EffectFrame(E_LINE3, 0.05f, Color::Green, Vector2(52,12)),
    Effect_BattleStart::EffectFrame(E_LINE4, 0.05f, Color::Green, Vector2(52,13)),
    Effect_BattleStart::EffectFrame(E_LINE5, 0.05f, Color::Green, Vector2(52,14))
};

Effect_BattleStart::Effect_BattleStart(const Vector2& position)
    : super(sequence[0].frame, sequence[0].Pos, sequence[0].color)
{
    m_iEffectSequenceCnt = sizeof(sequence) / sizeof(sequence[0]);
    m_tTimer.SetTargerTime(sequence[0].playTime);
    m_SortingOrder = 10;
}

void Effect_BattleStart::Tick(float deltaTime)
{
    super::Tick(deltaTime);

    m_tTimer.Tick(deltaTime);
    if (!m_tTimer.IsTimeOut())
    {
        return;
    }

    if (m_iCurSequenceIdx == m_iEffectSequenceCnt - 1)
    {
        Destroy();
        return;
    }

    m_tTimer.Reset();

    ++m_iCurSequenceIdx;

    m_tTimer.SetTargerTime(sequence[m_iCurSequenceIdx].playTime);

    ChangeImage(sequence[m_iCurSequenceIdx].frame);
    m_Pos = sequence[m_iCurSequenceIdx].Pos;

    m_Color = sequence[m_iCurSequenceIdx].color;
}