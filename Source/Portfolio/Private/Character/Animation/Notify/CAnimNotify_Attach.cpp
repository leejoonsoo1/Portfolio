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
		UE_LOG(LogTemp, Warning, TEXT("UCAnimNotify_Attach::Notify : Player is nullptr"));

		return;
	}

	UCAttachment* Attachment = Player->FindComponentByClass<UCAttachment>();
	if (!Attachment)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCAnimNotify_Attach::Notify : Attachment is nullptr"));

		return;
	}

	Attachment->ComponentAttachTo(Player->GetMesh(), "Holster");
}