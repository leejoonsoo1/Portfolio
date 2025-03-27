#include "CAnimNotifyState_MonsterFly.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "GameFramework\Character.h"

FString UCAnimNotifyState_MonsterFly::GetNotifyName_Implementation() const
{
	return "Fly";
}

void UCAnimNotifyState_MonsterFly::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ACharacter* Monster = Cast<ACharacter>(MeshComp->GetOwner());

	if (!Monster)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCAnimNotifyState_MonsterFly::NotifyBegin : Monster is nullptr"));

		return;
	}

	UCharacterMovementComponent* MovementComp = Monster->GetCharacterMovement();

	if (!MovementComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCAnimNotifyState_MonsterFly::NotifyBegin : MovementComp is nullptr"));

		return;
	}

	MovementComp->SetMovementMode(EMovementMode::MOVE_Flying);
}

void UCAnimNotifyState_MonsterFly::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	ACharacter* Monster = Cast<ACharacter>(MeshComp->GetOwner());

	if (!Monster)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCAnimNotifyState_MonsterFly::NotifyEnd : Monster is nullptr"));

		return;
	}

	UCharacterMovementComponent* MovementComp = Monster->GetCharacterMovement();

	if (!MovementComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCAnimNotifyState_MonsterFly::NotifyEnd : MovementComp is nullptr"));

		return;
	}

	MovementComp->SetMovementMode(EMovementMode::MOVE_Walking);
}