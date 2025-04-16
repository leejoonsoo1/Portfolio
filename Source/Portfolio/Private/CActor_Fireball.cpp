#include "CActor_Fireball.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CPlayerCharacter.h"
#include "Engine/DamageEvents.h"

ACActor_Fireball::ACActor_Fireball()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	CollisionComp->InitSphereRadius(20.f);
	CollisionComp->SetCollisionProfileName("BlockAllDynamic");
	CollisionComp->SetNotifyRigidBodyCollision(true);
	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed				= 1500.f;
	ProjectileMovement->MaxSpeed					= 1500.f;
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

		FDamageEvent DamageEvent;
		Player->ApplyDamage(FireballDamage, DamageEvent, GetInstigatorController(), this);

		Destroy();
	}
}