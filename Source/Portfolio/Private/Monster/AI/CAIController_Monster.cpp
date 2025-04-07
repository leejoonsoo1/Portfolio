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
	Sight->SetMaxAge(0.2f);

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

	if (PossessedMonster && ensure(PossessedMonster->GetBehaviorTree()))
	{
		// 먼저 블랙보드 초기화
		UBlackboardComponent* BlackboardCompRaw = nullptr;
		UseBlackboard(PossessedMonster->GetBehaviorTree()->GetBlackboardAsset(), BlackboardCompRaw);

		// RunBehaviorTree 이후 블랙보드가 유효하므로 그때 BehaviorComp에 전달
		BehaviorComp->SetBlackboardComponent(BlackboardCompRaw);

		RunBehaviorTree(PossessedMonster->GetBehaviorTree());
	}

	SetGenericTeamId(FGenericTeamId(TeamID));
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
		UE_LOG(LogTemp, Warning, TEXT("%s : AI Possessing Pawn!"), *FString(__FUNCTION__));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : AI Pawn is NULL!"), *FString(__FUNCTION__));
	}
}

void ACAIController_Monster::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	if (!BlackboardComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Blackboard component is null!"), *FString(__FUNCTION__));

		return;
	}

	AActor* TargetActor = nullptr;
	FActorPerceptionBlueprintInfo Info;

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
		SensedActor = TargetActor;

		if (CurrentTime - LastRoarTime >= RoarInterval)
		{
			//BlackboardComp->SetValueAsEnum("BehaviorKey", (uint8)EBehaviorType::Roar);
		}

		BlackboardComp->SetValueAsObject("OtherActorKey", TargetActor);
	}
	else
	{
		// 마지막으로 감지된 시간 계산
		if (GetPerceptionComponent()->GetActorsPerception(SensedActor, Info))
		{
			if (!Info.LastSensedStimuli.IsEmpty())
			{
				const float TimeSinceLastSeen = Info.LastSensedStimuli[0].GetAge();

				if (TimeSinceLastSeen >= 0.3f)
				{
					BlackboardComp->ClearValue("OtherActorKey");
					BlackboardComp->ClearValue("TargetDirectionKey");
					BlackboardComp->ClearValue("TargetDistanceKey");

					SensedActor = nullptr;
				}
			}
		}
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