#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CStateComponent.h"
#include "CMontagesComponent.generated.h"

USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	EStateType StateType;
	 
	UPROPERTY(EditAnywhere)
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AnimMontage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
	FName StartSection;

	UPROPERTY(EditAnywhere)
	bool bCanMove;
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
	void PlayEvade();
	void PlayHitted();
	void PlayGimmicked();

private:
	UFUNCTION()
	void UpdateMontage();
	UFUNCTION()
	void PlayAnimMontage(EStateType InStateType);

	UFUNCTION()
	void StateChanged(EStateType InPrevType, EStateType InNewType);

	UFUNCTION()
	void WeaponChanged(EWeaponType InPrevType, EWeaponType InNewType);

private:
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
	UDataTable* DataTable;

	FMontageData* CurrentMontage;
	UCStateComponent* StateComponent;

private:
	FMontageData* Datas[(int32)EStateType::Max];
	TArray<FMontageData*> ReadDatas;
};