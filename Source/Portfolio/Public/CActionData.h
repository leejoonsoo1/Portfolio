// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CActionData.generated.h"

USTRUCT(BlueprintType)
struct FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	UAnimontage* Montage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
	FName StartSection;

	UPROPERTY(EditAnywhere)
	bool bCanMove = true;

	UPROPERTY(EditAnywhere)
	bool bUseControlRotation = true;
};

USTRUCT(BlueprintType)

struct FActionData : public FEquipmentData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	float Damage = 5.f;

	UPROPERTY(EditAnywhere)
	float HitStop;

	UPROPERTY(EditAnywhere)
	FTransform EffectTransform;
};


UCLASS()
class PORTFOLIO_API UCActionData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	void BeginPlay(ACharacter* InOwnerCharacter, UActionObject** OutActionObject);

};
