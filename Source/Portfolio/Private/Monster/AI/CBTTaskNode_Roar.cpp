#include "CBTTaskNode_Roar.h"
#include "CAIController_Monster.h"
#include "CMonster.h"
#include "CBehaviorComponent.h"

UCBTTaskNode_Roar::UCBTTaskNode_Roar()
{
	NodeName = "Roar";
	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Roar::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACAIController_Monster* AIC = Cast<ACAIController_Monster>(OwnerComp.GetAIOwner());
	if (AIC == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("EBTNodeResult::Type UCBTTaskNode_Roar::ExecuteTask : AIC is nullptr"));

		return EBTNodeResult::Failed;
	}

	APawn* ControlledPawn = AIC->GetPawn();
	if (ControlledPawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("EBTNodeResult::Type UCBTTaskNode_Roar::ExecuteTask : ControlledPawn is nullptr"));

		return EBTNodeResult::Failed;
	}

	ACMonster* Monster = Cast<ACMonster>(ControlledPawn);
	if (Monster == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("EBTNodeResult::Type UCBTTaskNode_Roar::ExecuteTask : Monster is nullptr"));

		return EBTNodeResult::Failed;
	}

	if (Montage.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("EBTNodeResult::Type UCBTTaskNode_Roar::ExecuteTask : Montages array is empty"));

		return EBTNodeResult::Failed;
	}

	int32 RandomIndex = FMath::RandRange(0, Montage.Num() - 1);
	float Result = Monster->PlayAnimMontage(Montage[RandomIndex], Rate, Section);

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Roar::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
}
