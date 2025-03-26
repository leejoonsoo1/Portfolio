#pragma once

#include "Type.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChanged, EStateType, InPrevType, EStateType, InNewType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponTypeChanged, EWeaponType, InPrevType, EWeaponType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCStateComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Character StateType
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsIdleMode()			{ return StateType == EStateType::Idle; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsEvadeMode()			{ return StateType == EStateType::Evade; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsEquipMode()			{ return StateType == EStateType::Equip; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsUnEquipMode()		{ return StateType == EStateType::UnEquip; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsActionMode()			{ return StateType == EStateType::Action; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsHittedMode()			{ return StateType == EStateType::Hitted; }

	FORCEINLINE bool IsGroggyMode()			{ return StateType == EStateType::Groggy; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsDeadMode()			{ return StateType == EStateType::Dead; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE EStateType GetEStateType()	{ return StateType; }

public:
	// WeaponType
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsUnarmedMode()			{ return WeaponType == EWeaponType::Unarmed; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsSwordNShieldMode()		{ return WeaponType == EWeaponType::SwordNShield; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsGreatSwordMode()			{ return WeaponType == EWeaponType::GreatSword; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsLongSwordMode()			{ return WeaponType == EWeaponType::LongSword; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsHammerMode()				{ return WeaponType == EWeaponType::Hammer; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsLightBowgunMode()		{ return WeaponType == EWeaponType::LightBowgun; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsBowMode()				{ return WeaponType == EWeaponType::Bow; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsLanceMode()				{ return WeaponType == EWeaponType::Lance; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsDualBladesMode()			{ return WeaponType == EWeaponType::DualBlades; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsChargeBladeMode()		{ return WeaponType == EWeaponType::ChargeBlade; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsGunLanceMode()			{ return WeaponType == EWeaponType::GunLance; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsHeavyBowgunMode()		{ return WeaponType == EWeaponType::HeavyBowgun; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsSwitchAxeMode()			{ return WeaponType == EWeaponType::SwitchAxe; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE EWeaponType GetEWeaponType()	{ return WeaponType; }

public:
	// Monster's AI Behavior Type

public:
	// ¾È ¾¸.
	UFUNCTION(BlueprintPure)
	FORCEINLINE EWeaponType GetArmedWeaponType() { return ArmedWeaponType; }
	
public:
	// StateType
	void SetIdleMode();
	void SetEvadeMode();
	void SetEquipMode();
	void SetUnEquipMode();
	void SetActionMode();
	void SetHittedMode();
	void SetGroggyMode();
	void SetDeadMode();
	
public:
	// WeaponType
	void SetUnarmedMode();
	void SetSwordNShieldMode();
	void SetGreatSwordMode();
	void SetLongSwordMode();
	void SetHammerMode();
	void SetLightBowgunMode();
	void SetBowMode();
	void SetLanceMode();
	void SetDualBladesMode();
	void SetGunLanceMode();
	void SetHeavyBowgunMode();
	void SetSwitchAxeMode();

public:
	// ArmedWeaponType
	void SetArmedWeaponType(EWeaponType InNewArmedWeaponType);

private:
	void ChangeStateType(EStateType InNewType);
	void ChangeWeaponType(EWeaponType InNewType);

public:
	UPROPERTY(BlueprintAssignable)
	FStateTypeChanged OnStateTypeChanged;
	
	UPROPERTY(BlueprintAssignable)
	FWeaponTypeChanged OnWeaponTypeChanged;

private:
	EStateType StateType;
	EWeaponType WeaponType;
	EWeaponType ArmedWeaponType;
};
