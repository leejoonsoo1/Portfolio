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
	FORCEINLINE EMonsterStateType GetMonsterState() const { return MonsterState; }

public:
	void SetGroundMode();
	void SetFlyMode();

	void SetCalmMode();
	void SetAlertMode();
	void SetTiredMode();
	void EnragedMode();
	void StunnedMode();
	void SetKnockdownMode();
	void SetDeadMode();

private:
	void ChangeStateType(EMonsterStateType InNewType);

public:
	UPROPERTY(BlueprintAssignable)
	FMonsterStateChanged OnStateChanged;

private:
	EMonsterStateType MonsterState;
};
