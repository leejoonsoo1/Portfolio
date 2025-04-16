#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CActor_Fireball.generated.h"

class USphereComponent;
class UParticleSystemComponent;
class UProjectileMovementComponent;

UCLASS()
class PORTFOLIO_API ACActor_Fireball : public AActor
{
	GENERATED_BODY()
	
public:	
	ACActor_Fireball();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	UPROPERTY(EditAnywhere, Category = "Components")
	USphereComponent* CollisionComp;

	UPROPERTY(EditAnywhere, Category = "Movement")
	UProjectileMovementComponent* ProjectileMovement;

private:
	UPROPERTY(EditAnywhere, Category = "Fireball", meta = (AllowPrivateAccess = "true"))
	float FireballDamage = 15.0f;
};