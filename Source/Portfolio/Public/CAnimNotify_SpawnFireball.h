#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_SpawnFireball.generated.h"

UCLASS()
class PORTFOLIO_API UCAnimNotify_SpawnFireball : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

public:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AActor> FireballClass;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	FName SocketName = NAME_None;
};