#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_UpdateMonsterState.generated.h"

/*	
 *	2025 03 14
 * 
 */

class UCBehaviorComponent;

UCLASS()
class PORTFOLIO_API UCBTService_UpdateMonsterState : public UBTService
{
	GENERATED_BODY()
	
public:
	UCBTService_UpdateMonsterState();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	void UpdateFacingOnly(class ACMonster* InMonster, class AActor* InTargetActor, float DeltaSeconds);
	void EnterRoarMode(float CurrentTime, UCBehaviorComponent* BehaviorComp);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Distance", meta = (AllowPrivateAccess = "true"))
	float StopApproachDistance = 1500.f;

private:
	float FirstSensedTime	= -1.f;
	float LastRoarTime		= -999.f;
	bool bHasSensedPlayer	= false;
	bool bRoaredOnce		= false;
};