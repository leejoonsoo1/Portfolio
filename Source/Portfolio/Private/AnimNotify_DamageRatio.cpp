#include "AnimNotify_DamageRatio.h"
#include "CPlayerCharacter.h"
#include "CAttachment.h"

FString UAnimNotify_DamageRatio::GetNotifyName_Implementation() const
{
	return "SetDamageRatio";
}

void UAnimNotify_DamageRatio::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Player is nullptr"), *FString(__FUNCTION__));

		return;
	}

	UCAttachment* AttachmentComp = Player->AttachmentComp;
	if (!AttachmentComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s, Attachment is nullptr"), *FString(__FUNCTION__));

		return;
	}

	AttachmentComp->SetDamageRatio(DamageRatio);
}