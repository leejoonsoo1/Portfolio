#include "CAnimNotify_EmotionEnraged.h"
#include "CMonster.h"

FString UCAnimNotify_EmotionEnraged::GetNotifyName_Implementation() const
{
	return "Roar";
}

void UCAnimNotify_EmotionEnraged::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACMonster* Monster = Cast<ACMonster>(MeshComp->GetOwner());
	if (!Monster)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Monster is nullptr"), *FString(__FUNCTION__));

		return;
	}

	Monster->EmotionComp->SetEnragedMode();
}