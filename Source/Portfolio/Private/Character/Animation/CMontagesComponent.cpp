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
	if (!GetRow(BasicRows, Row, InRowName, InWeaponType)) return;

	CustomPlayAnimMontage(Row.AnimMontage, Row.PlayRate, Row.StartSection);
}

void UCMontagesComponent::PlayEquipping(FName InRowName, EWeaponType InWeaponType)
{
	FBasicMontageData Row;
	if (!GetRow(BasicRows, Row, InRowName, InWeaponType)) return;
	
	CustomPlayAnimMontage(Row.AnimMontage, Row.PlayRate, Row.StartSection);
}

void UCMontagesComponent::PlayUnEquipping(FName InRowName, EWeaponType InWeaponType)
{
	FBasicMontageData Row;
	if (!GetRow(BasicRows, Row, InRowName, InWeaponType)) return;

	CustomPlayAnimMontage(Row.AnimMontage, Row.PlayRate, Row.StartSection);
}

void UCMontagesComponent::PlayAttack(FName InRowName, EWeaponType InWeaponType)
{
	FBasicMontageData Row;
	
	if (!GetRow(BasicRows, Row, InRowName, InWeaponType))
	{
		FString DebugMessage = FString::Printf(TEXT("%s 를 가져오지 못하였습니다!"), &InRowName.ToString());

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DebugMessage);
	}
	
	CustomPlayAnimMontage(Row.AnimMontage, Row.PlayRate, Row.StartSection);
}

void UCMontagesComponent::PlayHitted()
{

}

void UCMontagesComponent::PlayGimmicked()
{
}

template <typename T>
bool UCMontagesComponent::GetRow(TArray<T*> InRows, T& InRow, FName InRowName, EWeaponType InWeaponType)
{
	for (T* Row : InRows)
	{
		if (Row->Name == InRowName && Row->WeaponType == InWeaponType)
		{
			InRow = *Row;

			return true;
		}
	}

	return false;
}

void UCMontagesComponent::CustomPlayAnimMontage(UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName)
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter) return;

	OwnerCharacter->PlayAnimMontage(AnimMontage, InPlayRate, StartSectionName);
}