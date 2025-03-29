#include "CAnimNotify_MonsterTransitionMontage.h"
#include "CMonster.h"

FString UCAnimNotify_MonsterTransitionMontage::GetNotifyName_Implementation() const
{
	return "MonsterTransitionMontage";
}
void UCAnimNotify_MonsterTransitionMontage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACMonster* Monster = Cast<ACMonster>(MeshComp->GetOwner());
	if (!Monster)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Monster is nullptr"), *FString(__FUNCTION__));

		return;
	}

	Monster->PlayAnimMontage(Montage, PlayRate, StartSectionName);
}