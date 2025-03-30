#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_RadialAttack.generated.h"

UCLASS()
class PORTFOLIO_API UCAnimNotify_RadialAttack : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);

private:
	UPROPERTY(EditAnywhere, Category = "Sphere", meta = (AllowPrivateAccess = "true"))
	float TraceRadius = 1500.f;
	
	UPROPERTY(EditAnywhere, Category = "Sphere", meta = (AllowPrivateAccess = "true"))
	float TraceDistance = 0.f;

	UPROPERTY(EditAnywhere, Category = "Sphere", meta = (AllowPrivateAccess = "true"))
	float Damage = 0.f;
};