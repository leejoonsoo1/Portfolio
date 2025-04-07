#include "CHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Status.h"
#include "CPlayerCharacter.h"

ACHUD::ACHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetFinder(TEXT("/Game/UI/BP_UI"));

	if (WidgetFinder.Succeeded())
	{
		StatusWidgetClass = WidgetFinder.Class;
	}
}

void ACHUD::BeginPlay()
{
	Super::BeginPlay();

	if (StatusWidgetClass)
	{
		Widget = CreateWidget<UCUserWidget_Status>(GetWorld(), StatusWidgetClass);

		if (Widget)
		{
			Widget->AddToViewport();

			APlayerController* PC = GetWorld()->GetFirstPlayerController();
			if (!PC)
			{
				UE_LOG(LogTemp, Warning, TEXT("%s : PC is nullptr"), *FString(__FUNCTION__));

				return;
			}

			ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(PC->GetPawn());
			if (!Player)
			{
				UE_LOG(LogTemp, Warning, TEXT("%s : Player is nullptr"), *FString(__FUNCTION__));

				return;
			}

			Player->OnHPChanged.AddDynamic(Widget, &UCUserWidget_Status::UpdateHP);
			Player->OnStaminaChanged.AddDynamic(Widget, &UCUserWidget_Status::UpdateStamina);

			Widget->UpdateHP(Player->GetCurrentHP() / Player->GetMaxHP());
			Widget->UpdateStamina(Player->GetCurrentStamina() / Player->GetMaxStamina());
		}
	}
}