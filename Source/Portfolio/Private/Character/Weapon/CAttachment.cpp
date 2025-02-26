#include "CAttachment.h"
#include "CAttachment.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

UCAttachment::UCAttachment()
{
	
}

void UCAttachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());

	if (!OwnerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCAttachment : OwnerCharacter is null!"));
	}

	if (!OwnerCharacter->GetMesh())
	{
		UE_LOG(LogTemp, Warning, TEXT("UCAttachment : OwnerCharacter has no mesh"));
	}

	Super::BeginPlay();
}

void UCAttachment::ComponentAttachTo(FName SocketName)
{
	if (!OwnerCharacter || !OwnerCharacter->GetMesh())
	{
		UE_LOG(LogTemp, Error, TEXT("UCAttachment: Failed to attch - OwnerCharacter or Mesh is null!"));

		return;
	}

	if (!Mesh)
	{
		UE_LOG(LogTemp, Error, TEXT("UCAttachment: Failed to attch - Attach Mesh is null!"));

		return;
	}

	Mesh->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), SocketName);
}
