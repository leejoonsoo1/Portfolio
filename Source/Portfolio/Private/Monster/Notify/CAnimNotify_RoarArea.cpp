#include "CAnimNotify_RoarArea.h"
#include "CMonster.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

FString UCAnimNotify_RoarArea::GetNotifyName_Implementation() const
{
	return "SphereTrace";
}

void UCAnimNotify_RoarArea::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACMonster* Monster = Cast<ACMonster>(MeshComp->GetOwner());

	if (!Monster)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Monster is nullptr"), *FString(__FUNCTION__));

		return;
	}

	UWorld* World = Monster->GetWorld();

	if (!World) return;

	FVector Start	= Monster->GetActorLocation() + FVector(0, 0, 0);
	FVector Forward = Monster->GetActorForwardVector();
	FVector End		= Start + Forward * TraceDistance;

	TArray<FHitResult> HitResults;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Monster);

	bool bHit = World->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(TraceRadius), Params);

	// µð¹ö±×
	DrawDebugSphere(World, Start, TraceRadius, 5, FColor::Green, false, 1.f);
	
	if (bHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();

			if (HitActor)
			{
				UE_LOG(LogTemp, Warning, TEXT("Hit Actor : %s"), *HitActor->GetName());


			}
		}
	}

}