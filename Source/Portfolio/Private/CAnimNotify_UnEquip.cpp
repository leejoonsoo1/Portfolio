#include "CAnimNotify_UnEquip.h"
#include "CPlayerCharacter.h"

FString UCAnimNotify_UnEquip::GetNotifyName_Implementation() const
{
	return "UnEquip";
}

void UCAnimNotify_UnEquip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());

	if (!Player) return;

	Player->EndUnEquipping();
}