#include "CBTService_UpdateMonsterState.h"
#include "CMonsterStateComponent.h"
#include "CStateComponent.h"
#include "CAIController_Monster.h"
#include "CBehaviorComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CMonster.h"
#include "GameFramework\CharacterMovementComponent.h"

UCBTService_UpdateMonsterState::UCBTService_UpdateMonsterState()
{
	NodeName = "RootService_Monster";
	Interval = 0.1f;
	RandomDeviation = 0.0f;
	bCallTickOnSearchStart = true;
}

void UCBTService_UpdateMonsterState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController_Monster* AIC = Cast<ACAIController_Monster>(OwnerComp.GetAIOwner());
	
	if (AIC == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : AIC is nullptr"), *FString(__FUNCTION__));

		return;
	}

	UCBehaviorComponent* BehaviorComp = Cast<UCBehaviorComponent>(AIC->GetComponentByClass(UCBehaviorComponent::StaticClass()));
	
	if (BehaviorComp == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : BehaviorComp is nullptr"), *FString(__FUNCTION__));

		return;
	}

	APawn* MonsterPawn = AIC->GetPawn();
	ACMonster* Monster = Cast<ACMonster>(MonsterPawn);

	if (!Monster)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Monster is nullptr"), *FString(__FUNCTION__));

		return;
	}

	if (Monster->StateComp->IsDeadMode())
	{
		return;
	}

	if (MonsterPawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : MonsterPawn is nullptr"), *FString(__FUNCTION__));

		return;
	}

	UCMonsterStateComponent* MonsterStateComp = Cast<UCMonsterStateComponent>(MonsterPawn->GetComponentByClass(UCMonsterStateComponent::StaticClass()));

	if (MonsterStateComp == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : MonsterStateComp is nullptr"), *FString(__FUNCTION__));

		return;
	}

	AActor* TargetActor = BehaviorComp->GetTargetValue();
	if (!TargetActor)
	{
		BehaviorComp->SetPatrolMode();
		
		return;
	}

	if (!bHasSensedPlayer && TargetActor)
	{
		FirstSensedTime		= GetWorld()->GetTimeSeconds();
		LastRoarTime		= FirstSensedTime;
		bHasSensedPlayer	= true;
	}

	float CurrentTime				= GetWorld()->GetTimeSeconds();
	float ElapsedSinceFirstSense	= CurrentTime - FirstSensedTime;
	float ElapsedSinceLastRoar		= CurrentTime - LastRoarTime;

	if (ElapsedSinceFirstSense <= 3.f)
	{
		BehaviorComp->SetWaitMode();
		UpdateFacingOnly(Monster, TargetActor, DeltaSeconds);

		return;
	}
	else if (((ElapsedSinceFirstSense > 3.f && !bRoaredOnce) || ElapsedSinceLastRoar >= 180.f) && (BehaviorComp->IsWaitMode() && !BehaviorComp->IsRoarMode()))
	{
		EnterRoarMode(CurrentTime, BehaviorComp);

		return;
	}

	Monster->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	Monster->GetCharacterMovement()->bOrientRotationToMovement = true;

	APawn* ControlledPawn = AIC->GetPawn();
	if (!ControlledPawn || !TargetActor) return;

	// 타겟까지의 벡터 (방향 벡터)
	FVector ToTargetVector = TargetActor->GetActorLocation() - ControlledPawn->GetActorLocation();

	// 거리 계산 (벡터 길이)
	float Distance = MonsterPawn->GetDistanceTo(TargetActor);

	// 방향 벡터 (단위 벡터)
	FVector ToTarget	= ToTargetVector.GetSafeNormal();
	FRotator LookAtRot	= ToTarget.Rotation();

	// 몬스터의 방향과 타겟 방향의 Yaw 차이.
	float YawDiff = FMath::FindDeltaAngleDegrees(ControlledPawn->GetActorRotation().Yaw, LookAtRot.Yaw);

	// 방향 판별
	ETargetDirectionType Direction;

	if (FMath::Abs(YawDiff) <= 45.f)
	{
		Direction = ETargetDirectionType::Front;
	}
	else if (YawDiff > 45.f && YawDiff <= 135.f)
	{
		Direction = ETargetDirectionType::Right;
	}
	else if (YawDiff <= -45.f && YawDiff >= -135.f)
	{
		Direction = ETargetDirectionType::Left;
	}
	else
	{
		Direction = ETargetDirectionType::Back;
	}
	
	UCStateComponent* OtherStateComp = Cast<UCStateComponent>(TargetActor->GetComponentByClass(UCStateComponent::StaticClass()));
	UBlackboardComponent* BlackBoardComp = AIC->GetBlackboardComp();

	if (!BlackBoardComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : BlackBoardComp is nullptr"), *FString(__FUNCTION__));
	}

	// 블랙 보드에 값 저장.
	BlackBoardComp->SetValueAsEnum("TargetDirectionKey", (uint8)Direction);
	BlackBoardComp->SetValueAsFloat("TargetDistanceKey", Distance);

	if (OtherStateComp && OtherStateComp->IsDeadMode())
	{
		BehaviorComp->SetWaitMode();

		return;
	}

	// Set AttackMode
	if (Distance < StopApproachDistance && (!BehaviorComp->IsAttackMode() && !BehaviorComp->IsRoarMode()))
	{
		MonsterStateComp->SetActionMode();
		BehaviorComp->SetAttackMode();

		return;
	}

	// Set ApproachMode
	if (Distance <= AIC->GetSightRadius() && (!BehaviorComp->IsAttackMode() && !BehaviorComp->IsRoarMode()))
	{
		if (Distance > StopApproachDistance)
		{
			BehaviorComp->SetApproachMode();
			
			return;
		}
		else if (Distance <= StopApproachDistance)
		{
			UpdateFacingOnly(Monster, TargetActor, DeltaSeconds);

			return;
		}
	}
}

void UCBTService_UpdateMonsterState::UpdateFacingOnly(ACMonster* InMonster, AActor* InTargetActor, float DeltaSeconds)
{
	if (!InMonster || !InTargetActor) return;

	InMonster->GetCharacterMovement()->DisableMovement();
	InMonster->GetCharacterMovement()->bOrientRotationToMovement = false;

	FVector ToTarget = InTargetActor->GetActorLocation() - InMonster->GetActorLocation();
	FRotator LookAtRotation = ToTarget.GetSafeNormal().Rotation();
	FRotator CurrentRot = InMonster->GetActorRotation();

	float NewYaw = FMath::FInterpTo(CurrentRot.Yaw, LookAtRotation.Yaw, DeltaSeconds, 1.f);

	FRotator NewRot(0.f, NewYaw, 0.f);
	InMonster->SetActorRotation(NewRot);

	if (TurnMontage)
	{
		UAnimInstance* AnimInstance = InMonster->GetMesh()->GetAnimInstance();
		if (AnimInstance && !AnimInstance->Montage_IsPlaying(TurnMontage))
		{
			AnimInstance->Montage_Play(TurnMontage);
		}
	}
}

void UCBTService_UpdateMonsterState::EnterRoarMode(float CurrentTime, UCBehaviorComponent* BehaviorComp)
{
	if (!BehaviorComp) return;

	LastRoarTime = CurrentTime;
	bRoaredOnce = true;

	BehaviorComp->SetRoarMode();
}