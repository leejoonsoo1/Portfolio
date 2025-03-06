#include "CAttachment.h"
#include "CAttachment.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

UCAttachment::UCAttachment()
{
	
}

void UCAttachment::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	if (!OwnerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCAttachment : OwnerCharacter is null!"));

		return;
	}

	if (!OwnerCharacter->GetMesh())
	{
		UE_LOG(LogTemp, Warning, TEXT("UCAttachment : OwnerCharacter has no mesh"));

		return;
	}
	
	/*
	*	2025 03 06
	*	무기 충돌 감지를 위한 Collision 셋.
	*/
	if (!Mesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCAttachment : Mesh is null!"));

		return;
	}
	
	Mesh->SetCollisionProfileName(TEXT("Weapon"));
}

void UCAttachment::ComponentAttachTo(USkeletalMeshComponent* OwnerMesh, FName SocketName)
{
	if (!OwnerMesh)
	{
		if (!OwnerCharacter || !OwnerCharacter->GetMesh())
		{
			UE_LOG(LogTemp, Error, TEXT("UCAttachment: Failed to attch - OwnerCharacter or Mesh is null!"));

			return;
		}

		OwnerMesh = OwnerCharacter->GetMesh();
	}

	if (!Mesh)
	{
		UE_LOG(LogTemp, Error, TEXT("UCAttachment: Failed to attch - Attach Mesh is null!"));

		return;
	}

	Mesh->AttachToComponent(OwnerMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), SocketName);
}
