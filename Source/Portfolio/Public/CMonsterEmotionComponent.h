#pragma once

#include "Type.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CMonsterEmotionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMonsterEmotionStateChanged, EMonsterEmotionStateType, PrevState, EMonsterEmotionStateType, NewState);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_API UCMonsterEmotionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCMonsterEmotionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE EMonsterEmotionStateType GetEmotionState() { return MonsterEmotion; }

public:
	// EMonsterEmotionStateType
	void SetCalmMode();
	void SetAlertMode();
	void SetTiredMode();
	void SetEnragedMode();

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsCalmMode() { return MonsterEmotion == EMonsterEmotionStateType::Calm; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsAlertMode() { return MonsterEmotion == EMonsterEmotionStateType::Alert; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsTiredMode() { return MonsterEmotion == EMonsterEmotionStateType::Tired; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsEnragedMode() { return MonsterEmotion == EMonsterEmotionStateType::Enraged; }

private:
	void ChangeEmotionType(EMonsterEmotionStateType InNewType);

public:
	UPROPERTY(BlueprintAssignable)
	FMonsterEmotionStateChanged OnEmotionStateChanged;

private:
	EMonsterEmotionStateType MonsterEmotion;
};