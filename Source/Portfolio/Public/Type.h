#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Type.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle	UMETA(DisplayName = "Idle"),
	Evade	UMETA(DisplayName = "Wait"),
	Equip	UMETA(DisplayName = "Equip"),
	UnEquip UMETA(DisplayName = "UnEquip"),
	Action	UMETA(DisplayName = "Action"),
	Hitted	UMETA(DisplayName = "Hitted"),
	Groggy	UMETA(DisplayName = "Groggy"),
	Dead	UMETA(DisplayName = "Dead"),
	Max		UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Unarmed			UMETA(DisplayName = "Unarmed"), 
	SwordNShield	UMETA(DisplayName = "SwordNShield"), 
	GreatSword		UMETA(DisplayName = "GreatSword"), 
	LongSword		UMETA(DisplayName = "LongSword"), 
	Hammer			UMETA(DisplayName = "Hammer"), 
	LightBowgun		UMETA(DisplayName = "LightBowgun"), 
	Bow				UMETA(DisplayName = "Bow"), 
	Lance			UMETA(DisplayName = "Lance"), 
	DualBlades		UMETA(DisplayName = "DualBlades"), 
	ChargeBlade		UMETA(DisplayName = "ChargeBlade"), 
	GunLance		UMETA(DisplayName = "GunLance"), 
	HeavyBowgun		UMETA(DisplayName = "HavyBowgun"), 
	SwitchAxe		UMETA(DisplayName = "SwitchAxe"), 
	Max				UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EMonsterEmotionStateType : uint8
{
	Calm		UMETA(DispalyName = "Calm"),
	Alert		UMETA(DisplayName = "Alert"),
	Tired		UMETA(DisplayName = "Tired"),
	Enraged		UMETA(DisplayName = "Enraged"),
	Max         UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EMonsterStateType : uint8
{
	Ground		UMETA(DisplayName = "Ground"),
	Fly			UMETA(DisplayName = "Fly"),

	Idle		UMETA(DisplayName = "Idle"),
	Action		UMETA(DisplayName = "Action"),
	Stunned		UMETA(DisplayName = "Stunned"),
	Knockdown	UMETA(DisplayName = "Knockdown"),
	Dead		UMETA(DisplayName = "Dead"),
	Max			UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EBehaviorType : uint8
{
	Wait		UMETA(DisplayName = "Wait"),	
	Approach 	UMETA(DisplayName = "Approach"),
	Attack		UMETA(DisplayName = "Attack"),
	Special		UMETA(DisplayName = "Special"),
	Patrol 		UMETA(DisplayName = "Patrol"),
	Flinch		UMETA(DisplayName = "Flinch"),
	RunAway		UMETA(DisplayName = "RunAway"),
	Search		UMETA(DisplayName = "Search"),
	Roar		UMETA(DisplayName = "Roar"),
	Land		UMETA(DisplayName = "Land"),
	Takeoff		UMETA(DisplayName = "Takeoff"),
	Max			UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ETargetDirectionType : uint8
{
	Front	UMETA(DisplayName = "Front"),
	Left	UMETA(DisplayName = "Left"),
	Right	UMETA(DisplayName = "Right"),
	Back	UMETA(DisplayName = "Back")
};