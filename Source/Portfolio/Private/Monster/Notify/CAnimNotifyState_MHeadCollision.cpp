#include "CAnimNotifyState_MHeadCollision.h"
#include "CMonster.h"

FString UCAnimNotifyState_MHeadCollision::GetNotifyName_Implementation() const
{
	return "Monster_HeadCollision";
}

void UCAnimNotifyState_MHeadCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	APawn* Pawn = Cast<APawn>(MeshComp->GetOwner());
	if (!Pawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Pawn is nullptr"), *FString(__FUNCTION__));

		return;
	}

	ACMonster* Monster = Cast<ACMonster>(Pawn);
	if (!Monster)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Monster is nullptr"), *FString(__FUNCTION__));

		return;
	}

	Monster->OnAttackCollisionHead();
}

void UCAnimNotifyState_MHeadCollision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	APawn* Pawn = Cast<APawn>(MeshComp->GetOwner());
	if (!Pawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Pawn is nullptr"), *FString(__FUNCTION__));

		return;
	}

	ACMonster* Monster = Cast<ACMonster>(Pawn);
	if (!Monster)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Monster is nullptr"), *FString(__FUNCTION__));

		return;
	}

	Monster->OffAttackCollisionHead();
}