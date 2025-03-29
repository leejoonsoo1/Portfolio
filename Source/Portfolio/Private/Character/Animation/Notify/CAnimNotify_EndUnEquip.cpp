#include "CAnimNotify_EndUnEquip.h"
#include "CPlayerCharacter.h"

FString UCAnimNotify_EndUnEquip::GetNotifyName_Implementation() const
{
	return "UnEquip";
}

void UCAnimNotify_EndUnEquip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Player is nullptr"), *FString(__FUNCTION__));

		return;
	}

	Player->EndUnEquipping();
}