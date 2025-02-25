// Fill out your copyright notice in the Description page of Project Settings.


#include "CEquipment.h"

// Sets default values
ACEquipment::ACEquipment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACEquipment::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

