// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEquipment.generated.h"

class ACharacter;
class UCStateComponent;
class UCAttributeComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentDelegate);

UCLASS()
class PORTFOLIO_API ACEquipment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACEquipment();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetData(FEquipmentData& InData);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
