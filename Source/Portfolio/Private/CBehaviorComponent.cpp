#include "CBehaviorComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UCBehaviorComponent::UCBehaviorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCBehaviorComponent::SetBlackboardComponent(UBlackboardComponent* InBlackboardComp)
{
	BlackboardComp = InBlackboardComp;
}

EBehaviorType UCBehaviorComponent::GetType()
{
	return (EBehaviorType)(BlackboardComp->GetValueAsEnum(BehaviorKeyName));
}

void UCBehaviorComponent::ChangeType(EBehaviorType InNewType)
{
	EBehaviorType Prev = GetType();
	BlackboardComp->SetValueAsEnum(BehaviorKeyName, (uint8)InNewType);
}

bool UCBehaviorComponent::IsIdleMode()
{
	return GetType() == EBehaviorType::Idle;
}

bool UCBehaviorComponent::IsWaitMode()
{
	return GetType() == EBehaviorType::Wait;
}

bool UCBehaviorComponent::IsApproachMode()
{
	return GetType() == EBehaviorType::Approach;
}

bool UCBehaviorComponent::IsAttackMode()
{
	return GetType() == EBehaviorType::Attack;
}

bool UCBehaviorComponent::IsPatrolMode()
{
	return GetType() == EBehaviorType::Patrol;
}

bool UCBehaviorComponent::IsFlinchMode()
{
	return GetType() == EBehaviorType::Flinch;
}

bool UCBehaviorComponent::IsRunAwayMode()
{
	return GetType() == EBehaviorType::RunAway;
}

bool UCBehaviorComponent::IsSearchMode()
{
	return GetType() == EBehaviorType::Search;
}

bool UCBehaviorComponent::IsRoarMode()
{
	return GetType() == EBehaviorType::Roar;
}

bool UCBehaviorComponent::IsLandMode()
{
	return GetType() == EBehaviorType::Land;
}

bool UCBehaviorComponent::IsTakeoffMode()
{
	return GetType() == EBehaviorType::Takeoff;
}

void UCBehaviorComponent::SetIdleMode()
{
	ChangeType(EBehaviorType::Idle);
}

void UCBehaviorComponent::SetWaitMode()
{
	ChangeType(EBehaviorType::Wait);
}

void UCBehaviorComponent::SetApproachMode()
{
	ChangeType(EBehaviorType::Approach);
}

void UCBehaviorComponent::SetAttackMode()
{
	ChangeType(EBehaviorType::Attack);
}

void UCBehaviorComponent::SetSpecialMode()
{
	ChangeType(EBehaviorType::Special);
}

void UCBehaviorComponent::SetPatrolMode()
{
	ChangeType(EBehaviorType::Patrol);
}

void UCBehaviorComponent::SetFlinchMode()
{
	ChangeType(EBehaviorType::Flinch);
}

void UCBehaviorComponent::SetRunAwayMode()
{
	ChangeType(EBehaviorType::RunAway);
}

void UCBehaviorComponent::SetSearchMode()
{
	ChangeType(EBehaviorType::Search);
}

void UCBehaviorComponent::SetRoarMode()
{
	ChangeType(EBehaviorType::Roar);
}

void UCBehaviorComponent::SetLandMode()
{
	ChangeType(EBehaviorType::Land);
}

void UCBehaviorComponent::SetTakeoffMode()
{
	ChangeType(EBehaviorType::Takeoff);
}

AActor* UCBehaviorComponent::GetTargetValue()
{
	return Cast<AActor>(BlackboardComp->GetValueAsObject(OtherActorKeyName));
}

FVector UCBehaviorComponent::GetLocationValue()
{
	return BlackboardComp->GetValueAsVector(LocationKeyName);
}
