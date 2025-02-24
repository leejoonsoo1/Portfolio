#include "CAnimNotify_Evade.h"
#include "CPlayerCharacter.h"

FString UCAnimNotify_Evade::GetNotifyName_Implementation() const
{
	return "Evade";
}

void UCAnimNotify_Evade::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	
	if (!Player) return;

 	Player->End_Evade();
}
