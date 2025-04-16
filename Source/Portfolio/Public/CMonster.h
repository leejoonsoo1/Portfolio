#pragma once

#include "CoreMinimal.h"
#include "CMonsterStateComponent.h"
#include "CMonsterEmotionComponent.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "Engine/DamageEvents.h"
#include "CMonster.generated.h"

/*
 *  2025-03-10
 *  몬스터의 최상위 클래스.
 *  - 몬스터의 데이터 테이블을 초기화하고 Behavior Tree를 저장하는 역할을 수행.
 *  - 공격은 Behavior Tree를 통해 몽타주를 제어하는 방식으로 구현할 예정.
 *  - 현재 추가적인 기능은 구상 중이며, 아직 큰 기능은 없음.
 */
 
class UBehaviorTree;
class UCBehaviorComponent;

USTRUCT(BlueprintType)
struct FMonsterData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Monster")
	FName Name;

	UPROPERTY(EditAnywhere, Category = "Monster")
	FString Description;

	UPROPERTY(EditAnywhere, Category = "Monster")
	float Health;

	UPROPERTY(EditAnywhere, Category = "Monster")
	float Damage;

	UPROPERTY(EditAnywhere, Category = "Monster")
	float WalkSpeed;

	UPROPERTY(EditAnywhere, Category = "Monster")
	float FyingSpeed;
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
	
	virtual void MonsterEnraged();
	virtual void Dead();

public:
	virtual void PlayAttackMontage(UAnimMontage* InAnimMontage, float InRate, FName InSectionName);
	virtual void PlayRoarMontage(UAnimMontage* InAnimMontage, float InRate, FName InSectionName);
	virtual FName GetName();
	virtual float GetHealth();
	virtual float GetDamage();
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Attack")
	void OnAttackCollisionHead();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Attack")
	void OnAttackCollisionTail();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Attack")
	void OnAttackCollisionFeet();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Attack")
	void OffAttackCollisionHead();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Attack")
	void OffAttackCollisionTail();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Attack")
	void OffAttackCollisionFeet();

public:
	FORCEINLINE UDataTable* GetMonsterTable() const { return MonsterDataTable; }
	FORCEINLINE UBehaviorTree* GetBehaviorTree() { return BehaviorTreeAsset; }

public:
	void LoadMonsterData(FName InMonsterName);

	UFUNCTION()
	void HandleStateChanged(EMonsterStateType PrevState, EMonsterStateType NewState);

	UFUNCTION()
	void HandleEmotionChanged(EMonsterEmotionStateType PrevState, EMonsterEmotionStateType NewState);

	UFUNCTION(BlueprintCallable)
	void ApplyDamage(float InDamage, FDamageEvent const& InDamageEvent, AController* InEventInstigator, AActor* InDamageCauser);
	virtual float TakeDamage(float InDamageAmount, struct FDamageEvent const& InDamageEvent, class AController* InEventInstigator, class AActor* InDamageCauser) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component")
	UCMonsterStateComponent* StateComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component")
	UCMonsterEmotionComponent* EmotionComp;

	//UPROPERTY(EditAnywhere, Category = "AI")
	//UCBehaviorComponent* BehaviorComp;

private:	
	UPROPERTY(EditDefaultsOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UDataTable* MonsterDataTable;

	UPROPERTY(EditDefaultsOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviorTreeAsset;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* RoarMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeadMontage;

protected:
	FName MonsterName;
	FString MonsterDescription;
	float MonsterMaxHealth;
	float MonsterHealth;	
	float MonsterDamage;
	float WalkSpeed;
	float FyingSpeed;
};