#include "CAnimNotifyState_NXTAOne.h"
#include "CPlayerCharacter.h"

FString UCAnimNotifyState_NXTAOne::GetNotifyName_Implementation() const
{
	return "AttackOneNextCombo";
}

void UCAnimNotifyState_NXTAOne::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
}

void UCAnimNotifyState_NXTAOne::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());

	if (!Player) return;
	if (!AnimMontage) return;

	APlayerController* PC = Cast<APlayerController>(Player->GetController());

	if (!PC) return;

	if (PC->IsInputKeyDown(EKeys::LeftMouseButton))
	{
		Player->PlayAnimMontage(AnimMontage, PlayRate, StartSectionName);
	}
}

void UCAnimNotifyState_NXTAOne::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
