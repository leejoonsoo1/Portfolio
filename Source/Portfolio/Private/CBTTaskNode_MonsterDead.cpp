#include "CBTTaskNode_MonsterDead.h"
#include "CAIController_Monster.h"
#include "CMonster.h"

UCBTTaskNode_MonsterDead::UCBTTaskNode_MonsterDead()
{
	NodeName = "Dead";
	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_MonsterDead::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController_Monster* AIC = Cast<ACAIController_Monster>(OwnerComp.GetAIOwner());
	if (AIC == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : AIC is nullptr"), *FString(__FUNCTION__));

		return EBTNodeResult::Failed;
	}

	APawn* ControlledPawn = AIC->GetPawn();
	if (ControlledPawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("^%s : ControlledPawn is nullptr"), *FString(__FUNCTION__));

		return EBTNodeResult::Failed;
	}

	ACMonster* Monster = Cast<ACMonster>(ControlledPawn);
	if (Monster == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : Monster is nullptr"), *FString(__FUNCTION__));

		return EBTNodeResult::Failed;
	}

	USkeletalMeshComponent* Mesh = Monster->GetMesh();
	if (Mesh == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : Mesh is nullptr"), *FString(__FUNCTION__));

		return EBTNodeResult::Failed;
	}

	Monster->PlayAnimMontage(Montage, Rate, Section);

	return ;
}

void UCBTTaskNode_MonsterDead::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}