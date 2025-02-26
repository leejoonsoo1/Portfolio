#include "CAnimNotifyState_Equipping.h"
#include "CPlayerCharacter.h"

FString UCAnimNotifyState_Equipping::GetNotifyName_Implementation() const
{
	return "Equipping";
}

void UCAnimNotifyState_Equipping::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	
	if (!Player) return;

	Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
}

void UCAnimNotifyState_Equipping::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());

	if (!Player) return;

	Player->EndEquipping();
}