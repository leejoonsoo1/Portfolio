#include "CMonster_Rathalos.h"

ACMonster_Rathalos::ACMonster_Rathalos()
{
	AIControllerClass = ACAIController_Monster::StaticClass();

	// 에디터에서 배치된 액터만 AIController를 자동으로 할당. (런타임에서 스폰된 몬스터는 AIController를 받지 않음.)
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 로드할 몬스터 이름.
	MonsterNameToLoad = TEXT("Rathalos");
}

void ACMonster_Rathalos::BeginPlay()
{
	Super::BeginPlay();

	LoadData();

	ACAIController_Monster* AIController = Cast<ACAIController_Monster>(GetController());

	if (AIController)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController is successfully assigned and of type ACAIController_Monster: %s"), *AIController->GetName());

		return;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AIController is NOT assigned or not of type ACAIController_Monster!"));

		return;
	}


}


void ACMonster_Rathalos::LoadData()
{
	if (MonsterNameToLoad.IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("Please check the monster name."));

		return;
	}

	LoadMonsterData(MonsterNameToLoad);
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