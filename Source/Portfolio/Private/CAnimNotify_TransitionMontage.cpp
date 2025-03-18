#include "CAnimNotify_TransitionMontage.h"
#include "CMonster.h"

FString UCAnimNotify_TransitionMontage::GetNotifyName_Implementation() const
{
	return "TransitionMontage";
}
void UCAnimNotify_TransitionMontage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACMonster* Monster = Cast<ACMonster>(MeshComp->GetOwner());

	if (!Monster)
	{
		UE_LOG(LogTemp, Error, TEXT("Monster is nullptr"));

		return;
	}

	Monster->PlayAnimMontage(Montage, PlayRate, StartSectionName);
}