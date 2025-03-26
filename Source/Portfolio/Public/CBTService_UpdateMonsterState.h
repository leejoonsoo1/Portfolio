#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_UpdateMonsterState.generated.h"

/*	
 *	2025 03 14
 * 
 */
UCLASS()
class PORTFOLIO_API UCBTService_UpdateMonsterState : public UBTService
{
	GENERATED_BODY()
	
public:
	UCBTService_UpdateMonsterState();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Distance", meta = (AllowPrivateAccess = "true"))
	float StopApproachDistance = 1500.f;
};