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

	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCAnimNotifyState_NXTAOne::NotifyBegin : Player is nullptr"));

		return;
	}
}

// Tick으로 bCharge가 false 이면 바로 공격 동작.
void UCAnimNotifyState_NXTAOne::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());

	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCAnimNotifyState_NXTAOne::NotifyTick : Player is nullptr"));

		return;
	}
	
	APlayerController* PC = Cast<APlayerController>(Player->GetController());

	if (ConditionKey != EKeys::Invalid)
	{
		if (!PC)
		{
			UE_LOG(LogTemp, Warning, TEXT("UCAnimNotifyState_NXTAOne::NotifyTick : PlayerController is nullptr"));

			return;
		}

		if (!AnimMontage_NextAttackStance)
		{
			UE_LOG(LogTemp, Warning, TEXT("UCAnimNotifyState_NXTAOne::NotifyTick : AnimMontage_NextAttackStance is nullptr"));

			return;
		}

		bool bKeyW = PC->IsInputKeyDown(EKeys::W);
		bool bKeyLeftMouseButton = PC->IsInputKeyDown(EKeys::LeftMouseButton);

		if (bKeyW && bKeyLeftMouseButton)
		{
			Player->PlayAnimMontage(AnimMontage_NextAttackStance, PlayRate, StartSectionName);

			return;
		}
	}

	if (!Player->GetCharge())
	{
		if (!AnimMontage_NextAttack)
		{
			UE_LOG(LogTemp, Warning, TEXT("UCAnimNotifyState_NXTAOne::NotifyTick : AnimMontage_NextAttack is nullptr"));

			return;
		}

		Player->PlayAnimMontage(AnimMontage_NextAttack, PlayRate, StartSectionName);

		return;
	}
}

// Notify가 끝날 때 까지 bCharge가 True이면 다음 차징 동작 출력.
void UCAnimNotifyState_NXTAOne::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());

	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCAnimNotifyState_NXTAOne::NotifyEnd : Player is nullptr"));

		return;
	}

	if (!AnimMontage_NextCharge)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCAnimNotifyState_NXTAOne::NotifyEnd : AnimMontage_NextCharge is null"));

		return;
	}

	if (Player->GetCharge())
	{
		Player->PlayAnimMontage(AnimMontage_NextCharge, PlayRate, StartSectionName);
	}
}
