#include "CAnimNotify_Equip.h"
#include "CPlayerCharacter.h"

FString UCAnimNotify_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void UCAnimNotify_Equip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());

	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Player is nullptr"), *FString(__FUNCTION__));

		return;
	}

	Player->EndEquipping();
}