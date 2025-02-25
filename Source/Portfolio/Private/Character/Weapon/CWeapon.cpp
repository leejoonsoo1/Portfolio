#include "CWeapon.h"
#include "Engine/DataTable.h"

// Sets default values
ACWeapon::ACWeapon()
{

}

void ACWeapon::Attack()
{
}

// Called when the game starts or when spawned
void ACWeapon::BeginPlay()
{
	Super::BeginPlay();

	InitializeWeaponFromDataTable("");
}

void ACWeapon::InitializeWeaponFromDataTable(FName RowName)
{
	if (!WeaponDataTable)
	{
		return;
	}

	FWeaponData* Data = WeaponDataTable->FindRow<FWeaponData>(RowName, TEXT("Lookup FWeaponData"));

	if (Data)
	{
		WeaponData = *Data;
	}
}