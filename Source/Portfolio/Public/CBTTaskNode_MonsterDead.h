#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CBTTaskNode_MonsterDead.generated.h"

UCLASS()
class PORTFOLIO_API UCBTTaskNode_MonsterDead : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UCBTTaskNode_MonsterDead();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, Category = "Monstage", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* Montage;

	UPROPERTY(EditAnywhere, Category = "Monstage", meta = (AllowPrivateAccess = "true"))
	float Rate = 1.f;

	UPROPERTY(EditAnywhere, Category = "Monstage", meta = (AllowPrivateAccess = "true"))
	FName Section = NAME_None;
};