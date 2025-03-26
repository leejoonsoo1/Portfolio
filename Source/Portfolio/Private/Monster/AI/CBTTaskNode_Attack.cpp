#include "CBTTaskNode_Attack.h"
#include "CAIController_Monster.h"
#include "CMonster.h"
#include "CMonsterStateComponent.h"
#include "CBehaviorComponent.h"

UCBTTaskNode_Attack::UCBTTaskNode_Attack()
{
	NodeName = "Attack";
	bNotifyTick = true;

	Rate = 1.f;
	Section = NAME_None;
}

EBTNodeResult::Type UCBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController_Monster* AIC = Cast<ACAIController_Monster>(OwnerComp.GetAIOwner());
	if (AIC == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("EBTNodeResult::Type UCBTTaskNode_Attack::ExecuteTask : AIC is nullptr"));

		return EBTNodeResult::Failed;
	}

	APawn* ControlledPawn = AIC->GetPawn();
	if (ControlledPawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("EBTNodeResult::Type UCBTTaskNode_Attack::ExecuteTask : ControlledPawn is nullptr"));

		return EBTNodeResult::Failed;
	}

	ACMonster* Monster = Cast<ACMonster>(ControlledPawn);
	if (Monster == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("EBTNodeResult::Type UCBTTaskNode_Attack::ExecuteTask : Monster is nullptr"));

		return EBTNodeResult::Failed;
	}

	if (Montage.Num() < 1)
	{
		UE_LOG(LogTemp, Error, TEXT("EBTNodeResult::Type UCBTTaskNode_Attack::ExecuteTask : Montage is nullptr"));

		return EBTNodeResult::Failed;
	}
	else
	{
		int32 RandomIndex = FMath::RandRange(0, Montage.Num() - 1);

		Monster->PlayAttackMontage(Montage[RandomIndex], Rate, Section);
	}

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController_Monster* AIC = Cast<ACAIController_Monster>(OwnerComp.GetAIOwner());

	if (AIC == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UCBTTaskNode_Attack::TickTask : AIC is nullptr"));

		return;
	}

	APawn* ControlledPawn = AIC->GetPawn();
	if (ControlledPawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UCBTTaskNode_Attack::TickTask : ControlledPawn is nullptr"));

		return;
	}

	ACMonster* Monster = Cast<ACMonster>(ControlledPawn);
	if (Monster == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UCBTTaskNode_Attack::TickTask : Monster is nullptr"));

		return;
	}

	if (Monster->StateComp == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UCBTTaskNode_Attack::TickTask : StateComp is nullptr"));

		return;
	}

	if (Monster->StateComp->IsIdleMode())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}