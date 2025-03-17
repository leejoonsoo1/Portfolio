#include "CMonsterStateComponent.h"

UCMonsterStateComponent::UCMonsterStateComponent()
{
	MonsterState = EMonsterStateType::Ground;
}

void UCMonsterStateComponent::BeginPlay()
{
	Super::BeginPlay();
}

//void UCMonsterStateComponent::SetGroundMode()
//{
//	ChangeStateType(EMonsterStateType::Ground);
//}
//
//void UCMonsterStateComponent::SetFlyMode()
//{
//	ChangeStateType(EMonsterStateType::Fly);
//}
//
//void UCMonsterStateComponent::SetCalmMode()
//{
//	ChangeStateType(EMonsterStateType::Calm);
//}
//
//void UCMonsterStateComponent::SetAlertMode()
//{
//	ChangeStateType(EMonsterStateType::Alert);
//}

void UCMonsterStateComponent::SetTiredMode()
{
	ChangeStateType(EMonsterStateType::Tired);
}

void UCMonsterStateComponent::EnragedMode()
{
	ChangeStateType(EMonsterStateType::Enraged);
}

void UCMonsterStateComponent::StunnedMode()
{
	ChangeStateType(EMonsterStateType::Stunned);
}

void UCMonsterStateComponent::SetKnockdownMode()
{
	ChangeStateType(EMonsterStateType::Knockdown);
}

void UCMonsterStateComponent::SetDeadMode()
{
	ChangeStateType(EMonsterStateType::Dead);
}

void UCMonsterStateComponent::ChangeStateType(EMonsterStateType InNewType)
{
	EMonsterStateType PrevType = MonsterState;
	MonsterState = InNewType;

	OnStateChanged.Broadcast(PrevType, MonsterState);
}