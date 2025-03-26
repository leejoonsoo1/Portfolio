#include "CMonsterStateComponent.h"

UCMonsterStateComponent::UCMonsterStateComponent()
{
	MonsterState = EMonsterStateType::Ground;
}

void UCMonsterStateComponent::BeginPlay()
{
	Super::BeginPlay();
}

// EMonsterStateType
void UCMonsterStateComponent::SetIdleMode()
{
	ChangeStateType(EMonsterStateType::Idle);
}

// EMonsterStateType
void UCMonsterStateComponent::SetActionMode()
{
	ChangeStateType(EMonsterStateType::Action);
}

// EMonsterStateType
void UCMonsterStateComponent::SetStunnedMode()
{
	ChangeStateType(EMonsterStateType::Stunned);
}

// EMonsterStateType
void UCMonsterStateComponent::SetKnockdownMode()
{
	ChangeStateType(EMonsterStateType::Knockdown);
}

// EMonsterStateType
void UCMonsterStateComponent::SetDeadMode()
{
	ChangeStateType(EMonsterStateType::Dead);
}

// EMonsterStateType
void UCMonsterStateComponent::ChangeStateType(EMonsterStateType InNewType)
{
	EMonsterStateType PrevType = MonsterState;
	MonsterState = InNewType;

	OnStateChanged.Broadcast(PrevType, MonsterState);
}