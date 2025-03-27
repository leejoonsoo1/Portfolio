#include "CAnimNotify_RadialAttack.h"

FString UCAnimNotify_RadialAttack::GetNotifyName_Implementation() const
{
	return FString();
}

void UCAnimNotify_RadialAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
}
