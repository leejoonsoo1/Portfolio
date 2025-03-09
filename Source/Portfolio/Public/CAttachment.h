#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Type.h"
#include "CAttachment.generated.h"

class USkeletalMeshComponent;
class ACharacter;
class ACWeapon;

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
	void Attack();
	void SwitchWeaponType(EWeaponType NewType);

public:
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

private:
	float Damage;
	EWeaponType WeaponType;
};