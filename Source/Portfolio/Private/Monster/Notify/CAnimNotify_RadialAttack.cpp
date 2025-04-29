#include "CAnimNotify_RadialAttack.h"
#include "CPlayerCharacter.h"
#include "CMontagesComponent.h"
#include "CMonster.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/DamageEvents.h"

FString UCAnimNotify_RadialAttack::GetNotifyName_Implementation() const
{
	return "MonsterRadialAttack";
}

void UCAnimNotify_RadialAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

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
	FVector End		= Start + Forward * TraceDistance;

	TArray<FHitResult> HitResults;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Monster);

	bool bHit = World->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(TraceRadius), Params);

	DrawDebugSphere(World, Start, TraceRadius, 5, FColor::Green, false, 1.f);

	if (bHit)
	{
		FRadialDamageEvent RadialEvent;
		RadialEvent.DamageTypeClass		= UDamageType::StaticClass();
		RadialEvent.Origin				= Monster->GetActorLocation();
		RadialEvent.Params.BaseDamage	= Damage;
		RadialEvent.Params.InnerRadius	= 400.f;
		RadialEvent.Params.OuterRadius	= 800.f;

		for (const FHitResult& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();
			ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(HitActor);

			if (Player)
			{
				// KnockBack Direction 계산
				FVector ToTarget = Player->GetActorLocation() - Monster->GetActorLocation();
				ToTarget.Z = 0.f;
				ToTarget.Normalize();

				// 방향 비교
				FVector PlayerForward = Player->GetActorForwardVector();
				PlayerForward.Z = 0.f;
				PlayerForward.Normalize();

				float Dot = FVector::DotProduct(PlayerForward, ToTarget);

				FName HittedAnimName;

				if (Dot > 0.f)
				{
					HittedAnimName = "Hitted_Forward";
				}
				else
				{
					HittedAnimName = "Hitted_Backward";
				}

				Player->StateComp->SetHittedMode();
				Player->MontagesComp->PlayHitted(HittedAnimName, EWeaponType::Unarmed);
				Player->TakeDamage(Damage, RadialEvent, Monster->GetController(), Monster);

				FVector KnockbackVelocity = ToTarget * 2000.f + FVector(0.f, 0.f, 300.f);
				Player->LaunchCharacter(KnockbackVelocity, true, true);
			}
		}
	}
}