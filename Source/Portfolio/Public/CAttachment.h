#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAttachment.generated.h"

class USkeletalMeshComponent;
class ACharacter;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PORTFOLIO_API UCAttachment : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	UCAttachment();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintCallable)
	void ComponentAttachTo(FName SocketName = "Holster");

public:
	USkeletalMeshComponent* GetMesh() { return Mesh; }

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Comp")
	USceneComponent* RootComp;

public:
	UPROPERTY(EditAnywhere, Category = "Comp")
	USkeletalMeshComponent* Mesh;

	ACharacter* OwnerCharacter;
};
