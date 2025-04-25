#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CActor_DamageFont.generated.h"

class UWidgetComponent;

UCLASS()
class PORTFOLIO_API ACActor_DamageFont : public AActor
{
	GENERATED_BODY()
	
public:	
	ACActor_DamageFont();

public:
	void SetDamageText(int32 DamageAmount);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UWidgetComponent* WidgetComp;
};