#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CStateComponent.h"
#include "CMontagesComponent.generated.h"

/*
* 2025. 02. 28
* About Play Animation Montage Class
* 현재 EStateType과 EWeaponType만을 참조해서 두 타입이 변하는 시점에 DataTable의 1개 Row를 업데이트를 진행.
* 두 개의 변수 타입만 가지고 애니메이션을 재생하기 때문에, 다양한 전투 동작을 재생하는데 한계가 존재함.
* Evade와 Equip, UnEquip 모션은 기본 동작으로만 구성을 하고 Battle 관련 DataTable을 따로 생성이 필요함.
*
* 기존에 비효율적인 EStateType과 EWeaponType이 변할 때마다
* Row을 읽어오는게 아니라 DataTable 형식으로 읽어와서 Map의 형태로 변수를 저장
* Name으로 불러올 예정.
*/

USTRUCT(BlueprintType)
struct FBasicMontageData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	FString Description;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
	FName StartSection;
}; 

/*
* 2025 02 28 금요일
* 공격 모션은 모든 공격의 첫 타격만 데이터 테이블에서 저장.
* 나머지 콤보로 이어지는 동작은 AnimNotify_State에서 다룰 에정.
*/
USTRUCT(BlueprintType)
struct FBattleMontageData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	FString Description;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
	FName StartSection;
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PORTFOLIO_API UCMontagesComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UCMontagesComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	UAnimMontage* GetMontage(FName InRowName = TEXT(""), EStateType InType = EStateType::UnEquip);

	UFUNCTION()
	UAnimMontage* GetBasicMontage(FName InMontageName);

	UFUNCTION()
	UAnimMontage* GetBattleMontage(FName InMontageName);

public:
	// Evade는 무장한 상태와 무장 안한 상태 때문에 EStateType이 필요.
	void PlayEvade(FName InRowName = "UnArmedEvade", EStateType Type = EStateType::UnEquip);

public:
	void PlayEquipping();
	void PlayUnEquipping();
	void PlayHitted();
	void PlayGimmicked();

private:
	UFUNCTION()
	void LoadBasicAnimMontages();

	UFUNCTION()
	void LoadBattleAnimMontages();

	UFUNCTION()
	void CustomPlayAnimMontage(UAnimMontage* AnimMontage, float InPlayRate = 1.0f, FName StartSectionName = NAME_None);

private:
	// 기본 모션 테이블, 맵.
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
	UDataTable* BasicMontageTable;
	TMap<FName, UAnimMontage*> BasicMontageMap;

	// 배틀 관련 데이터 테이블, 맵.
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
	UDataTable* BattleMontageTable;
	TMap<FName, UAnimMontage*> BattleMontageMap;
};