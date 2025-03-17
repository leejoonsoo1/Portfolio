#include "CBTTaskNode_Patrol.h"
#include "CAICOntroller_Monster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "NavMesh/RecastNavMesh.h"
#include "CBehaviorComponent.h"

UCBTTaskNode_Patrol::UCBTTaskNode_Patrol()
{
    NodeName = "Patrol";
    bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    ACAIController_Monster* AIC = Cast<ACAIController_Monster>(OwnerComp.GetAIOwner());
    if (!AIC)
    {
        UE_LOG(LogTemp, Error, TEXT("AIC is nullptr"));

        return EBTNodeResult::Failed;
    }

    APawn* ControlledPawn = AIC->GetPawn();
    if (!ControlledPawn)
    {
        UE_LOG(LogTemp, Error, TEXT("ControlledPawn is nullptr"));

        return EBTNodeResult::Failed;
    }

    ACMonster* Monster = Cast<ACMonster>(ControlledPawn);
    if (!Monster)
    {
        UE_LOG(LogTemp, Error, TEXT("Monster is nullptr"));

        return EBTNodeResult::Failed;
    }

    UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());

    if (!NavSys)
    {
        UE_LOG(LogTemp, Error, TEXT("NavSys is nullptr"));

        return EBTNodeResult::Failed;
    }

    FNavLocation RandomPoint;
    float MaxRadius = 2000.f;

    if (NavSys->GetRandomReachablePointInRadius(ControlledPawn->GetActorLocation(), MaxRadius, RandomPoint))
    {
        PatrolTargetLocation = RandomPoint.Location;
        AIC->MoveToLocation(PatrolTargetLocation);
        bIsMoving = true;

        return EBTNodeResult::InProgress;
    }

    return EBTNodeResult::Failed;
}

void UCBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    if (!bIsMoving) return;

    ACAIController_Monster* AIC = Cast<ACAIController_Monster>(OwnerComp.GetAIOwner());
    if (!AIC)
    {
        UE_LOG(LogTemp, Error, TEXT("AIC is nullptr"));

        return;
    }

    APawn* AIPawn = AIC->GetPawn();
    if (!AIPawn)
    {
        UE_LOG(LogTemp, Error, TEXT("AIPawn is nullptr"));

        return;
    }

    float Distance = FVector::Dist(AIPawn->GetActorLocation(), PatrolTargetLocation);
    if (Distance < 100.f)
    {
        AIC->StopMovement();
        bIsMoving = false;

        UCBehaviorComponent* BehaviorComp = Cast<UCBehaviorComponent>(AIC->GetComponentByClass(UCBehaviorComponent::StaticClass()));
        if (BehaviorComp)
        {
            BehaviorComp->SetWaitMode();
        }

        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}