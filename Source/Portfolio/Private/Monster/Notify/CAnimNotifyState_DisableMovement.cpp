#include "CAnimNotifyState_DisableMovement.h"
#include "CPlayerCharacter.h"

FString UCAnimNotifyState_DisableMovement::GetNotifyName_Implementation() const
{
	return "DisableMovement";
}

void UCAnimNotifyState_DisableMovement::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());

	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCAnimNotifyState_DisableMovement::NotifyBegin : Player is nullptr"));

		return;
	}

	Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
}

void UCAnimNotifyState_DisableMovement::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());

	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCAnimNotifyState_DisableMovement::NotifyEnd : Player is nullptr"));

		return;
	}

	Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}