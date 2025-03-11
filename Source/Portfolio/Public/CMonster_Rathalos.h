#pragma once

#include "CoreMinimal.h"
#include "CMonster.h"
#include "CAIController_Monster.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "CMonster_Rathalos.generated.h"

/*
 *  2025-03-10
 *  몬스터 헌터의 시그니처 몬스터, 리오레우스.
 *  - 부모 클래스에서 저장한 데이터 테이블을 `Rathalos` 멤버 변수에 할당.
 *  - 현재는 기본적인 데이터 설정만 포함되어 있으며, 주요 기능은 추후 추가 예정.
 */
UCLASS()
class PORTFOLIO_API ACMonster_Rathalos : public ACMonster
{
	GENERATED_BODY()
	
protected:
	ACMonster_Rathalos();
	virtual void BeginPlay() override;
	virtual void LoadData() override;

public:
	// 몬스터 공통 함수.
	virtual FName GetName() override;
	virtual float GetHealth() override;
	virtual float GetDamage() override;

	// virtual function으로 beginOverlap 넣을 예정.

	// AI 관련

private:
	FName MonsterNameToLoad;

	UPROPERTY(EditDefaultsOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviorTreeAsset;
};
