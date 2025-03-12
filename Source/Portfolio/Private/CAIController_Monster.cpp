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
	Sight->SightRadius = 800.f;
	Sight->LoseSightRadius = 1200.f;
	Sight->PeripheralVisionAngleDegrees = 90.f;
	Sight->SetMaxAge(1.f);

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;

	TeamID = 1;
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

}

void ACAIController_Monster::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
}

void ACAIController_Monster::RemovePlayerKey()
{
}

void ACAIController_Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
