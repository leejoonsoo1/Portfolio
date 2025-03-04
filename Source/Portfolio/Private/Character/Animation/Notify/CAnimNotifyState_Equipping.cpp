#include "CAnimNotifyState_Equipping.h"
#include "CPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

/*
*	2025. 03. 02
*	현재 노티파이 비긴은 하는 일이 없음.
*/
FString UCAnimNotifyState_Equipping::GetNotifyName_Implementation() const
{
	return "Equipping";
}

void UCAnimNotifyState_Equipping::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());

	if (!Player) return;

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(MeshComp->GetWorld(), 0);

    if (PlayerController)
    {
        PlayerController->DisableInput(PlayerController);
    }
}

void UCAnimNotifyState_Equipping::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	
    if (!Player) return;
    
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(MeshComp->GetWorld(), 0);

    if (PlayerController)
    {
        PlayerController->EnableInput(PlayerController);
	    Player->EndEquipping();
    }
}