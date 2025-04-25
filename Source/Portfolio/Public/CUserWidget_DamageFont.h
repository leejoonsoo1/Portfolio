#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_DamageFont.generated.h"

UCLASS()
class PORTFOLIO_API UCUserWidget_DamageFont : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetDamage(int32 InDamageAmount);

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DamageText;
};