#include "CAnimNotifyState_Invincible.h"
#include "CPlayerCharacter.h"
#include "CStateComponent.h"

FString UCAnimNotifyState_Invincible::GetNotifyName_Implementation() const
{
	return "Invinciblie";
}

void UCAnimNotifyState_Invincible::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Player is nullptr"), *FString(__FUNCTION__));
		
		return;
	}

	Player->StateComp->SetInvincibleMode();
}

void UCAnimNotifyState_Invincible::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s, : Player is nullptr"), *FString(__FUNCTION__));

		return;
	}

	Player->StateComp->SetVincibleMode();
}