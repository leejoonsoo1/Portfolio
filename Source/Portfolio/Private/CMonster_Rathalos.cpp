#include "CMonster_Rathalos.h"

ACMonster_Rathalos::ACMonster_Rathalos()
{

}

void ACMonster_Rathalos::BeginPlay()
{
	Super::BeginPlay();

	LoadData();
}


void ACMonster_Rathalos::LoadData()
{
	if (MonsterNameToLoad.IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("Please check the monster name."));
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

USkeletalMesh* ACMonster_Rathalos::GetMesh()
{
	Super::GetMesh();

	return MonsterMesh;
}
