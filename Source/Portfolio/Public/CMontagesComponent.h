// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CStateComponent.h"
#include "CMontagesComponent.generated.h"

USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	EStateType Type;
	 
	UPROPERTY(EditAnywhere)
	UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
	FName StartSection;

	UPROPERTY(EditAnywhere)
	bool bCanMove;	
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PORTFOLIO_API UCMontagesComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UCMontagesComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void PlayEvade();
	void PlayHitted();

private:
	void PlayAnimMontage(EStateType InType);

private:
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
	UDataTable* DataTable;

private:
	FMontageData* Datas[(int32)EStateType::Max];
};