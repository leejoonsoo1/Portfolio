#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Type.h"
#include "Kismet/GameplayStatics.h"
#include "CAttachment.generated.h"

class USkeletalMeshComponent;
class ACharacter;
class ACWeapon;
class USoundBase;
class ACActor_DamageFont;

//UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
UCLASS(DefaultToInstanced, BlueprintType, config = Engine)
class PORTFOLIO_API UCAttachment : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	UCAttachment();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void ComponentAttachTo(USkeletalMeshComponent* OwnerMesh = nullptr, FName SocketName = "Holster");

	void SpawnWeapon();
	void SetDamage(float InDamage);
	void Attack();
	void SwitchWeaponType(EWeaponType NewType);
	
	void ClearDamagedActors();

	void SetDamageRatio(float InDagameRatio);
	FORCEINLINE float GetDamageRatio() const { return DamageRatio; }

public:
	UFUNCTION(BlueprintCallable)
	void OnMeshOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintPure)
	USkeletalMeshComponent* GetMesh() const { return Mesh; }
	ACWeapon* GetCurrentWeapon() const { return CurrentWeapon; }

private:
	UPROPERTY(EditAnywhere, Category = "Comp")
	USkeletalMeshComponent* Mesh;

	ACharacter* OwnerCharacter;

private:
	UPROPERTY()
	ACWeapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ACWeapon> WeaponClass;
	TSet<AActor*> DamagedActors;

private:
	UPROPERTY(EditAnywhere, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	float VolumeMultiplier;

	UPROPERTY(EditAnywhere, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	float PitchMultiplier;

private:
	float Damage;
	float DamageRatio;
	EWeaponType WeaponType;
	TSubclassOf<ACActor_DamageFont> DamageFontClass;
};