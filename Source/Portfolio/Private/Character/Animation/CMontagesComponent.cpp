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

	LoadBasicAnimMontages();
	LoadBattleAnimMontages();
}

void UCMontagesComponent::PlayEvade(FName InRowName, EStateType InType)
{
	if (InRowName.IsEqual("")) return;

	UAnimMontage* AnimMontage = GetMontage(InRowName, InType);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("UCMontagesComponent::PlayEvade"));

	CustomPlayAnimMontage(AnimMontage);
}

void UCMontagesComponent::PlayEquipping()
{

}

void UCMontagesComponent::PlayUnEquipping()
{

}

void UCMontagesComponent::PlayHitted()
{

}

void UCMontagesComponent::PlayGimmicked()
{
}

 UAnimMontage* UCMontagesComponent::GetMontage(FName InRowName, EStateType Type)
{
	if (Type == EStateType::UnEquip)
	{
		return GetBasicMontage(InRowName);
	}
	else if (Type == EStateType::Equip)
	{
		return GetBattleMontage(InRowName);
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("UCMontagesComponent::GetMontage ptrNull"));

	return nullptr;
}

 UAnimMontage* UCMontagesComponent::GetBasicMontage(FName InMontageName)
{
	UAnimMontage* FoundMontage = *BasicMontageMap.Find(InMontageName);

	return FoundMontage;
}

 UAnimMontage* UCMontagesComponent::GetBattleMontage(FName InMontageName)
{
	UAnimMontage* FoundMontage = *BasicMontageMap.Find(InMontageName);

	return FoundMontage;
}

void UCMontagesComponent::LoadBasicAnimMontages()
{
	if (!BasicMontageTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("BasicMontageTable is not set"));
		return;
	}

	const FString ContextString(TEXT("Name"));
	TArray<FBasicMontageData*> Rows;
	BasicMontageTable->GetAllRows<FBasicMontageData>(ContextString, Rows);

	for (FBasicMontageData* Row : Rows)
	{
		if (Row && Row->AnimMontage)
		{
			BasicMontageMap.Add(*Row->Name, Row->AnimMontage);
			UE_LOG(LogTemp, Log, TEXT("[Basic] Loaded Montage : %s -> %s"), *Row->Name, *Row->AnimMontage->GetName());
		}
	}
}

void UCMontagesComponent::LoadBattleAnimMontages()
{
	if (!BattleMontageTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("BasicMontageTable is not Set"));
		return;
	}

	const FString ContextString(TEXT("Name"));
	TArray<FBattleMontageData*> BattleMontageRows;
	BattleMontageTable->GetAllRows<FBattleMontageData>(ContextString, BattleMontageRows);

	for (FBattleMontageData* Row : BattleMontageRows)
	{
		if (Row && Row->AnimMontage)
		{
			BattleMontageMap.Add(*Row->Name, Row->AnimMontage);
			UE_LOG(LogTemp, Log, TEXT("[Battle] Loaded Montage : %s -> %s"), *Row->Name, *Row->AnimMontage->GetName());
		}

		UAnimMontage* aa = *BattleMontageMap.Find("aa");
	}
}

void UCMontagesComponent::CustomPlayAnimMontage(UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName)
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter) return;

	OwnerCharacter->PlayAnimMontage(AnimMontage, InPlayRate, StartSectionName);

	return;
}