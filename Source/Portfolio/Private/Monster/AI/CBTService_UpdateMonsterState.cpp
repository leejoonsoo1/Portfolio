#include "CBTService_UpdateMonsterState.h"
#include "CMonsterStateComponent.h"
#include "CStateComponent.h"
#include "CAIController_Monster.h"
#include "CBehaviorComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CMonster.h"

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
		UE_LOG(LogTemp, Error, TEXT("%s : AIC is nullptr"), *FString(__FUNCTION__));

		return;
	}

	UCBehaviorComponent* BehaviorComp = Cast<UCBehaviorComponent>(AIC->GetComponentByClass(UCBehaviorComponent::StaticClass()));
	
	if (BehaviorComp == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : BehaviorComp is nullptr"), *FString(__FUNCTION__));

		return;
	}

	APawn* MonsterPawn = AIC->GetPawn();
	ACMonster* Monster = Cast<ACMonster>(MonsterPawn);

	if (!Monster)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Monster is nullptr"), *FString(__FUNCTION__));

		return;
	}

	if (Monster->StateComp->IsDeadMode())
	{
		BehaviorComp->SetWaitMode();
	}

	if (MonsterPawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : MonsterPawn is nullptr"), *FString(__FUNCTION__));

		return;
	}

	UCMonsterStateComponent* MonsterStateComp = Cast<UCMonsterStateComponent>(MonsterPawn->GetComponentByClass(UCMonsterStateComponent::StaticClass()));

	if (MonsterStateComp == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : MonsterStateComp is nullptr"), *FString(__FUNCTION__));

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

	// Set ApproachMode
	if (Distance <= AIC->GetSightRadius() && Distance >= StopApproachDistance)
	{
		if (!BehaviorComp->IsAttackMode())
		{
			BehaviorComp->SetApproachMode();

			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("%s : Target Distance: %.2f"), *FString(__FUNCTION__), Distance);
	UE_LOG(LogTemp, Warning, TEXT("%s : SightRadius: %.2f, StopApproachDistance: %.2f"), *FString(__FUNCTION__), AIC->GetSightRadius(), StopApproachDistance);

	// Set AttackMode
	if (Distance < StopApproachDistance)
	{
		MonsterStateComp->SetActionMode();
		BehaviorComp->SetAttackMode();

		return;
	}
}