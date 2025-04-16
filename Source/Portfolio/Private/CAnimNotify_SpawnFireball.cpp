// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotify_SpawnFireball.h"

FString UCAnimNotify_SpawnFireball::GetNotifyName_Implementation() const
{
	return "SpawnFireball";
}

void UCAnimNotify_SpawnFireball::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Owner is nullptr"), *FString(__FUNCTION__));

		return;
	}

	if (!FireballClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : FIreballClass is nullptr"), *FString(__FUNCTION__));

		return;
	}

	FVector SpawnLocation	= MeshComp->GetSocketLocation(SocketName);
	FRotator SpawnRotation	= MeshComp->GetSocketRotation(SocketName);

	FActorSpawnParameters Params;
	Params.Instigator	= Owner->GetInstigator();
	Params.Owner		= Owner;

	MeshComp->GetWorld()->SpawnActor<AActor>(FireballClass, SpawnLocation, SpawnRotation, Params);
}