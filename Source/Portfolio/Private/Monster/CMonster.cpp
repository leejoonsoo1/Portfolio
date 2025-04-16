#include "CMonster.h"
#include "CAIController_Monster.h"
#include "BrainComponent.h"

ACMonster::ACMonster()
{
	StateComp		= CreateDefaultSubobject<UCMonsterStateComponent>(TEXT("MonsterStateComp"));
	EmotionComp		= CreateDefaultSubobject<UCMonsterEmotionComponent>(TEXT("MonsterEmotionComp"));
	//BehaviorComp	= CreateDefaultSubobject<UCBehaviorComponent>(TEXT("BehaviorComp"));

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

// This function is overridden in a child class.
void ACMonster::LoadData()
{
}

void ACMonster::MonsterEnraged()
{
}

void ACMonster::Dead()
{
	ACAIController_Monster* AIC = Cast<ACAIController_Monster>(GetController());

	if (!AIC)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : AIC is nullptr"), *FString(__FUNCTION__));

		return;
	}

	AIC->BrainComponent->StopLogic("Monster Died");
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
	//UE_LOG(LogTemp, Warning, TEXT("%s : %d -> %d"), *FString(__FUNCTION__), (int32)PrevState, (int32)NewState);

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
			Dead();
			break;
	}
}

void ACMonster::HandleEmotionChanged(EMonsterEmotionStateType PrevState, EMonsterEmotionStateType NewState)
{
	//UE_LOG(LogTemp, Warning, TEXT("Monster Emotion Changed : %d -> %d"), (int32)PrevState, (int32)NewState);

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
		MonsterEnraged();
		break;
	}
}

void ACMonster::ApplyDamage(float InDamage, FDamageEvent const& InDamageEvent, AController* InEventInstigator, AActor* InDamageCauser)
{
	TakeDamage(InDamage, InDamageEvent, InEventInstigator, InDamageCauser);
}

float ACMonster::TakeDamage(float InDamageAmount, FDamageEvent const& InDamageEvent, AController* InEventInstigator, AActor* InDamageCauser)
{
	MonsterHealth = FMath::Clamp(MonsterHealth - InDamageAmount, 0.f, MonsterHealth);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Monster Current HP : %.1f"), MonsterHealth));

	if (MonsterHealth <= 0.f)
	{
		if (!StateComp)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s : StateComp is nullptr"), *FString(__FUNCTION__));

			return 0.f;
		}

		if (!StateComp->IsDeadMode())
		{
			StateComp->SetDeadMode();
		}
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

// This function is overridden in Blueprint.
void ACMonster::OnAttackCollisionHead_Implementation()
{
}

// This function is overridden in Blueprint.
void ACMonster::OnAttackCollisionTail_Implementation()
{
}

// This function is overridden in Blueprint.
void ACMonster::OnAttackCollisionFeet_Implementation()
{
}

// This function is overridden in Blueprint.
void ACMonster::OffAttackCollisionHead_Implementation()
{
}

// This function is overridden in Blueprint.
void ACMonster::OffAttackCollisionTail_Implementation()
{
}

// This function is overridden in Blueprint.
void ACMonster::OffAttackCollisionFeet_Implementation()
{
}

void ACMonster::PlayAttackMontage(UAnimMontage* InAnimMontage, float InRate, FName InSectionName)
{
	StateComp->SetActionMode();

	PlayAnimMontage(InAnimMontage, InRate, InSectionName);
}

void ACMonster::PlayRoarMontage(UAnimMontage* InAnimMontage, float InRate, FName InSectionName)
{
}