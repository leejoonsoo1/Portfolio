#include "CAnimNotify_Attach.h"
#include "CPlayerCharacter.h"
#include "CAttachment.h"

FString UCAnimNotify_Attach::GetNotifyName_Implementation() const
{
	return "Attach";
}

void UCAnimNotify_Attach::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Player is nullptr"), *FString(__FUNCTION__));

		return;
	}

	UCAttachment* Attachment = Player->FindComponentByClass<UCAttachment>();
	if (!Attachment)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Attachment is nullptr"), *FString(__FUNCTION__));

		return;
	}

	Attachment->ComponentAttachTo(Player->GetMesh(), "Holster");
}