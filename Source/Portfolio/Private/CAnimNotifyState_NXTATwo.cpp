#include "CAnimNotifyState_NXTATwo.h"
#include "CPlayerCharacter.h"

FString UCAnimNotifyState_NXTATwo::GetNotifyName_Implementation() const
{
	return "AttackTwoNextCombo";
}

void UCAnimNotifyState_NXTATwo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
}

void UCAnimNotifyState_NXTATwo::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	
	if (!Player) return;
	if (!AnimMontage) return;

	APlayerController* PC = Cast<APlayerController>(Player->GetController());
	
	if (!PC) return;

	if (ConditionKey != EKeys::Invalid && PC->IsInputKeyDown(ConditionKey)) 
	{
		Player->PlayAnimMontage(AnimMontage, PlayRate, StartSectionName);
	}
}

void UCAnimNotifyState_NXTATwo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}