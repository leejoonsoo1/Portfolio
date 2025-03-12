#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CMonster.generated.h"

/*
 *  2025-03-10
 *  몬스터의 최상위 클래스.
 *  - 몬스터의 데이터 테이블을 초기화하고 Behavior Tree를 저장하는 역할을 수행.
 *  - 공격은 Behavior Tree를 통해 몽타주를 제어하는 방식으로 구현할 예정.
 *  - 현재 추가적인 기능은 구상 중이며, 아직 큰 기능은 없음.
 */
 
class UBehaviorTree;

USTRUCT(BlueprintType)
struct FMonsterData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Monster")
	FName Name;

	UPROPERTY(EditAnywhere, Category = "Monster")
	FName Description;

	UPROPERTY(EditAnywhere, Category = "Monster")
	float Health;

	UPROPERTY(EditAnywhere, Category = "Monster")
	float Damage;
};

UCLASS()
class PORTFOLIO_API ACMonster : public ACharacter
{
	GENERATED_BODY()

public:
	ACMonster();

protected:
	virtual void BeginPlay() override;
	virtual void LoadData();

public:
	virtual FName GetName();
	virtual float GetHealth();
	virtual float GetDamage();
	
public:
	FORCEINLINE UDataTable* GetMonsterTable() const { return MonsterDataTable; }
	FORCEINLINE UBehaviorTree* GetBehaviorTree() { return BehaviorTreeAsset; }

public:
	void LoadMonsterData(FName InMonsterName);

	// virtual function으로 beginOverlap 넣을 예정.

private:	
	UPROPERTY(EditDefaultsOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UDataTable* MonsterDataTable;

	UPROPERTY(EditDefaultsOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviorTreeAsset;

protected:
	FName MonsterName;
	FName MonsterDescription;
	float MonsterHealth;
	float MonsterDamage;
};
  