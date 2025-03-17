#pragma once

#include "CoreMinimal.h"
#include "Type.h"
#include "Components/ActorComponent.h"
#include "CBehaviorComponent.generated.h"

class UBlackboardComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_API UCBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCBehaviorComponent();

public:
	void SetBlackboardComponent(UBlackboardComponent* InBlackboardComp);

private:
	EBehaviorType GetType();
	void ChangeType(EBehaviorType InNewType);

public:
	UFUNCTION(Blueprintpure)
	bool IsIdleMode();

	UFUNCTION(Blueprintpure)
	bool IsWaitMode();

	UFUNCTION(Blueprintpure)
	bool IsApproachMode();

	UFUNCTION(Blueprintpure)
	bool IsAttackMode();
	
	UFUNCTION(Blueprintpure)
	bool IsPatrolMode();

	UFUNCTION(Blueprintpure)
	bool IsFlinchMode();

	UFUNCTION(Blueprintpure)
	bool IsRunAwayMode();

	UFUNCTION(Blueprintpure)
	bool IsSearchMode();

	UFUNCTION(Blueprintpure)
	bool IsRoarMode();

	UFUNCTION(Blueprintpure)
	bool IsLandMode();

	UFUNCTION(Blueprintpure)
	bool IsTakeoffMode();

public:
	void SetIdleMode();
	void SetWaitMode();
	void SetApproachMode();
	void SetAttackMode();
	void SetSpecialMode();
	void SetPatrolMode();
	void SetFlinchMode();
	void SetRunAwayMode();
	void SetSearchMode();
	void SetRoarMode();
	void SetLandMode();
	void SetTakeoffMode();

	AActor* GetTargetValue();
	FVector GetLocationValue();

private:
	UPROPERTY(EditDefaultsOnly, Category = "BlackboardKeyName", meta = (AllowPrivateAccess = "true"))
	FName OtherActorKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "BlackboardKeyName", meta = (AllowPrivateAccess = "true"))
	FName LocationKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "BlackboardKeyName", meta = (AllowPrivateAccess = "true"))
	FName BehaviorKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "BlackboardKeyName", meta = (AllowPrivateAccess = "true"))
	FName AngleKeyName;

private:
	UBlackboardComponent* BlackboardComp;
};