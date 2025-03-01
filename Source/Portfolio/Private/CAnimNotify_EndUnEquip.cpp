#include "CAnimNotify_EndUnEquip.h"
#include "CPlayerCharacter.h"

FString UCAnimNotify_EndUnEquip::GetNotifyName_Implementation() const
{
	return "UnEquip";
}

void UCAnimNotify_EndUnEquip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	
	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	if (!Player) return;

	Player->EndUnEquipping();
}