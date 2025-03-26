#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_RoarArea.generated.h"

UCLASS()
class PORTFOLIO_API UCAnimNotify_RoarArea : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Sphere", meta = (AllowPrivateAccess = "true"))
	float TraceRadius	= 2500.f;
	UPROPERTY(EditDefaultsOnly, Category = "Sphere", meta = (AllowPrivateAccess = "true"))
	float TraceDistance = 0.f;
};