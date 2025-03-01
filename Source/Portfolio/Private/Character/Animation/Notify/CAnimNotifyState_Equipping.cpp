#include "CAnimNotifyState_Equipping.h"
#include "CPlayerCharacter.h"

/*
*	2025. 03. 02
*	현재 노티파이 비긴은 하는 일이 없음.
*/
FString UCAnimNotifyState_Equipping::GetNotifyName_Implementation() const
{
	return "Equipping";
}

void UCAnimNotifyState_Equipping::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{

}

void UCAnimNotifyState_Equipping::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());

	if (!Player) return;

	Player->EndEquipping();
}