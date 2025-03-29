#include "CAnimNotify_SetMonsterIdleState.h"
#include "CMonster.h"

FString UCAnimNotify_SetMonsterIdleState::GetNotifyName_Implementation() const
{
	return "SetMonsterIdleState";
}

void UCAnimNotify_SetMonsterIdleState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACMonster* Monster = Cast<ACMonster>(MeshComp->GetOwner());

	if (!Monster)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : Monster is nullptr"), *FString(__FUNCTION__));

		return;
	}

	Monster->StateComp->SetIdleMode();
}