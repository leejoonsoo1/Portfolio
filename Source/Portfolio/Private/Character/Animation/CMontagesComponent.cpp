#include "CMontagesComponent.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"

// Sets default values
UCMontagesComponent::UCMontagesComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
}

// Called when the game starts or when spawned
void UCMontagesComponent::BeginPlay()
{
	Super::BeginPlay();

	LoadAnimMontages();
}

void UCMontagesComponent::PlayEquipping()
{
	PlayAnimMontage(EStateType::Equip);
}

void UCMontagesComponent::PlayUnEquipping()
{
	PlayAnimMontage(EStateType::UnEquip);
}

void UCMontagesComponent::PlayEvade()
{
	PlayAnimMontage(EStateType::Evade);
}

void UCMontagesComponent::PlayHitted()
{
	PlayAnimMontage(EStateType::Hitted);
}

void UCMontagesComponent::PlayGimmicked()
{
}

void UCMontagesComponent::StateChanged(EStateType InPrevType, EStateType InNewType)
{
	UpdateMontage();
}

void UCMontagesComponent::WeaponChanged(EWeaponType InPrevType, EWeaponType InNewType)
{
	UpdateMontage();
}

void UCMontagesComponent::LoadAnimMontages()
{
	if (!BasicMontageTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("BasicMontageTable is not set"));
		return;
	}

	if (!BattleMontageTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("BasicMontageTable is not Set"));
		return;
	}

	const FString

	TArray<FBasicMontageData*> BasicMontageRows;
	TArray<FBattleMontageData*> BattleMontageRows;

	BasicMontageRows->GetAllRows<"Name",

	for (FBasicMontageData* Row : BasicMontageRows)
	{

	}
}

void UCMontagesComponent::UpdateMontage()
{
	return;

}

void UCMontagesComponent::PlayAnimMontage(EStateType InType)
{
	return;


}