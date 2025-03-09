#pragma once

#include "CoreMinimal.h"
#include "CWeapon.h"
#include "CGreatSword.generated.h"

class ACPlayerCharacter;

UCLASS()
class PORTFOLIO_API ACGreatSword : public ACWeapon
{
	GENERATED_BODY()
	
public:
	ACGreatSword();

protected:
	virtual void BeginPlay() override;
	void LoadWeaponData();

public:
	virtual void Attack() override;
	virtual EWeaponType GetWeaponType() override;
	virtual float GetDamage() override;
	virtual USkeletalMesh* GetMesh() override;

private:
	EWeaponType WeaponType;
	float Damage;
	USkeletalMesh* Mesh;

private:
	ACPlayerCharacter* Player;
	APlayerController* PC;
};