#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Type.h"
#include "CWeapon.generated.h"

class UAnimMontage;
class ACPlayerCharacter;

USTRUCT(BlueprintType)
struct FWeaponData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Weapon")
	FName WeaponName;

	UPROPERTY(EditAnywhere, Category="Weapon")
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	float Damage;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	USkeletalMesh* Mesh;
};

UCLASS()
class PORTFOLIO_API ACWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void LoadData();

public:
	virtual void Attack();
	virtual FName GetName();
	virtual float GetDamage();
	virtual EWeaponType GetWeaponType();
	virtual USkeletalMesh* GetMesh();

	void SetWeaponOwner(ACharacter* InOwnerCharacter);
	ACharacter* GetWeaponOwner();

	void LoadWeaponData(FName InWeaponName, EWeaponType InType);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	UDataTable* WeaponDataTable;

	ACharacter* OwnerWeaponCharacter;

protected:
	// 자식들의 고유 속성을 저장할 변수.
	FName WeaponName;
	EWeaponType WeaponType;
	float WeaponDamage;
	USkeletalMesh* WeaponMesh;

protected:
	// Owner 캐릭터의 속성
	ACPlayerCharacter* Player;
	APlayerController* PC;
};
