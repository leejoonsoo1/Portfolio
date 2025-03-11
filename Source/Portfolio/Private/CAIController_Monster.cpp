#include "CAIController_Monster.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "CMonster_Rathalos.h"

ACAIController_Monster::ACAIController_Monster()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("UBlackboard"));
	
}

void ACAIController_Monster::BeginPlay()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void ACAIController_Monster::OnPossess(APawn* InPawn)
{
}

void ACAIController_Monster::OnUnPossess()
{
}

void ACAIController_Monster::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
}

void ACAIController_Monster::RemovePlayerKey()
{
}
