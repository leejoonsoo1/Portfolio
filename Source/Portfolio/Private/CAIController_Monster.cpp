#include "CAIController_Monster.h"
#include "CBehaviorComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "CMonster_Rathalos.h"

ACAIController_Monster::ACAIController_Monster()
{
	PrimaryActorTick.bCanEverTick = true;

	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	BehaviorComp = CreateDefaultSubobject<UCBehaviorComponent>(TEXT("BehaviorComp"));
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
	
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	Sight->SightRadius = 1500.f;
	Sight->LoseSightRadius = 1800.f;
	Sight->PeripheralVisionAngleDegrees = 90.f;
	Sight->SetMaxAge(1.f);

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;

	// Perception Config
	PerceptionComp->ConfigureSense(*Sight);
	PerceptionComp->SetDominantSense(UAISense_Sight::StaticClass());
	PerceptionComp->OnPerceptionUpdated.AddDynamic(this, &ACAIController_Monster::OnPerceptionUpdated);

	TeamID = 1;
	bDrawRange = true;
	AdjustHeight = 64;
	BehaviorRange = 150;
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
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("AI Possessing Pawn!"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("AI Pawn is NULL!"));
	}
}

void ACAIController_Monster::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	if (!BlackboardComp) return;

	AActor* TargetActor = nullptr;

	for (AActor* Actor : UpdatedActors)
	{
		if (Actor && Actor->ActorHasTag("Player"))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Hello, Unreal!"));

			TargetActor = Actor;
			break;
		}
	}
		if (TargetActor)
		{
			BlackboardComp->SetValueAsObject("OtherActorKey", TargetActor);
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