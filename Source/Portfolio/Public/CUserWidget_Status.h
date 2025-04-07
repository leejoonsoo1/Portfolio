#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Status.generated.h"

class UProgressBar;

UCLASS()
class PORTFOLIO_API UCUserWidget_Status : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION()
	void UpdateHP(float Percent);

	UFUNCTION()
	void UpdateStamina(float Percent);

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HP;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* Stamina;

	float TargetStamina = 1.f;
	float CurrentStamina = 1.f;
};