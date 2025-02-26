#include "CAnimNotifyState_UnEquipping.h"
#include "CPlayerCharacter.h"

FString UCAnimNotifyState_UnEquipping::GetNotifyName_Implementation() const
{
	return "UnEquipping";
}

void UCAnimNotifyState_UnEquipping::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());

	if (!Player) return;

	Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
}

void UCAnimNotifyState_UnEquipping::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());

	if (!Player) return;

	Player->EndUnEquipping();
}
