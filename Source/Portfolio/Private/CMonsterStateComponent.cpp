#include "CMonsterStateComponent.h"

UCMonsterStateComponent::UCMonsterStateComponent()
{
	MonsterState = EMonsterStateType::Ground;
}

void UCMonsterStateComponent::BeginPlay()
{
	Super::BeginPlay();
}

// EMonsterEmotionStateType
void UCMonsterStateComponent::SetCalmMode()
{
	ChangeEmotionType(EMonsterEmotionStateType::Calm);
}

// EMonsterEmotionStateType
void UCMonsterStateComponent::SetAlertMode()
{
	ChangeEmotionType(EMonsterEmotionStateType::Alert);
}

// EMonsterEmotionStateType
void UCMonsterStateComponent::SetTiredMode()
{
	ChangeEmotionType(EMonsterEmotionStateType::Tired);
}

// EMonsterEmotionStateType
void UCMonsterStateComponent::EnragedMode()
{
	ChangeEmotionType(EMonsterEmotionStateType::Enraged);
}

// EMonsterEmotionStateType
void UCMonsterStateComponent::ChangeEmotionType(EMonsterEmotionStateType InNewType)
{
	EMonsterEmotionStateType PrevType = MonsterEmotion;
	MonsterEmotion = InNewType;

	OnEmotionStateChanged.Broadcast(PrevType, MonsterEmotion);
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