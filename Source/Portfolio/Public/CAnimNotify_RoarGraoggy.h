#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_RoarGraoggy.generated.h"

UCLASS()
class PORTFOLIO_API UCAnimNotify_RoarGraoggy : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	UPROPERTY(EditAnywhere, Category = "Sphere", meta = (AllowPrivateAccess = "true"))
	float TraceRadius = 1500.f;
	
	UPROPERTY(EditAnywhere, Category = "Sphere", meta = (AllowPrivateAccess = "true"))
	float TraceDistance = 0.f;
};