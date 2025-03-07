#include "CWeapon.h"
#include "Engine/DataTable.h"

// Sets default values
ACWeapon::ACWeapon()
{

}

void ACWeapon::Attack()
{
}

void ACWeapon::GetWeaponType()
{
}

// Called when the game starts or when spawned
void ACWeapon::BeginPlay()
{
	Super::BeginPlay();

	ConstructorHelpers::FObjectFinder<UDataTable> DT(TEXT("/Game/DataTable/Weapon"));

	if (DT.Succeeded())
	{
		WeaponDataTable = DT.Object;
	}
}