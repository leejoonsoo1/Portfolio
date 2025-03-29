#include "CAnimNotifyState_CanEvadeTiming.h"
#include "CPlayerCharacter.h"

FString UCAnimNotifyState_CanEvadeTiming::GetNotifyName_Implementation() const
{
	return "CanEvadeTiming";
}

void UCAnimNotifyState_CanEvadeTiming::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	
	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Player is nullptr"), *FString(__FUNCTION__));

		return;
	}
}

void UCAnimNotifyState_CanEvadeTiming::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());

	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Player is nullptr"), *FString(__FUNCTION__));

		return;
	}

	APlayerController* PC = Cast<APlayerController>(Player->GetController());

	if (!PC)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Player Controller is nullptr"), *FString(__FUNCTION__));

		return;
	}

	if (PC->IsInputKeyDown(EKeys::SpaceBar) && PC->IsInputKeyDown(EKeys::D))
	{
		if (!AnimMontage_RightEvade)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s : AnimMontage_RightEvade is null"), *FString(__FUNCTION__));

			return;
		}

		Player->PlayAnimMontage(AnimMontage_RightEvade, PlayRate, StartSectionName);
	}
	else if (PC->IsInputKeyDown(EKeys::SpaceBar) && PC->IsInputKeyDown(EKeys::A))
	{
		if (!AnimMontage_LeftEvade)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s : AnimMontage_LeftEvade is null"), *FString(__FUNCTION__));

			return;
		}

		Player->PlayAnimMontage(AnimMontage_LeftEvade, PlayRate, StartSectionName);
	}
	else if (PC->IsInputKeyDown(EKeys::SpaceBar) && PC->IsInputKeyDown(EKeys::S))
	{
		if (!AnimMontage_BackEvade)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s : AnimMontage_BackEvade is null"), *FString(__FUNCTION__));

			return;
		}

		Player->PlayAnimMontage(AnimMontage_BackEvade, PlayRate, StartSectionName);
	}
}

void UCAnimNotifyState_CanEvadeTiming::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
