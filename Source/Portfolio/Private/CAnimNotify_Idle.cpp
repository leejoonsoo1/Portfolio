#include "CAnimNotify_Idle.h"
#include "CPlayerCharacter.h"

FString UCAnimNotify_Idle::GetNotifyName_Implementation() const
{
	return "SetIdle";
}

void UCAnimNotify_Idle::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());

	if (!Player) return;

	Player->StateComp->SetIdleMode();
}