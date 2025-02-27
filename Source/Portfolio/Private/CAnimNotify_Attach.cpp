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

	UCAttachment* StateComp = Player->FindComponentByClass<UCAttachment>();
	if (!StateComp) return;

	StateComp->ComponentAttachTo(Player->GetMesh(), "Holster");
}