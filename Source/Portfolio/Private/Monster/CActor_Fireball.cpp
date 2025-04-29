#include "CActor_Fireball.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CPlayerCharacter.h"
#include "Engine/DamageEvents.h"
#include "CMontagesComponent.h"

ACActor_Fireball::ACActor_Fireball()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	CollisionComp->InitSphereRadius(200.f);
	CollisionComp->SetCollisionProfileName("Monster");
	CollisionComp->SetNotifyRigidBodyCollision(true);
	CollisionComp->SetVisibility(false);
	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed				= 4500.f;
	ProjectileMovement->MaxSpeed					= 4500.f;
	ProjectileMovement->bRotationFollowsVelocity	= true;
	ProjectileMovement->bShouldBounce				= false;
	ProjectileMovement->ProjectileGravityScale		= 0.f;
}

void ACActor_Fireball::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionComp->OnComponentHit.AddDynamic(this, &ACActor_Fireball::OnHit);
	SetLifeSpan(5.f);
}

void ACActor_Fireball::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(OtherActor);

		if (Player)
		{
			FDamageEvent DamageEvent;

			FName HittedAnimName;
			FVector FireballForward = GetActorForwardVector();
			FVector HitDirection = (OtherActor->GetActorLocation() - Hit.ImpactPoint).GetSafeNormal();
			float Dot = FVector::DotProduct(FireballForward, HitDirection);

			if (Dot > 0)
			{
				HittedAnimName = "Hitted_Backward"; 
			}
			else
			{
				HittedAnimName = "Hitted_Forward";
			}
			
			Player->MontagesComp->PlayHitted(HittedAnimName, EWeaponType::Unarmed);
			Player->ApplyDamage(FireballDamage, DamageEvent, GetInstigatorController(), this);
		}

		Destroy();
	}
}