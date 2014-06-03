﻿#pragma once
#include "EnumSet.h"

struct UnitData
{
	float		HP;
	float		MoveSpeed;
	float		MoveSpeedFormationBonus;
	float		MoveSpeedMapBonus;
	float		AttackRange;
	float		AttackRangeFormationBonus;
	float		AttackRangeMapBonus;
	float		AttackPower;
	float		AttackPowerFormationBonus;
	float		AttackPowerMapBonus;
	float		Defense;
	float		DefenseFormationBonus;
	float		DefenseMapBonus;
	ULONGLONG	AttackDelay;
	ULONGLONG	AttackDelayFormationBonus;
	ULONGLONG	AttackDelayMapBonus;
};

class UnitStatus ///# 네이밍이 중요한데.. 보통 xxxStatus라고 하면 계속 변하는 상태를 의미.. (보통 캐릭터 스탯)
{
public:
	static bool LoadUnitStatus( );

private:
	UnitStatus();
	~UnitStatus();

//public:
	// std::array<float, static_cast<size_t>(UnitType::UNIT_MAX)> UnitHP; // max 256 용량은 둘째치고 매번 캐스팅하면서 쓰느리 그냥 노가다?


};
extern UnitData	g_Arrow;
extern UnitData	g_Guard;
extern UnitData	g_Knight;
extern UnitData	g_Pike;
extern UnitData	g_Sword;
extern UnitData	g_King;
