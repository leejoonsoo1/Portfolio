#include "CBehaviorComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UCBehaviorComponent::UCBehaviorComponent()
{
	OtherActorKeyName	= "OtherActorKey";
	LocationKeyName		= "LocationKey";
	BehaviorKeyName		= "BehaviorKey";
}

void UCBehaviorComponent::SetBlackboardComponent(UBlackboardComponent* InBlackboardComp)
{
	BlackboardComp = InBlackboardComp;

	UE_LOG(LogTemp, Warning, TEXT("%s : BlackboardComp set"), *FString(__FUNCTION__));	
}

EBehaviorType UCBehaviorComponent::GetType()
{
	if (!BlackboardComp)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : BlackbaordComp is nullptr"), *FString(__FUNCTION__));

		return EBehaviorType::Max;
	}

	return (EBehaviorType)(BlackboardComp->GetValueAsEnum(BehaviorKeyName));
}

void UCBehaviorComponent::ChangeType(EBehaviorType InNewType)
{
	EBehaviorType Prev = GetType();
	
	UE_LOG(LogTemp, Warning, TEXT("%s : Change State!"), *FString(__FUNCTION__));

	if (!BlackboardComp)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : BlackbaordComp is nullptr"), *FString(__FUNCTION__));

		return;
	}

	if (Prev == InNewType)
	{
		// 상태 동일 → 변경 생략
		return;
	}


	UE_LOG(LogTemp, Warning, TEXT("%s : %d -> %d"), *FString(__FUNCTION__), (int32)Prev, (int32)InNewType);

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

void UCBehaviorComponent::SetWaitMode()
{
	UE_LOG(LogTemp, Warning, TEXT("%s : Behavior Component States is Wait Mode"), *FString(__FUNCTION__));

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
	if (!BlackboardComp)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : BlackbaordComp is nullptr"), *FString(__FUNCTION__));

		return nullptr;
	}

	return Cast<AActor>(BlackboardComp->GetValueAsObject(OtherActorKeyName));
}

FVector UCBehaviorComponent::GetLocationValue()
{
	if (!BlackboardComp)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : BlackbaordComp is nullptr"), *FString(__FUNCTION__));

		return FVector(0, 0, 0);
	}

	return BlackboardComp->GetValueAsVector(LocationKeyName);
}