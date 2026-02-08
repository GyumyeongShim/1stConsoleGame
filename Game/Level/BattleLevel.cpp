#include "BattleLevel.h"
#include "Game/Game.h"
#include "Actor/Actor.h"
#include "Util/Utill.h"
#include "Core/Input.h"
#include "Render/Renderer.h"

#include "Actor/Player.h"
#include "Actor/Monster.h"
#include "Actor/Wall.h"

#include "UI/UI_Dialogue.h"

#include "Effect/Effect_BattleStart.h"

#include <string>
#include <algorithm>

using namespace Wannabe;

BattleLevel::BattleLevel()
    :m_eBattleState(BattleState::Start)
{
    Initialize();
}

BattleLevel::~BattleLevel()
{
    for (Actor* actor : m_vecPlayerParty)
        delete actor;

    for (Actor* actor : m_vecEnemyParty)
        delete actor;

    m_vecPlayerParty.clear();
    m_vecEnemyParty.clear();
}

void BattleLevel::SetupBattle(std::vector<Actor*> vecPlayer, std::vector<Actor*> vecEnemy)
{
    m_vecPlayerParty = vecPlayer;
    m_vecEnemyParty = vecEnemy;

    m_eBattleState = BattleState::Start;
}

void BattleLevel::Tick(float deltaTime)
{
    super::Tick(deltaTime);

    Input();

    //실시간 로직 처리.
    switch (m_eBattleState)
    {
    case BattleLevel::BattleState::Start:
        Phase_Start();
        break;
    case BattleLevel::BattleState::CommandSelect:
        Phase_CommandSelect();
        break;
    case BattleLevel::BattleState::TurnCheck:
        Phase_TurnCheck();
        break;
    case BattleLevel::BattleState::Animation:
        Phase_Animation();
        break;
    case BattleLevel::BattleState::Result:
        Phase_Result();
        break;
    default:
        break;
    }
}

void BattleLevel::Draw()
{
    super::Draw();
    Draw_OutLine();

    if (m_eBattleState == BattleState::CommandSelect)
        Draw_Menu();
    else if (m_eBattleState == BattleState::TurnCheck)
        Draw_TargetMenu();
}

void BattleLevel::Initialize()
{
    // todo 임시UI, 연출 이후 진행
    //AddNewActor(new Effect_BattleStart(Vector2::Zero));
    AddNewActor(new UI_Dialogue("dialogue 1", Vector2(2, 14), Color::Green));
    AddNewActor(new UI_Dialogue("Text12342432", Vector2(2, 15), Color::Green));
}

