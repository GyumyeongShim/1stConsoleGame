#pragma once
#include "Actor/Actor.h"

using namespace Wannabe;

enum class CommandType
{
	Atk,
	Run
};

class BattleCommand
{
public:
	Actor* Instigator = nullptr;
	Actor* Target = nullptr;
	CommandType Type = CommandType::Atk;
};