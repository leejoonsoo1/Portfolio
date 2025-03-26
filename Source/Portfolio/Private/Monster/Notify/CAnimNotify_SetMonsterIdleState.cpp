#include "CAnimNotify_SetMonsterIdleState.h"
#include "CMonster.h"

FString UCAnimNotify_SetMonsterIdleState::GetNotifyName_Implementation() const
{
	return "SetMonsterIdleState";
}

void UCAnimNotify_SetMonsterIdleState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACMonster* Monster = Cast<ACMonster>(MeshComp->GetOwner());

	if (!Monster)
	{
		UE_LOG(LogTemp, Error, TEXT("Monster is nullptr"));

		return;
	}

	Monster->StateComp->SetIdleMode();
}