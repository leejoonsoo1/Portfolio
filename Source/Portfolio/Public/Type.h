#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Type.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle, Evade, Equip, UnEquip, Action, Hitted, Dead, Max
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Unarmed, SwordNShield, GreatSword, LongSword, Hammer, LightBowgun, Bow, Lance, DualBlades, ChargeBlade, GunLance, HeavyBowgun, SwitchAxe, Max
};

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	Ground, Fly, Max
};

UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Idle, Wait, Approach, Action, Patrol, Stun, RunAway, Max
};