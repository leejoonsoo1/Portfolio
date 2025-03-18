#pragma once

#include "Type.h"
#include "CoreMinimal.h"
#include "CMonsterStateComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMonsterStateChanged, EMonsterStateType, PrevState, EMonsterStateType, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMonsterEmotionStateChanged, EMonsterEmotionStateType, PrevState, EMonsterEmotionStateType, NewState);


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

	UFUNCTION(BlueprintPure)
	FORCEINLINE EMonsterEmotionStateType GetEmotionState() const { return MonsterEmotion; }

public:


	// EMonsterEmotionStateType
	void SetCalmMode();
	void SetAlertMode();
	void SetTiredMode();
	void EnragedMode();

	// EMonsterStateType
	//void SetGroundMode();
	//void SetFlyMode();
	void SetIdleMode();
	void SetActionMode();
	void SetStunnedMode();
	void SetKnockdownMode();
	void SetDeadMode();

private:
	void ChangeStateType(EMonsterStateType InNewType);
	void ChangeEmotionType(EMonsterEmotionStateType InNewType);

public:
	UPROPERTY(BlueprintAssignable)
	FMonsterStateChanged OnStateChanged;

	UPROPERTY(BlueprintAssignable)
	FMonsterEmotionStateChanged OnEmotionStateChanged;
private:
	EMonsterStateType MonsterState;
	EMonsterEmotionStateType MonsterEmotion;
};
