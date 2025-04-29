#include "CAnimNotifyState_WeaponCollision.h"
#include "CPlayerCharacter.h"
#include "CAttachment.h"

FString UCAnimNotifyState_WeaponCollision::GetNotifyName_Implementation() const
{
	return "Player_WeaponCollision";
}

void UCAnimNotifyState_WeaponCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : "), *FString(__FUNCTION__));

		return;
	}

	USkeletalMeshComponent* Mesh = Player->AttachmentComp->GetMesh();
	if (!MeshComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : MeshComp is nullptr"), *FString(__FUNCTION__));

		return;
	}

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void UCAnimNotifyState_WeaponCollision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Player is nullptr"), *FString(__FUNCTION__));

		return;
	}

	USkeletalMeshComponent* Mesh = Player->AttachmentComp->GetMesh();
	if (!MeshComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : MeshComp is nullptr"), *FString(__FUNCTION__));

		return;
	}

	Player->AttachmentComp->ClearDamagedActors();
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}