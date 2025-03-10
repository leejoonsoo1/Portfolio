#include "CMonster.h"

ACMonster::ACMonster()
{

}

void ACMonster::BeginPlay()
{
	Super::BeginPlay();

	UDataTable* DT = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/DT_Monster"));

	if (!DT)
	{
		UE_LOG(LogTemp, Error, TEXT("Monster Table can not found! (/Game/DataTable/DT_Monster)"));
	}
	
	MonsterDataTable = DT;
}

void ACMonster::LoadData()
{
}

void ACMonster::LoadMonsterData(FName InMonsterName)
{
	if (MonsterDataTable)
	{
		TArray<FName> RowNames = MonsterDataTable->GetRowNames();

		for (const FName& RowName : RowNames)
		{
			FMonsterData* MonsterData = MonsterDataTable->FindRow<FMonsterData>(RowName, TEXT(""));

			if (MonsterData->Name == InMonsterName)
			{
				MonsterName = MonsterData->Name;
				MonsterDescription = MonsterData->Description;
				MonsterHealth = MonsterData->Health;
				MonsterDamage = MonsterData->Damage;
				MonsterMesh = DuplicateObject<USkeletalMesh>(MonsterData->Mesh, this);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Monster Table Table is not set!"));
	}
}

FName ACMonster::GetName()
{
	return FName();
}

float ACMonster::GetHealth()
{
	return 0.0f;
}

float ACMonster::GetDamage()
{
	return 0.0f;
}

USkeletalMesh* ACMonster::GetMesh()
{
	return nullptr;
}