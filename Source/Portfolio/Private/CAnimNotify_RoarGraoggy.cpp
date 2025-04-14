#include "CAnimNotify_RoarGraoggy.h"
#include "CMonster.h"
#include "CPlayerCharacter.h"
#include "CMontagesComponent.h"

FString UCAnimNotify_RoarGraoggy::GetNotifyName_Implementation() const
{
	return "Roar_Groggy";
}

void UCAnimNotify_RoarGraoggy::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	APawn* Pawn = Cast<APawn>(MeshComp->GetOwner());
	if (!Pawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Pawn is nullptr"), *FString(__FUNCTION__));

		return;
	}

	ACMonster* Monster = Cast<ACMonster>(Pawn);
	if (!Monster)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Monster is nullptr"), *FString(__FUNCTION__));

		return;
	}

	UWorld* World = Monster->GetWorld();
	if (!World) return;

	FVector Start	= Monster->GetActorLocation() + FVector(0, 0, 0);
	FVector Forward = Monster->GetActorForwardVector();
	FVector End = Start + Forward * TraceDistance;

	TArray<FHitResult> HitResults;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Monster);

	bool bHit = World->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(TraceRadius), Params);

	if (bHit)
	{
		FRadialDamageEvent RadialEvent;
		RadialEvent.DamageTypeClass		= UDamageType::StaticClass();
		RadialEvent.Origin				= Monster->GetActorLocation();
		RadialEvent.Params.BaseDamage	= 0.f;
		RadialEvent.Params.InnerRadius	= 1500.f;
		RadialEvent.Params.OuterRadius	= 1500.f;

		for (const FHitResult& Hit : HitResults)
		{
			AActor* HitActor			= Hit.GetActor();
			ACPlayerCharacter* Player	= Cast<ACPlayerCharacter>(HitActor);

			if (Player)
			{
				Player->StateComp->SetGroggyMode();
				Player->MontagesComp->PlayGroggy("Groggy", EWeaponType::Unarmed);
			}
		}
	}
}