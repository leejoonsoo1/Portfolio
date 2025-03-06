#include "CAnimNotifyState_NXTAOne.h"
#include "CPlayerCharacter.h"

FString UCAnimNotifyState_NXTAOne::GetNotifyName_Implementation() const
{
	return "AttackOneNextCombo";
}

void UCAnimNotifyState_NXTAOne::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());

	if (!Player) return;
}

// Tick으로 bCharge가 false 이면 바로 공격 동작.
void UCAnimNotifyState_NXTAOne::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());

	if (!Player) return;
	
	APlayerController* PC = Cast<APlayerController>(Player->GetController());

	if (ConditionKey != EKeys::Invalid)
	{
		if (!PC) return;

		if (PC->WasInputKeyJustPressed(EKeys::W) && PC->WasInputKeyJustPressed(EKeys::LeftMouseButton))
		{
			Player->PlayAnimMontage(AnimMontage_NextAttack, PlayRate, StartSectionName);

			return;
		}
	}

	if (!Player->GetCharge())
	{
		if (!AnimMontage_NextAttack) return;

		Player->PlayAnimMontage(AnimMontage_NextAttack, PlayRate, StartSectionName);
	}

}

// Notify가 끝날 때 까지 bCharge가 True이면 다음 차징 동작 출력.
void UCAnimNotifyState_NXTAOne::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());

	if (!Player) return;
	if (!AnimMontage_NextCharge) return;

	if (Player->GetCharge())
	{
		Player->PlayAnimMontage(AnimMontage_NextCharge, PlayRate, StartSectionName);
	}
}
