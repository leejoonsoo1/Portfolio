#include "CAnimNotifyState_Attach.h"
#include "CPlayerCharacter.h"
#include "CAttachment.h"

FString UCAnimNotifyState_Attach::GetNotifyName_Implementation() const
{
    return "Attach";
}

void UCAnimNotifyState_Attach::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Player is nullptr"), *FString(__FUNCTION__));

		return;
	}

	UCAttachment* StateComp = Player->FindComponentByClass<UCAttachment>();
	if (!StateComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : StateComp is nullptr"), *FString(__FUNCTION__));

		return;
	}

	StateComp->ComponentAttachTo(Player->GetMesh(), "R_Weapon_01");

	if (!Player->StateComp->IsGreatSwordMode())
	{
		Player->StateComp->SetGreatSwordMode();
	}
}

void UCAnimNotifyState_Attach::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Player is nullptr"), *FString(__FUNCTION__));

		return;
	}

	UCAttachment* StateComp = Player->FindComponentByClass<UCAttachment>();
	if (!StateComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : StateComp is nullptr"), *FString(__FUNCTION__));

		return;
	}

	StateComp->ComponentAttachTo(Player->GetMesh(), "L_Weapon_01");
}
