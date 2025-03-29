#include "CAnimNotify_Takle.h"
#include "CPlayerCharacter.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/DamageEvents.h"

FString UCAnimNotify_Takle::GetNotifyName_Implementation() const
{
	return "TakleCollision";
}

void UCAnimNotify_Takle::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	APawn* Pawn = Cast<APawn>(MeshComp->GetOwner());
	if (!Pawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Pawn is nullptr"), *FString(__FUNCTION__));

		return;
	}

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(Pawn);
	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Player is nullptr"), *FString(__FUNCTION__));

		return;
	}

	UWorld* World = Player->GetWorld();
	if (!World) return;

	FVector Start	= Player->GetActorLocation() + FVector(0, 0, 0);
	FVector Forward = Player->GetActorForwardVector();
	FVector End = Start + Forward * TraceDistance;

	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params;

	bool bHit = World->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(TraceRadius), Params);

	if (bHit)
	{
		FDamageEvent DamageEvent;

		for (const FHitResult& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();
			if (HitActor && HitActor != Player)
			{
				HitActor->TakeDamage(Damage, DamageEvent, Player->GetController(), Player);
			}
		}
	}
}