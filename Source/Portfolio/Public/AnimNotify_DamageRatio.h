#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_DamageRatio.generated.h"

UCLASS()
class PORTFOLIO_API UAnimNotify_DamageRatio : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	UPROPERTY(EditAnywhere, Category = "DamageRatio", meta = (AllowPrivateAccess = "true"))
	float DamageRatio = 1.f;
};