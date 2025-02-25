#pragma once

#include "Type.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle, Evade, Equip, Action, Hitted, Dead, Max
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	SwordNShield, GreatSword, LongSword, Hammer, LightBowgun, Bow, Lance, DualBlades, ChargeBlade, GunLance, HeavyBowgun, SwitchAxe, Max
};