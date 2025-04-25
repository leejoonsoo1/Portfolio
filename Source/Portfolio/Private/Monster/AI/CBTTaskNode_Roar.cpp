#include "CBTTaskNode_Roar.h"
#include "CAIController_Monster.h"
#include "CMonster.h"
#include "CBehaviorComponent.h"
#include "GameFramework\CharacterMovementComponent.h"

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
		UE_LOG(LogTemp, Error, TEXT("%s : AIC is nullptr"), *FString(__FUNCTION__));

		return EBTNodeResult::Failed;
	}

	APawn* ControlledPawn = AIC->GetPawn();
	if (ControlledPawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : ControlledPawn is nullptr"), *FString(__FUNCTION__));

		return EBTNodeResult::Failed;
	}

	ACMonster* Monster = Cast<ACMonster>(ControlledPawn);
	if (Monster == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : Monster is nullptr"), *FString(__FUNCTION__));

		return EBTNodeResult::Failed;
	}

	if (Montage.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("%s : Montages array is empty"), *FString(__FUNCTION__));

		return EBTNodeResult::Failed;
	}

	Monster->GetCharacterMovement()->DisableMovement();

	int32 RandomIndex = FMath::RandRange(0, Montage.Num() - 1);
	float Result = Monster->PlayAnimMontage(Montage[RandomIndex], Rate, Section);

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Roar::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController_Monster* AIC = Cast<ACAIController_Monster>(OwnerComp.GetAIOwner());
	if (AIC == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : AIC is nullptr"), *FString(__FUNCTION__));
		
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		return;
	}

	APawn* ControlledPawn = AIC->GetPawn();
	if (ControlledPawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : ControlledPawn is nullptr"), *FString(__FUNCTION__));

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		return;
	}

	ACMonster* Monster = Cast<ACMonster>(ControlledPawn);
	if (Monster == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : StateComp is nullptr"), *FString(__FUNCTION__));

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		return;
	}

	if (Monster->EmotionComp == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : EmotionComp is nullptr"), *FString(__FUNCTION__));

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		return;
	}

	if (Monster->EmotionComp->IsEnragedMode())
	{
		Monster->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		Monster->GetCharacterMovement()->bOrientRotationToMovement = true;

		AIC->BehaviorComp->SetWaitMode();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		return;
	}
}