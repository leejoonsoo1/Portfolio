#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController_Monster.generated.h"

class ACMonster_Rathalos;
class UCBehaviorComponent;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class PORTFOLIO_API ACAIController_Monster : public AAIController
{
	GENERATED_BODY()
	
public:
	ACAIController_Monster();

protected:
	virtual void BeginPlay() override;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	UFUNCTION()
	void RemovePlayerKey();

protected:
	//UPROPERTY(VisibleDefaultsOnly, Category = "Components", meta=(AllowPrivateAccess = "true"))
	//UCBehaviorComponent* BehaviorComp;

	//UPROPERTY(VisibleDefaultsOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	//UAIPerceptionComponent* PerceptionComp;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	bool bDrawRange;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float AdjustHeight;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float BehaviorRange;

private:
	ACMonster_Rathalos* PossessedMonster;
	UAISenseConfig_Sight* Sight;
};
