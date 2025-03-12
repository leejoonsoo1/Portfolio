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

bool UCBehaviorComponent::IsWaitMode()
{
	return GetType() == EBehaviorType::Wait;
}

bool UCBehaviorComponent::IsApproachMode()
{
	return GetType() == EBehaviorType::Approach;
}

bool UCBehaviorComponent::IsActionMode()
{
	return GetType() == EBehaviorType::Action;
}

bool UCBehaviorComponent::IsPatrolMode()
{
	return GetType() == EBehaviorType::Patrol;
}

bool UCBehaviorComponent::IsStucnMode()
{
	return GetType() == EBehaviorType::Stun;
}

bool UCBehaviorComponent::IsRunAwayMode()
{
	return GetType() == EBehaviorType::RunAway;
}

void UCBehaviorComponent::SetWaitMode()
{
	ChangeType(EBehaviorType::Wait);
}

void UCBehaviorComponent::SetApproachMode()
{
	ChangeType(EBehaviorType::Approach);
}

void UCBehaviorComponent::SetActionMode()
{
	ChangeType(EBehaviorType::Action);
}

void UCBehaviorComponent::SetPatrolMode()
{
	ChangeType(EBehaviorType::Patrol);
}

void UCBehaviorComponent::SetStunMode()
{
	ChangeType(EBehaviorType::Stun);
}

void UCBehaviorComponent::SetRunAwayMode()
{
	ChangeType(EBehaviorType::RunAway);
}

AActor* UCBehaviorComponent::GetTargetValue()
{
	return Cast<AActor>(BlackboardComp->GetValueAsObject(OtherActorKeyName));
}

FVector UCBehaviorComponent::GetLocationValue()
{
	return BlackboardComp->GetValueAsVector(LocationKeyName);
}
