#include "CBTService_UpdateMonsterState.h"
#include "CMonsterStateComponent.h"
#include "CStateComponent.h"
#include "CAIController_Monster.h"
#include "CBehaviorComponent.h"

UCBTService_UpdateMonsterState::UCBTService_UpdateMonsterState()
{
	NodeName = "RootService_Monster";
}

void UCBTService_UpdateMonsterState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController_Monster* AIC = Cast<ACAIController_Monster>(OwnerComp.GetAIOwner());
	
	if (AIC == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AIC is nullptr"));

		return;
	}

	UCBehaviorComponent* BehaviorComp = Cast<UCBehaviorComponent>(AIC->GetComponentByClass(UCBehaviorComponent::StaticClass()));
	
	if (BehaviorComp == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("BehaviorComp is nullptr"));

		return;
	}

	APawn* MonsterPawn = AIC->GetPawn();

	if (MonsterPawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MonsterPawn is nullptr"));

		return;
	}

	UCMonsterStateComponent* MonsterStateComp = Cast<UCMonsterStateComponent>(MonsterPawn->GetComponentByClass(UCMonsterStateComponent::StaticClass()));

	if (MonsterStateComp == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MonsterStateComp is nullptr"));

		return;
	}

	if (MonsterStateComp->GetMonsterState() == EMonsterStateType::Dead)
	{
		BehaviorComp->SetWaitMode();
		AIC->GetBrainComponent()->StopLogic("Dead");
	}

	AActor* OtherActor = BehaviorComp->GetTargetValue();

	if (!OtherActor)
	{
		BehaviorComp->SetPatrolMode();

		return;
	}

	float Distance = MonsterPawn->GetDistanceTo(OtherActor);

	UCStateComponent* OtherStateComp = Cast<UCStateComponent>(OtherActor->GetComponentByClass(UCStateComponent::StaticClass()));

	if (OtherStateComp && OtherStateComp->IsDeadMode())
	{
		BehaviorComp->SetWaitMode();

		return;
	}

	// Set AttackMode
	if (Distance < AIC->GetBehaviorRange())
	{
		MonsterStateComp->SetAlertMode();
		BehaviorComp->SetAttackMode();

		return;
	}

	// Set ApproachMode
	if (Distance < AIC->GetSightRadius())
	{
		BehaviorComp->SetApproachMode();

		return;
	}
}