void BattleLevel::PlayAni()
{
    //Util::TurnOffCursor();
    //Util::ClearScreen();

    int iWidth = Renderer::Get().GetScreenSize().x;
    int iHeight = Renderer::Get().GetScreenSize().y;

    for (int y = 0; y < iHeight; ++y)
    {
        for (int x = 0; x < iWidth / 2; ++x)
        {
            // 좌우 대칭
            int mirroredX = x;

            // 그라데이션 색상 설정
            Color color;
            float ratio = static_cast<float>(y) / iHeight;
            if (ratio < 0.33f) color = Color::RightGray;           // 밝은 영역
            else if (ratio < 0.66f) color = Color::Blue;           // 중간
            else color = Color::RightBlue;       // 어두운 영역

            // 좌측
            Renderer::Get().Submit("W", Vector2(mirroredX, y), color, 0);

            // 우측 (좌우 대칭)
            Renderer::Get().Submit("0", Vector2(iWidth - 1 - mirroredX, y), color, 0);
        }

        Renderer::Get().Draw();

        //float t = static_cast<float>(y) / iHeight;

        // ease-out 느낌
        //int delay = static_cast<int>(20 + 80 * t * t);
        //std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}

void BattleLevel::Input()
{
    if (m_eBattleState == BattleState::CommandSelect)
        Phase_CommandSelect();
    else if (m_eBattleState == BattleState::TurnCheck)
        Draw_TargetMenu();
}

void BattleLevel::Draw_OutLine()
{
    // 배틀로직에서 사용될 테두리를 그립니다.
    const int width = 80;
    const int height = 25;

    for (int y = 0; y < height; ++y) 
    {
        for (int x = 0; x < width; ++x) 
        {
            if (y == 0 || y == height - 1 || x == 0 || x == width -1) 
            {   
                Renderer::Get().Submit("@", Vector2(x, y));
            }
        }
    }
}

void BattleLevel::Draw_Menu()
{    
    const int boxX = 56;
    const int boxY = 16;

    Renderer::Get().Submit("┌─────────┐", Vector2(boxX, boxY));
    Renderer::Get().Submit("│                  │", Vector2(boxX, boxY + 1));
    Renderer::Get().Submit("│                  │", Vector2(boxX, boxY + 2));
    Renderer::Get().Submit("│                  │", Vector2(boxX, boxY + 3));
    Renderer::Get().Submit("│                  │", Vector2(boxX, boxY + 4));
    Renderer::Get().Submit("└─────────┘", Vector2(boxX, boxY + 5));
    
    const char* items[4] = { "FIGHT", "MAGIC", "ITEM", "RUN" };
    const int menuStartY = 17;
    const int cursorX = 58;
    const int textX = 59;

    for (int i = 0; i < 4; i++)
    {
        int current = 0;
        int y = menuStartY + i;

        // 커서
        bool bSelected = false;
        if (i == m_iCursorInx)
            bSelected = true;
        Renderer::Get().Submit(bSelected ? ">" : " ", Vector2(cursorX, y), bSelected ? Color::Green : Color::White);

        // 텍스트
        Renderer::Get().Submit(items[i], Vector2(textX, y), bSelected ? Color::Green : Color::White);
    }
}

void BattleLevel::Draw_TargetMenu()
{
}

void BattleLevel::Phase_Start()
{
    //전투 입장 Ani == Actor
    m_eBattleState = BattleState::TurnCheck;
}

void BattleLevel::Phase_CommandSelect()
{
    //플레이어 여부
    if (m_vecPlayerParty.empty())
        return;

    // 턴 Max actor 여부
    Actor* curActor = m_vecTurnOrder.empty() ? nullptr : m_vecTurnOrder.front();
    if (curActor == nullptr)
        return;

    //메뉴 선택
    const int menuCount = 4;

    // 커서 이동
    if (Input::Get().GetKeyDown(VK_UP))
    {
        m_iCursorInx--;
        if (m_iCursorInx < 0)
            m_iCursorInx = menuCount - 1;
    }

    if (Input::Get().GetKeyDown(VK_DOWN))
    {
        m_iCursorInx++;
        if (m_iCursorInx >= menuCount)
            m_iCursorInx = 0;
    }

    if (Input::Get().GetKeyDown(VK_RETURN))
    {
        switch (m_iCursorInx)
        {
        case 0: // FIGHT
            break;
        case 1: // MAGIC
            break;
        case 2: // ITEM
            break;
        case 3: // RUN
            break;
        default:
            break;
        }

        // 선택 후 다음 상태로 진행
        m_eBattleState = BattleState::Animation;
    }

    if (m_iCursorInx >= 4)
        m_iCursorInx = 1;

    if (m_iCursorInx <= 0)
        m_iCursorInx = 0;
}

void BattleLevel::Phase_TurnCheck()
{
    for (Actor* actor : m_vecPlayerParty)
    {
        if (actor->GetStat()->IsTurnMax() == true)
        {
            BattleCommand* cmd = new BattleCommand();
            cmd->Instigator = actor;
            cmd->Type = CommandType::Atk;
            if (m_vecEnemyParty.empty() == false)
                cmd->Target = m_vecEnemyParty[0];
            m_queBattleCmd.push(cmd);
        }
    }

    for (Actor* enemyActor : m_vecEnemyParty)
    {
        if (enemyActor->GetStat()->IsTurnMax() == true)
        {
            BattleCommand* cmd = new BattleCommand();
            cmd->Instigator = enemyActor;
            cmd->Type = CommandType::Atk;
            if (m_vecPlayerParty.empty() == false)
                cmd->Target = m_vecPlayerParty[0];

            m_queBattleCmd.push(cmd);
        }
    }

    if(m_queBattleCmd.empty() == false)
        m_eBattleState = BattleState::Animation;
}

void BattleLevel::Phase_Animation()
{
    if (m_queBattleCmd.empty() == true)
    {
        m_eBattleState = BattleState::TurnCheck;
        return;
    }

    BattleCommand* cmd = m_queBattleCmd.front();
    m_queBattleCmd.pop();
    Actor* Attacker = cmd->Instigator;
    Actor* Target = cmd->Target;
    if (Attacker && Target)
    {
        int dmg = Attacker->GetStat()->CalcDamage(*Target->GetStat());
        Target->GetStat()->TakeDamage(dmg);

        if (Target->GetStat()->IsDead() == true)
        {
            auto& vec = (Target->GetTeam() == Team::Player)
                ? m_vecPlayerParty : m_vecEnemyParty;

            vec.erase(std::remove(vec.begin(), vec.end(), Target), vec.end());
        }

        Attacker->GetStat()->ResetTurn(); //공격자 턴 초기화
    }


    delete cmd;
    if (IsFinishBattle() == true)
    {
        m_eBattleState = BattleState::Result;
    }
    else
        m_eBattleState = BattleState::CommandSelect; // 다음 턴 준비
}

void BattleLevel::Phase_Result()
{
    //쓰러짐, 경험치, 배틀 종료 여부
    Game::Get().BattleEnd();
}

bool BattleLevel::IsFinishBattle()
{
    bool bFinished = false;
    if (m_vecPlayerParty.empty() == true)
        bFinished = true;

    if (m_vecEnemyParty.empty() == true)
        bFinished = true;

    return bFinished;
}
