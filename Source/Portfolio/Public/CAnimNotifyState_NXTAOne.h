#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState_NXTAOne.generated.h"

UCLASS()
class PORTFOLIO_API UCAnimNotifyState_NXTAOne : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	UPROPERTY(EditAnywhere, Category = "True", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AnimMontage_NextCharge;

	UPROPERTY(EditAnywhere, Category = "False", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AnimMontage_NextAttack;

	UPROPERTY(EditAnywhere, Category = "NextMotion", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AnimMontage_NextAttackStance;

	UPROPERTY(EditAnywhere, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	float PlayRate = 1.f;

	UPROPERTY(EditAnywhere, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	FName StartSectionName = NAME_None;

	// 동시 입력이 안됨. 삭제 예정.
	UPROPERTY(EditAnywhere)
	FKey ConditionKey = EKeys::Invalid;
};