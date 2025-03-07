#pragma once

#include "CoreMinimal.h"
#include "CWeapon.h"
#include "CGreatSword.generated.h"

UCLASS()
class PORTFOLIO_API ACGreatSword : public ACWeapon
{
	GENERATED_BODY()
	
public:
	ACGreatSword();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Attack() override;
	virtual void GetWeaponType();
};