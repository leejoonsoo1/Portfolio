#include "CAnimNotify_PlayerNextMotion.h"
#include "CPlayerCharacter.h"

FString UCAnimNotify_PlayerNextMotion::GetNotifyName_Implementation() const
{
	return "Player_NextMontage";
}

void UCAnimNotify_PlayerNextMotion::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Player is nullptr"), *FString(__FUNCTION__));

		return;
	}

	Player->PlayAnimMontage(Montage, PlayRate, StartSectionName);
}