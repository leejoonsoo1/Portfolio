#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle, Evade, Equip, Action, Hitted, Dead, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChanged, EStateType, InPrevType, EStateType, InNewType);

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
	bool IsIdleMode()	{ return Type == EStateType::Idle; }

	UFUNCTION(BlueprintPure)
	bool IsEvadeMode()	{ return Type == EStateType::Evade; }

	UFUNCTION(BlueprintPure)
	bool IsEquipMode()	{ return Type == EStateType::Equip; }

	UFUNCTION(BlueprintPure)
	bool IsActionMode() { return Type == EStateType::Action; }

	UFUNCTION(BlueprintPure)
	bool IsHittedMode()	{ return Type == EStateType::Hitted; }

	UFUNCTION(BlueprintPure)
	bool IsDeadMode()	{ return Type == EStateType::Dead; }

	void SetIdleMode();
	void SetEvadeMode();
	void SetEquipMode();
	void SetActionMode();
	void SetHittedMode();
	void setDeadMode();
	
private:
	void ChangeType(EStateType InNewType);

public:
	UPROPERTY(BlueprintAssignable)
	FStateTypeChanged OnStateTypeChanged;
		
private:
	EStateType Type;
};
