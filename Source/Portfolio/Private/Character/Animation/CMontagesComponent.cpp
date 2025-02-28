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

	BasicMontageTable->GetAllRows<FBasicMontageData>("", BasicRows);
	BattleMontageTable->GetAllRows<FBattleMontageData>("", BattleRows);
}

void UCMontagesComponent::PlayEvade(FName InRowName, EWeaponType InWeaponType)
{
	FBasicMontageData Row;
	GetRow(BasicRows, Row, InRowName, InWeaponType);

	CustomPlayAnimMontage(Row.AnimMontage, Row.PlayRate, Row.StartSection);
}

void UCMontagesComponent::PlayEquipping(FName InRowNmae, EWeaponType InWeaponType)
{
	FBasicMontageData Row;
	GetRow(BasicRows, Row, InRowNmae, InWeaponType);

	CustomPlayAnimMontage(Row.AnimMontage, Row.PlayRate, Row.StartSection);
}

void UCMontagesComponent::PlayUnEquipping(FName InRowNmae, EWeaponType InWeaponType)
{
	FBasicMontageData Row;
	GetRow(BasicRows, Row, InRowNmae, InWeaponType);

	CustomPlayAnimMontage(Row.AnimMontage, Row.PlayRate, Row.StartSection);
}

void UCMontagesComponent::PlayHitted()
{

}

void UCMontagesComponent::PlayGimmicked()
{
}

template <typename T>
void UCMontagesComponent::GetRow(TArray<T*> InRows, T& InRow, FName InRowName, EWeaponType InWeaponType)
{
	for (T* Row : InRows)
	{
		if (Row->Name == InRowName && Row->WeaponType == InWeaponType)
		{
			InRow = *Row;
		}
	}
}

void UCMontagesComponent::CustomPlayAnimMontage(UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName)
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter) return;

	OwnerCharacter->PlayAnimMontage(AnimMontage, InPlayRate, StartSectionName);
}

// UAnimMontage* UCMontagesComponent::GetMontage(FName InRowName, EStateType Type)
//{
//	//if (Type == EStateType::UnEquip)
//	//{
//	//	return GetBasicMontage(InRowName);
//	//}
//	//else if (Type == EStateType::Equip)
//	//{
//	//	return GetBattleMontage(InRowName);
//	//}
//
//	//return nullptr;
//}

// UAnimMontage* UCMontagesComponent::GetBasicMontage(FName InMontageName)
//{
//	UAnimMontage* FoundMontage = *BasicMontageMap.Find(InMontageName);
//
//	return FoundMontage;
//}
//
// UAnimMontage* UCMontagesComponent::GetBattleMontage(FName InMontageName)
//{
//	UAnimMontage* FoundMontage = *BasicMontageMap.Find(InMontageName);
//
//	return FoundMontage;
//}
//
//
//
//void UCMontagesComponent::LoadBasicAnimMontages()
//{
//	if (!BasicMontageTable)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("BasicMontageTable is not set"));
//		return;
//	}
//
//	//const FString ContextString(TEXT("Name"));
//	////TArray<FBasicMontageData*> BasicRows;
//	//BasicMontageTable->GetAllRows<FBasicMontageData>(ContextString, BasicRows);
//
//	//for (FBasicMontageData* Row : Rows)
//	//{
//	//	if (Row && Row->AnimMontage)
//	//	{
//	//		BasicMontageMap.Add(*Row->Name, Row->AnimMontage);
//	//		UE_LOG(LogTemp, Log, TEXT("[Basic] Loaded Montage : %s -> %s"), *Row->Name, *Row->AnimMontage->GetName());
//	//	}
//	//}
//}
//
//void UCMontagesComponent::LoadBattleAnimMontages()
//{
//	if (!BattleMontageTable)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("BasicMontageTable is not Set"));
//		return;
//	}
//
//	//const FString ContextString(TEXT("Name"));
//	//TArray<FBattleMontageData*> BattleMontageRows;
//	//BattleMontageTable->GetAllRows<FBattleMontageData>(ContextString, BattleMontageRows);
//
//	//for (FBattleMontageData* Row : BattleMontageRows)
//	//{
//	//	if (Row && Row->AnimMontage)
//	//	{
//	//		BattleMontageMap.Add(*Row->Name, Row->AnimMontage);
//	//		UE_LOG(LogTemp, Log, TEXT("[Battle] Loaded Montage : %s -> %s"), *Row->Name, *Row->AnimMontage->GetName());
//	//	}
//	//}
//}
//
