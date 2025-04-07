#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController_Monster.generated.h"

class ACMonster;
class UCBehaviorComponent;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class PORTFOLIO_API ACAIController_Monster : public AAIController
{
	GENERATED_BODY()
	
public:
	ACAIController_Monster();

	float GetSightRadius();
	FORCEINLINE float GetBehaviorRange() { return BehaviorRange; }

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	UFUNCTION()
	void RemovePlayerKey();

public:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCBehaviorComponent* BehaviorComp;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UAIPerceptionComponent* PerceptionComp;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	bool bDrawRange;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float AdjustHeight;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float BehaviorRange;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Team")
	uint8 TeamID;

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBlackboardComponent* BlackboardComp;

	ACMonster* PossessedMonster;
	UAISenseConfig_Sight* Sight;

private:
	float LastRoarTime = 0.f;
	const float RoarInterval = 120.f;
	AActor* SensedActor;
	float LastSensedTime;
};