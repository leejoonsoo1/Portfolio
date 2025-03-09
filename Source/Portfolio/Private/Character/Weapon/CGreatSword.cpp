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

	LoadWeaponData();

	if (!OwnerWeaponCharacter)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("ACGreatSword::BeginPlay() : Has no Owner!"));

		return;
	}

	Player = Cast<ACPlayerCharacter>(GetWeaponOwner());

	if (!Player->MontagesComp)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("ACGreatSword::BeginPlay() : Has no montagesComp!"));

		return;
	}

	PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!PC)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("ACGreatSword::BeginPlay() : Has no OwnerPawn!"));

		return;
	}
}

void ACGreatSword::LoadWeaponData()
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
				Damage = WeaponData->Damage;
				Mesh = WeaponData->Mesh;
				WeaponType = WeaponData->WeaponType;

				return;
			}
		}
    }
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


// 
EWeaponType ACGreatSword::GetWeaponType()
{
	return WeaponType;
}

float ACGreatSword::GetDamage()
{
	return Damage;
}

USkeletalMesh* ACGreatSword::GetMesh()
{
	return Mesh;
}

