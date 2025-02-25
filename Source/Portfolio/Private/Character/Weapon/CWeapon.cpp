#include "CWeapon.h"
#include "Engine/DataTable.h"

// Sets default values
ACWeapon::ACWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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