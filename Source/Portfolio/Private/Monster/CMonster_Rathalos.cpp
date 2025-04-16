#include "CMonster_Rathalos.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DamageEvents.h"

ACMonster_Rathalos::ACMonster_Rathalos()
{
	AIControllerClass = ACAIController_Monster::StaticClass();

	// 에디터에서 배치된 액터만 AIController를 자동으로 할당. (런타임에서 스폰된 몬스터는 AIController를 받지 않음.)
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 로드할 몬스터 이름.
	MonsterNameToLoad = TEXT("Rathalos");

	GetCapsuleComponent()->SetCanEverAffectNavigation(false);

	// AIController가 방향을 제어하도록 설정
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	/*
	*	2025 03 13
	*	여유가 있으면 구현 예정.
	*	FlyingSpeed와 WalkSppe는 일단 Default값으로.
	*/
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	GetCharacterMovement()->MaxFlySpeed = 1200.f;
	GetCharacterMovement()->BrakingDecelerationFlying = 500.f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
}

void ACMonster_Rathalos::BeginPlay()
{
	Super::BeginPlay();

	LoadData();

	ACAIController_Monster* AIController = Cast<ACAIController_Monster>(GetController());
	
	UE_LOG(LogTemp, Error, TEXT("%s is Called"), *FString(__FUNCTION__));

	if (!AIController)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : ACAIController_Monster is nullptr"), *FString(__FUNCTION__));

		return;
	}
}

void ACMonster_Rathalos::LoadData()
{
	Super::LoadData();

	if (MonsterNameToLoad.IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Please check the monster name."), *FString(__FUNCTION__));

		return;
	}

	UE_LOG(LogTemp, Error, TEXT("%s is Called"), *FString(__FUNCTION__));

	LoadMonsterData(MonsterNameToLoad);
}

void ACMonster_Rathalos::MonsterEnraged()
{
	Super::MonsterEnraged();
}

void ACMonster_Rathalos::Dead()
{
	Super::Dead();

	PlayAnimMontage(DeadMontage);
}

FName ACMonster_Rathalos::GetName()
{
	Super::GetName();

	return MonsterName;
}

float ACMonster_Rathalos::GetHealth()
{
	Super::GetHealth();

	return 0.0f;
}

float ACMonster_Rathalos::GetDamage()
{
	Super::GetDamage();

	return MonsterDamage;
}

void ACMonster_Rathalos::PlayAttackMontage(UAnimMontage* InAnimMontage, float InRate, FName InStartSectionName)
{
	Super::PlayAttackMontage(InAnimMontage, InRate, InStartSectionName);
}

void ACMonster_Rathalos::PlayRoarMontage(UAnimMontage* InAnimMontage, float InRate, FName InStartSecitonName)
{
	Super::PlayRoarMontage(InAnimMontage, InRate, InStartSecitonName);

	PlayAnimMontage(InAnimMontage);
}

float ACMonster_Rathalos::TakeDamage(float InDamageAmount, FDamageEvent const& InDamageEvent, AController* InEventInstigator, AActor* InDamageCauser)
{
	Super::TakeDamage(InDamageAmount, InDamageEvent, InEventInstigator, InDamageCauser);

	return 0.f;
}