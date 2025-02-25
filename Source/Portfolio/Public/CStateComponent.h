#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Type.h"
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
	UFUNCTION(BlueprintPure)
	bool IsIdleMode() { return StateType == EStateType::Idle; }

	UFUNCTION(BlueprintPure)
	bool IsEvadeMode() { return StateType == EStateType::Evade; }

	UFUNCTION(BlueprintPure)
	bool IsEquipMode() { return StateType == EStateType::Equip; }

	UFUNCTION(BlueprintPure)
	bool IsActionMode() { return StateType == EStateType::Action; }

	UFUNCTION(BlueprintPure)
	bool IsHittedMode() { return StateType == EStateType::Hitted; }

	UFUNCTION(BlueprintPure)
	bool IsDeadMode() { return StateType == EStateType::Dead; }

	UFUNCTION(BlueprintPure)
	EStateType GetEStateType() { return StateType; }

public:
	UFUNCTION(BlueprintPure)
	bool IsUnarmedMode() { return WeaponType == EWeaponType::Unarmed; }
	
	UFUNCTION(BlueprintPure)
	bool IsSwordNShieldMode() { return WeaponType == EWeaponType::SwordNShield; }
	
	UFUNCTION(BlueprintPure)
	bool IsGreatSwordMode() { return WeaponType == EWeaponType::GreatSword; }
	
	UFUNCTION(BlueprintPure)
	bool IsLongSwordMode() { return WeaponType == EWeaponType::LongSword; }
	
	UFUNCTION(BlueprintPure)
	bool IsHammerMode() { return WeaponType == EWeaponType::Hammer; }
	
	UFUNCTION(BlueprintPure)
	bool IsLightBowgunMode() { return WeaponType == EWeaponType::LightBowgun; }
	
	UFUNCTION(BlueprintPure)
	bool IsBowMode() { return WeaponType == EWeaponType::Bow; }
	
	UFUNCTION(BlueprintPure)
	bool IsLanceMode() { return WeaponType == EWeaponType::Lance; }
	
	UFUNCTION(BlueprintPure)
	bool IsDualBladesMode() { return WeaponType == EWeaponType::DualBlades; }
	
	UFUNCTION(BlueprintPure)
	bool IsChargeBladeMode() { return WeaponType == EWeaponType::ChargeBlade; }
	
	UFUNCTION(BlueprintPure)
	bool IsGunLanceMode() { return WeaponType == EWeaponType::GunLance; }
	
	UFUNCTION(BlueprintPure)
	bool IsHeavyBowgunMode() { return WeaponType == EWeaponType::HeavyBowgun; }
	
	UFUNCTION(BlueprintPure)
	bool IsSwitchAxeMode() { return WeaponType == EWeaponType::SwitchAxe; }
	
	UFUNCTION(BlueprintPure)
	EWeaponType GetEWeaponType() { return WeaponType; }

public:
	void SetIdleMode();
	void SetEvadeMode();
	void SetEquipMode();
	void SetActionMode();
	void SetHittedMode();
	void setDeadMode();
	
public:
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
};
