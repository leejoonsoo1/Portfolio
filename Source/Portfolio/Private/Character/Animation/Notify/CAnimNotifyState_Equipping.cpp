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

    if (!Player)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s : Player is nullptr"), *FString(__FUNCTION__));

        return;
    }

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(MeshComp->GetWorld(), 0);

    if (!PlayerController)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s : PlayerController is nullptr"), *FString(__FUNCTION__));

        return;
    }
    
    PlayerController->DisableInput(PlayerController);
}

void UCAnimNotifyState_Equipping::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(MeshComp->GetOwner());
	
    if (!Player)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s : Player is nullptr"), *FString(__FUNCTION__));

        return;
    }
    
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(MeshComp->GetWorld(), 0);

    if (PlayerController)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s : PlayerController is nullptr"), *FString(__FUNCTION__));

        return;
    }

    PlayerController->EnableInput(PlayerController);
    Player->EndEquipping();
}