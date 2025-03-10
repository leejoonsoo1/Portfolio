#include "CWeapon.h"
#include "Engine/DataTable.h"

// Sets default values
ACWeapon::ACWeapon()
{

}

void ACWeapon::Attack()
{
}

FName ACWeapon::GetName()
{
	return FName();
}

EWeaponType ACWeapon::GetWeaponType()
{
	return EWeaponType();
}

float ACWeapon::GetDamage()
{
	return 0.0f;
}

USkeletalMesh* ACWeapon::GetMesh()
{
	return nullptr;
}

void ACWeapon::SetWeaponOwner(ACharacter* InOwnerCharacter)
{
	OwnerWeaponCharacter = InOwnerCharacter;
}

ACharacter* ACWeapon::GetWeaponOwner()
{
	return OwnerWeaponCharacter;
}

void ACWeapon::LoadWeaponData(FName InWeaponName, EWeaponType InType)
{
	if (WeaponDataTable)
	{
		// 데이터 테이블의 모든 행을 가져옴
		TArray<FName> RowNames = WeaponDataTable->GetRowNames();

		for (const FName& RowName : RowNames)
		{
			// 각 Row를 순회하면서 데이터 가져오기
			FWeaponData* WeaponData = WeaponDataTable->FindRow<FWeaponData>(RowName, TEXT(""));

			if (WeaponData->WeaponType == EWeaponType::GreatSword && WeaponData->WeaponName == TEXT("Greatsword of the Royal"))
			{
				WeaponName = WeaponData->WeaponName;
				WeaponType = WeaponData->WeaponType;
				WeaponDamage = WeaponData->Damage;
				WeaponMesh = DuplicateObject<USkeletalMesh>(WeaponData->Mesh, this);

				return;
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("WeaponData Table Table is not set!"));
	}
}


// Called when the game starts or when spawned
void ACWeapon::BeginPlay()
{
	Super::BeginPlay();

	UDataTable* DT = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/Weapon"));

	if (!DT)
	{
		UE_LOG(LogTemp, Error, TEXT("Weapon Table can not found! (/Game/DataTable/Weapon)"));

		return;
	}

	WeaponDataTable = DT;
}

void ACWeapon::LoadData()
{
}
