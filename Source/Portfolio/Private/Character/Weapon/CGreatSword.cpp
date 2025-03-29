#include "CGreatSword.h"
#include "CPlayerCharacter.h"
#include "CMontagesComponent.h"
#include "CStateComponent.h"
#include "Kismet/GameplayStatics.h"

ACGreatSword::ACGreatSword()
{
}

void ACGreatSword::BeginPlay()
{
	Super::BeginPlay();

	LoadData();

	if (!OwnerWeaponCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : OwnerWeaponCharacter is nullptr"), *FString(__FUNCTION__));

		return;
	}

	Player = Cast<ACPlayerCharacter>(GetWeaponOwner());

	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Player is nullptr"), *FString(__FUNCTION__));

		return;
	}

	PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!PC)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : PlayerController is nullptr"), *FString(__FUNCTION__));

		return;
	}
}

void ACGreatSword::LoadData()
{
	Super::LoadData();

	LoadWeaponData(TEXT("Greatsword of the Royal"), EWeaponType::GreatSword);
}

void ACGreatSword::Attack()
{
	Super::Attack();

	if (PC->IsInputKeyDown(EKeys::LeftShift) && PC->IsInputKeyDown(EKeys::LeftMouseButton))
	{
		Player->MontagesComp->PlayAttack(TEXT("MouseLeft_SAttack"), Player->StateComp->GetEWeaponType());
	}
	else if (PC->IsInputKeyDown(EKeys::LeftMouseButton))
	{
		Player->MontagesComp->PlayAttack(TEXT("MouseLeft_Attack"), Player->StateComp->GetEWeaponType());
	}
	else if (PC->IsInputKeyDown(EKeys::RightMouseButton))
	{
		Player->MontagesComp->PlayAttack(TEXT("MouseRight_Attack"), Player->StateComp->GetEWeaponType());
	}
}

FName ACGreatSword::GetName()
{
	Super::GetName();

	return WeaponName;
}
 
EWeaponType ACGreatSword::GetWeaponType()
{
	Super::GetWeaponType();

	return WeaponType;
}

float ACGreatSword::GetDamage()
{
	Super::GetDamage();

	return WeaponDamage;
}

USkeletalMesh* ACGreatSword::GetMesh()
{
	Super::GetMesh();

	return WeaponMesh;
}

