#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "CWeapon.generated.h"

class UAnimMontage;

USTRUCT(BlueprintType)
struct FWeaponData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Weapon")
	FString WeaponName;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float Damage;
};

UCLASS()
class PORTFOLIO_API ACWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACWeapon();

protected:
	virtual void Attack();
	virtual void InitializeWeaponFromDataTable(FName RowName);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	UDataTable* WeaponDataTable;

	FWeaponData WeaponData;
};
