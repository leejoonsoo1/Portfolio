#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CHUD.generated.h"

class UCUserWidget_Status;

UCLASS()
class PORTFOLIO_API ACHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ACHUD();

public:
	virtual void BeginPlay() override;

	UCUserWidget_Status* GetStatusWidget() const { return Widget; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> StatusWidgetClass;
	
	UPROPERTY()
	UCUserWidget_Status* Widget;
};