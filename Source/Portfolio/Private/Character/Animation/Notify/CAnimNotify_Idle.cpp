#include "CAnimNotify_Idle.h"
#include "CPlayerCharacter.h"

FString UCAnimNotify_Idle::GetNotifyName_Implementation() const
{
	return "PlayerSetIdle";
}

void UCAnimNotify_Idle::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());

	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Player is nullptr"), *FString(__FUNCTION__));

		return;
	}

	Player->StateComp->SetIdleMode();
}