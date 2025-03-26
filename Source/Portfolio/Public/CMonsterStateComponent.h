#pragma once

#include "Type.h"
#include "CoreMinimal.h"
#include "CMonsterStateComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMonsterStateChanged, EMonsterStateType, PrevState, EMonsterStateType, NewState);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_API UCMonsterStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCMonsterStateComponent();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE EMonsterStateType GetMonsterState()			{ return MonsterState; }

public:
	// EMonsterStateType
	//void SetGroundMode();
	//void SetFlyMode();
	void SetIdleMode();
	void SetActionMode();
	void SetStunnedMode();
	void SetKnockdownMode();
	void SetDeadMode();

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsIdleMode()		{ return MonsterState == EMonsterStateType::Idle; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsActionMode()		{ return MonsterState == EMonsterStateType::Action; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool ISStunnedMode()	{ return MonsterState == EMonsterStateType::Stunned; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool ISKnockdownMode()	{ return MonsterState == EMonsterStateType::Knockdown; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsDeadMode()		{ return MonsterState == EMonsterStateType::Dead; }

private:
	void ChangeStateType(EMonsterStateType InNewType);

public:
	UPROPERTY(BlueprintAssignable)
	FMonsterStateChanged OnStateChanged;

private:
	EMonsterStateType MonsterState;
};
