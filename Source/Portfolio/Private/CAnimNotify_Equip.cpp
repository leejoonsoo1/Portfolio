#include "CAnimNotify_Equip.h"
#include "CPlayerCharacter.h"

FString UCAnimNotify_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void UCAnimNotify_Equip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());

	if (!Player) return;

	Player->EndEquipping();
}