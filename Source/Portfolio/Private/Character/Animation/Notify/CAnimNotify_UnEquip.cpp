#include "CAnimNotify_UnEquip.h"
#include "CPlayerCharacter.h"

FString UCAnimNotify_UnEquip::GetNotifyName_Implementation() const
{
	return "UnEquip";
}

void UCAnimNotify_UnEquip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation,EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());

	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCAnimNotify_UnEquip::Notify : Player is nullptr"));

		return;
	}

	Player->EndUnEquipping();
}