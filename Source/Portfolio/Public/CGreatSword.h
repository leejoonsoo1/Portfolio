#pragma once

#include "CoreMinimal.h"
#include "CWeapon.h"
#include "CGreatSword.generated.h"

/*	
*	2025 부모로 멤버 변수를 옮김.
*/
//class ACPlayerCharacter;

UCLASS()
class PORTFOLIO_API ACGreatSword : public ACWeapon
{
	GENERATED_BODY()
	
public:
	ACGreatSword();

protected:
	virtual void BeginPlay() override;
	virtual void LoadData() override;

public:
	virtual void Attack() override;
	virtual FName GetName() override;
	virtual float GetDamage() override;
	virtual EWeaponType GetWeaponType() override;
	virtual USkeletalMesh* GetMesh() override;

//	// Greatsword 고유 속성.
//private:
//	EWeaponType WeaponType;
//	float Damage;
//	USkeletalMesh* Mesh;
//
//	// 
//private:
//	ACPlayerCharacter* Player;
//	APlayerController* PC;
};