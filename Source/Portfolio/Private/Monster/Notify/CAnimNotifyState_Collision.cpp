#include "CAnimNotifyState_Collision.h"
#include "CMonster.h"

FString UCAnimNotifyState_Collision::GetNotifyName_Implementation() const
{
	return "Monster_Collision";
}

void UCAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ACMonster* Monster = Cast<ACMonster>(MeshComp->GetOwner());

	if (HeadCollision == true)
	{
		Monster->OnAttackCollisionHead();
	}

	if (TailCollision == true)
	{
		Monster->OnAttackCollisionTail();
	}

	if (FeetCollision == true)
	{
		Monster->OnAttackCollisionFeet();
	}
}

void UCAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	ACMonster* Monster = Cast<ACMonster>(MeshComp->GetOwner());

	if (HeadCollision == true)
	{
		Monster->OffAttackCollisionHead();
	}

	if (TailCollision == true)
	{
		Monster->OffAttackCollisionTail();
	}

	if (FeetCollision == true)
	{
		Monster->OffAttackCollisionFeet();
	}
}