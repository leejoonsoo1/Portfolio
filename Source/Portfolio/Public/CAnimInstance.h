// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Type.h"
#include "CAnimInstance.generated.h"

UCLASS()
class PORTFOLIO_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeBeginPlay() override;

private:
	// UFUNCTION()
	// void OnActionTypeChanged(EActionType InPrevType, EActionType InNewType);

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Player")
	float Speed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Player")
	float Angle;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	EWeaponType WeaponType;
};
