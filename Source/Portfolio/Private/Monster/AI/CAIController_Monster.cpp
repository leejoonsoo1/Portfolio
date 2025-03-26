#include "CAIController_Monster.h"
#include "CBehaviorComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "CMonster_Rathalos.h"

ACAIController_Monster::ACAIController_Monster()
{
	PrimaryActorTick.bCanEverTick = false;

	BlackboardComp	= CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	BehaviorComp	= CreateDefaultSubobject<UCBehaviorComponent>(TEXT("BehaviorComp"));
	PerceptionComp	= CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	Sight->SightRadius = 2500.f;
	Sight->LoseSightRadius = 3000.f;
	Sight->PeripheralVisionAngleDegrees = 360.f;
	Sight->SetMaxAge(0.5f);

	Sight->DetectionByAffiliation.bDetectEnemies	= true;
	Sight->DetectionByAffiliation.bDetectNeutrals	= false;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;

	// Perception Config
	PerceptionComp->ConfigureSense(*Sight);
	PerceptionComp->SetDominantSense(UAISense_Sight::StaticClass());
	PerceptionComp->OnPerceptionUpdated.AddDynamic(this, &ACAIController_Monster::OnPerceptionUpdated);

	TeamID			= 1;
	bDrawRange		= true;
	AdjustHeight	= 64;
	BehaviorRange	= 1500;
}

float ACAIController_Monster::GetSightRadius()
{
	return Sight->SightRadius;
}

void ACAIController_Monster::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedMonster = Cast<ACMonster>(InPawn);

	UBlackboardComponent* BlackboardCompRaw;

	if (!Blackboard)
	{
		BlackboardCompRaw = Blackboard.Get();
	}
	else
	{
		BlackboardCompRaw = BlackboardComp;
	}

	if (PossessedMonster && ensure(PossessedMonster->GetBehaviorTree()))
	{
		UseBlackboard(PossessedMonster->GetBehaviorTree()->GetBlackboardAsset(), BlackboardCompRaw);
		RunBehaviorTree(PossessedMonster->GetBehaviorTree());
	}

	SetGenericTeamId(FGenericTeamId(TeamID));
	BehaviorComp->SetBlackboardComponent(Blackboard);
}

void ACAIController_Monster::OnUnPossess()
{
	Super::OnUnPossess();
}

void ACAIController_Monster::BeginPlay()
{
	Super::BeginPlay();

	APawn* ControlledPawn = GetPawn();

	if (ControlledPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACAIController_Monster::BeginPlay() : AI Possessing Pawn!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ACAIController_Monster::BeginPlay() : AI Pawn is NULL!"));
	}
}

void ACAIController_Monster::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	if (!BlackboardComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACAIController_Monster::OnPerceptionUpdated : Blackboard component is null!"));

		return;
	}

	AActor* TargetActor = nullptr;

	for (AActor* Actor : UpdatedActors)
	{
		if (Actor && Actor->ActorHasTag("Player"))
		{
			TargetActor = Actor;
			break;
		}
	}

	if (TargetActor)
	{
		float CurrentTime = GetWorld()->GetTimeSeconds();

		if (CurrentTime - LastRoarTime >= RoarInterval)
		{
			BlackboardComp->SetValueAsEnum("BehaviorKey", (uint8)EBehaviorType::Roar);
		}

		APawn* ControlledPawn = GetPawn();
		if (!ControlledPawn || !TargetActor) return;

		// 타겟까지의 벡터 (방향 벡터)
		FVector ToTargetVector = TargetActor->GetActorLocation() - ControlledPawn->GetActorLocation();

		// 거리 계산 (벡터 길이)
		float Distance = ToTargetVector.Size();

		// 방향 벡터 (단위 벡터)
		FVector ToTarget	= ToTargetVector.GetSafeNormal();
		FRotator LookAtRot	= ToTarget.Rotation();

		// 몬스터의 방향과 타겟 방향의 Yaw 차이.
		float YawDiff = FMath::FindDeltaAngleDegrees(ControlledPawn->GetActorRotation().Yaw, LookAtRot.Yaw);

		// 디버그 출력
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("YawDiff: %.2f"), YawDiff));

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
		else if (YawDiff < -45.f && YawDiff >= -135.f)
		{
			Direction = ETargetDirectionType::Left;
		}
		else
		{
			Direction = ETargetDirectionType::Back;
		}

		if (Distance > BehaviorRange)
		{
			BlackboardComp->SetValueAsEnum("Approach", (uint8)EBehaviorType::Approach);
		}
		else if (Distance <= BehaviorRange)
		{
			BlackboardComp->SetValueAsEnum("Approach", (uint8)EBehaviorType::Attack);
		}

		// 블랙 보드에 값 저장.
		BlackboardComp->SetValueAsObject("OtherActorKey", TargetActor);
		BlackboardComp->SetValueAsEnum("TargetDirectionKey", (uint8)Direction);
		BlackboardComp->SetValueAsFloat("TargetDistanceKey", Distance);
	}
	else
	{
		BlackboardComp->ClearValue("OtherActorKey");
	}
}

void ACAIController_Monster::RemovePlayerKey()
{
}

void ACAIController_Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Center = PossessedMonster->GetActorLocation();
	Center.Z += AdjustHeight;

	//DrawDebugCircle(GetWorld(), Center, Sight->SightRadius, 64, FColor::Green, false, -1.f, (uint8)0U, 0.f, FVector::RightVector, FVector::ForwardVector);
	//DrawDebugCircle(GetWorld(), Center, BehaviorRange, 64, FColor::Red, false, -1.f, (uint8)0U, 0.f, FVector::RightVector, FVector::ForwardVector);
}