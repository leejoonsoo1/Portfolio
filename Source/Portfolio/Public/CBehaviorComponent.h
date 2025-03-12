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
	bool IsWaitMode();

	UFUNCTION(Blueprintpure)
	bool IsApproachMode();

	UFUNCTION(Blueprintpure)
	bool IsActionMode();
	
	UFUNCTION(Blueprintpure)
	bool IsPatrolMode();

	UFUNCTION(Blueprintpure)
	bool IsStucnMode();

	UFUNCTION(Blueprintpure)
	bool IsRunAwayMode();

	void SetWaitMode();
	void SetApproachMode();
	void SetActionMode();
	void SetPatrolMode();
	void SetStunMode();
	void SetRunAwayMode();

	AActor* GetTargetValue();
	FVector GetLocationValue();

private:
	UPROPERTY(EditDefaultsOnly, Category = "BlackboardKeyName", meta = (AllowPrivateAccess = "true"))
	FName OtherActorKeyName = "OtherActorKey";

	UPROPERTY(EditDefaultsOnly, Category = "BlackboardKeyName", meta = (AllowPrivateAccess = "true"))
	FName LocationKeyName = "LocationKey";

	UPROPERTY(EditDefaultsOnly, Category = "BlackboardKeyName", meta = (AllowPrivateAccess = "true"))
	FName BehaviorKeyName = "BehaviorKey";

private:
	UBlackboardComponent* BlackboardComp;
		
};