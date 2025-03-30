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
	UE_LOG(LogTemp, Error, TEXT("%s is Called : %s"), *FString(__FUNCTION__), *InMonsterName.ToString());

	if (MonsterDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("%s exist DataTable"), *FString(__FUNCTION__));

		TArray<FName> RowNames = MonsterDataTable->GetRowNames();

		UE_LOG(LogTemp, Error, TEXT("%s ddaasdf : %s"), *FString(__FUNCTION__), *RowNames[0].ToString());

		for (const FName& RowName : RowNames)
		{
			FMonsterData* MonsterData = MonsterDataTable->FindRow<FMonsterData>(RowName, TEXT(""));

			UE_LOG(LogTemp, Error, TEXT("%s For Inside : %s"), *FString(__FUNCTION__), *MonsterData->Name.ToString());

			if (MonsterData->Name == InMonsterName)
			{
				UE_LOG(LogTemp, Error, TEXT("%s Find RowName"), *FString(__FUNCTION__));

				MonsterName			= MonsterData->Name;
				MonsterDescription	= MonsterData->Description;
				MonsterMaxHealth	= MonsterData->Health;
				MonsterHealth		= MonsterMaxHealth;
				MonsterDamage		= MonsterData->Damage;

				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,
						FString::Printf(TEXT("%s : MonsterName : %s"), *FString(__FUNCTION__), *MonsterName.ToString()));

					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,
						FString::Printf(TEXT("%s : MonsterDescription : %s"), *FString(__FUNCTION__), *MonsterDescription));

					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,
						FString::Printf(TEXT("%s : MonsterMaxHealth : %.2f"), *FString(__FUNCTION__), MonsterHealth));

					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,
						FString::Printf(TEXT("%s : MonsterDamage : %.2f"), *FString(__FUNCTION__), MonsterDamage));
				}
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
			UE_LOG(LogTemp, Warning, TEXT("%s : Monster Mode: Ground."), *FString(__FUNCTION__));
			break;
		case EMonsterStateType::Fly:
			UE_LOG(LogTemp, Warning, TEXT("%s : Monster Mode: Fly."), *FString(__FUNCTION__));
			break;
		case EMonsterStateType::Idle:
			UE_LOG(LogTemp, Warning, TEXT("%s : Monster Mode: Idle."), *FString(__FUNCTION__));
			break;
		case EMonsterStateType::Action:
			UE_LOG(LogTemp, Warning, TEXT("%s : Monster Mode: Action."), *FString(__FUNCTION__));
			break;
		case EMonsterStateType::Stunned:
			UE_LOG(LogTemp, Warning, TEXT("%s : Monster Mode: Stunned."), *FString(__FUNCTION__));
			break;
		case EMonsterStateType::Knockdown:
			UE_LOG(LogTemp, Warning, TEXT("%s : Monster Mode: Knockdown."), *FString(__FUNCTION__));
			break;
		case EMonsterStateType::Dead:
			UE_LOG(LogTemp, Warning, TEXT("%s : Monster Mode: Dead."), *FString(__FUNCTION__));
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

void ACMonster::ApplyDamage(float InDamage, FDamageEvent const& InDamageEvent, AController* InEventInstigator, AActor* InDamageCauser)
{
	TakeDamage(InDamage, InDamageEvent, InEventInstigator, InDamageCauser);
}

float ACMonster::TakeDamage(float InDamageAmount, FDamageEvent const& InDamageEvent, AController* InEventInstigator, AActor* InDamageCauser)
{
	MonsterHealth -= InDamageAmount;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Monster Current HP : %.1f"), MonsterHealth));

	if (MonsterHealth <= 0.f)
	{
		if (!StateComp)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s : StateComp is nullptr"), *FString(__FUNCTION__));

			return 0.f;
		}

		StateComp->SetDeadMode();
	}

	return 0.f;
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