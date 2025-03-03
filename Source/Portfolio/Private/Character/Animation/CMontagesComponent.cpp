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

void UCMontagesComponent::PlayEquipping(FName InRowName, EWeaponType InWeaponType)
{
	FBasicMontageData Row;
	GetRow(BasicRows, Row, InRowName, InWeaponType);

	CustomPlayAnimMontage(Row.AnimMontage, Row.PlayRate, Row.StartSection);
}

void UCMontagesComponent::PlayUnEquipping(FName InRowName, EWeaponType InWeaponType)
{
	FBasicMontageData Row;
	GetRow(BasicRows, Row, InRowName, InWeaponType);

	CustomPlayAnimMontage(Row.AnimMontage, Row.PlayRate, Row.StartSection);
}

void UCMontagesComponent::PlayAttack(FName InRowName, EWeaponType InWeaponType)
{
	FBasicMontageData Row;
	GetRow(BasicRows, Row, InRowName, InWeaponType);

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