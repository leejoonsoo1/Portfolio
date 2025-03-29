#include "CMonster.h"

ACMonster::ACMonster()
{
	StateComp	= CreateDefaultSubobject<UCMonsterStateComponent>(TEXT("MonsterStateComp"));
	EmotionComp = CreateDefaultSubobject<UCMonsterEmotionComponent>(TEXT("MonsterEmotionComp"));

	MonsterName			= NAME_None;
	MonsterDescription	= TEXT("");
	MonsterHealth		= 100.f;
	MonsterDamage		= 10.f;
	WalkSpeed			= 10.f;
	FyingSpeed			= 10.f;
}

void ACMonster::BeginPlay()
{
	Super::BeginPlay();

	UDataTable* DT = LoadObject<UDataTable>(nullptr, TEXT("/Game/DataTable/DT_Monster"));

	if (!DT)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : Monster Table can not found! (/Game/DataTable/DT_Monster)"), *FString(__FUNCTION__));

		return;
	}
	
	MonsterDataTable = DT;

	if (!StateComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : StateComp is nullptr"), *FString(__FUNCTION__));


		return;
	}
	
	StateComp->OnStateChanged.AddDynamic(this, &ACMonster::HandleStateChanged);

	if (!EmotionComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : EmotionComp is nullptr"), *FString(__FUNCTION__));
	}

	EmotionComp->OnEmotionStateChanged.AddDynamic(this, &ACMonster::HandleEmotionChanged);
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
		UE_LOG(LogTemp, Error, TEXT("%s : Monster Table Table is not set!"), *FString(__FUNCTION__));
	}
}

void ACMonster::HandleStateChanged(EMonsterStateType PrevState, EMonsterStateType NewState)
{
	UE_LOG(LogTemp, Warning, TEXT("%s : %d -> %d"), *FString(__FUNCTION__), (int32)PrevState, (int32)NewState);

	switch(NewState)
	{
	case EMonsterStateType::Ground:
			UE_LOG(LogTemp, Warning, TEXT("Monster Mode: Ground."));
			break;
		case EMonsterStateType::Fly:
			UE_LOG(LogTemp, Warning, TEXT("Monster Mode: Fly."));
			break;
		case EMonsterStateType::Idle:
			UE_LOG(LogTemp, Warning, TEXT("Monster Mode: Idle."));
			break;
		case EMonsterStateType::Action:
			UE_LOG(LogTemp, Warning, TEXT("Monster Mode: Action."));
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

void ACMonster::HandleEmotionChanged(EMonsterEmotionStateType PrevState, EMonsterEmotionStateType NewState)
{
	UE_LOG(LogTemp, Warning, TEXT("Monster Emotion Changed : %d -> %d"), (int32)PrevState, (int32)NewState);

	switch (NewState)
	{
	case EMonsterEmotionStateType::Calm:
		UE_LOG(LogTemp, Warning, TEXT("Monster Mode: Calm."));
		break;
	case EMonsterEmotionStateType::Alert:
		UE_LOG(LogTemp, Warning, TEXT("Monster Mode: Alert."));
		break;
	case EMonsterEmotionStateType::Tired:
		UE_LOG(LogTemp, Warning, TEXT("Monster Mode: Tired."));
		break;
	case EMonsterEmotionStateType::Enraged:
		UE_LOG(LogTemp, Warning, TEXT("Monster Mode: Enraged."));
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

void ACMonster::OnAttackCollisionHead_Implementation()
{
}

void ACMonster::OnAttackCollisionTail_Implementation()
{
}

void ACMonster::OnAttackCollisionFeet_Implementation()
{
}

void ACMonster::OffAttackCollisionHead_Implementation()
{
}

void ACMonster::OffAttackCollisionTail_Implementation()
{
}

void ACMonster::OffAttackCollisionFeet_Implementation()
{
}

void ACMonster::PlayAttackMontage(UAnimMontage* InAnimMontage, float InRate, FName InSectionName)
{
	StateComp->SetActionMode();

	OnAttackCollisionHead();
	PlayAnimMontage(InAnimMontage, InRate, InSectionName);
}

void ACMonster::PlayRoarMontage(UAnimMontage* InAnimMontage, float InRate, FName InSectionName)
{
}