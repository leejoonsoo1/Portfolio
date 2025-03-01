#include "CAnimNotify_Attach.h"
#include "CPlayerCharacter.h"
#include "CAttachment.h"

FString UCAnimNotify_Attach::GetNotifyName_Implementation() const
{
	return "Attach";
}

void UCAnimNotify_Attach::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	if (!Player) return;

	UCAttachment* Attachment = Player->FindComponentByClass<UCAttachment>();
	if (!Attachment) return;

	Attachment->ComponentAttachTo(Player->GetMesh(), "Holster");
}