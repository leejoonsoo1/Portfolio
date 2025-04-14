#include "CMonsterEmotionComponent.h"

UCMonsterEmotionComponent::UCMonsterEmotionComponent()
{
	MonsterEmotion = EMonsterEmotionStateType::Calm;
}


void UCMonsterEmotionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCMonsterEmotionComponent::SetCalmMode()
{
	ChangeEmotionType(EMonsterEmotionStateType::Calm);
}

void UCMonsterEmotionComponent::SetAlertMode()
{
	ChangeEmotionType(EMonsterEmotionStateType::Alert);
}

void UCMonsterEmotionComponent::SetTiredMode()
{
	ChangeEmotionType(EMonsterEmotionStateType::Tired);
}

void UCMonsterEmotionComponent::SetEnragedMode()
{
	ChangeEmotionType(EMonsterEmotionStateType::Enraged);
}

void UCMonsterEmotionComponent::ChangeEmotionType(EMonsterEmotionStateType InNewType)
{
	EMonsterEmotionStateType PrevType = MonsterEmotion;
	MonsterEmotion = InNewType;

	OnEmotionStateChanged.Broadcast(PrevType, MonsterEmotion);
}