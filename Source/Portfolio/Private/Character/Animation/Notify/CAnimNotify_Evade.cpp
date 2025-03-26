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
	
	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCAnimNotify_Evade::Notify"));

		return;
	}

 	Player->EndEvade();
}