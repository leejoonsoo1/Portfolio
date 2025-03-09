#include "CWeapon.h"
#include "Engine/DataTable.h"

// Sets default values
ACWeapon::ACWeapon()
{

}

void ACWeapon::Attack()
{
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


// Called when the game starts or when spawned
void ACWeapon::BeginPlay()
{
	Super::BeginPlay();

	UDataTable* DT = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/Weapon"));

	if (DT)
	{
		WeaponDataTable = DT;
	}
}