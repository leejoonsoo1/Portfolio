#include "CMonster.h"


ACMonster::ACMonster()
{
	StateComp = CreateDefaultSubobject<UCMonsterStateComponent>(TEXT("MonsterStateComp"));
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

	if (StateComp)
	{
		StateComp->OnStateChanged.AddDynamic(this, &ACMonster::HandleStateChanged);
	}
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
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Monster Table Table is not set!"));
	}
}

void ACMonster::HandleStateChanged(EMonsterStateType PrevState, EMonsterStateType NewState)
{
	UE_LOG(LogTemp, Warning, TEXT("Monster State Changed : %d -> %d"), (int32)PrevState, (int32)NewState);

	switch(NewState)
	{
	case EMonsterStateType::Ground:
			UE_LOG(LogTemp, Warning, TEXT("Monster Mode: Ground."));
			break;
		case EMonsterStateType::Fly:
			UE_LOG(LogTemp, Warning, TEXT("Monster Mode: Fly."));
			break;
		case EMonsterStateType::Tired:
			UE_LOG(LogTemp, Warning, TEXT("Monster Mode: Tired."));
			break;
		case EMonsterStateType::Enraged:
			UE_LOG(LogTemp, Warning, TEXT("Monster Mode: Enraged."));
			break;
		case EMonsterStateType::Stunned:
			UE_LOG(LogTemp, Warning, TEXT("Monster Mode: Stunned."));
			break;
		case EMonsterStateType::Knockdown:
			UE_LOG(LogTemp, Warning, TEXT("Monster Mode: Knockdown."));
			break;
		case EMonsterStateType::Dead:
			UE_LOG(LogTemp, Warning, TEXT("Monster Mode: Dead."));
			break;
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