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
		UE_LOG(LogTemp, Warning, TEXT("%s : Player is nullptr"), *FString(__FUNCTION__));

		return;
	}

	Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
}

void UCAnimNotifyState_DisableMovement::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());

	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Player is nullptr"), *FString(__FUNCTION__));

		return;
	}

	Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}