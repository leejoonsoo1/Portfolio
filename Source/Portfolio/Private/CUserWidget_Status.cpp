#include "CUserWidget_Status.h"
#include "Kismet\GameplayStatics.h"
#include "GameFramework\PlayerController.h"
#include "Components/ProgressBar.h"
#include "CPlayerCharacter.h"


void UCUserWidget_Status::NativeConstruct()
{
	Super::NativeConstruct();

	if (HP) HP->SetPercent(1.f);
	if (Stamina) Stamina->SetPercent(1.f);

	TargetStamina	= CurrentStamina = 1.f;

	UE_LOG(LogTemp, Warning, TEXT("%s Operated"), *FString(__FUNCTION__));

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : PlayerController is nullptr"), *FString(__FUNCTION__));

		return;
	}

	ACPlayerCharacter* Player = Cast<ACPlayerCharacter>(PC->GetPawn());
	if (!Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Player is nullptr"), *FString(__FUNCTION__));

		return;
	}

	//Player->OnHPChanged.AddDynamic(this, &UCUserWidget_Status::UpdateHP);
	//Player->OnStaminaChanged.AddDynamic(this, &UCUserWidget_Status::UpdateStamina);
}

void UCUserWidget_Status::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UCUserWidget_Status::UpdateHP(float Percent)
{
	if (HP)
	{
		HP->SetPercent(FMath::Clamp(Percent, 0.f, 1.f));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : HP is nullptr"), *FString(__FUNCTION__));
	}
}

void UCUserWidget_Status::UpdateStamina(float Percent)
{
	if (Stamina)
	{
		TargetStamina = FMath::FloorToFloat(Percent * 1000.f) / 1000.f;

		Stamina->SetPercent(FMath::Clamp(Percent, 0.f, 1.f));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Stamina is nullptr"), *FString(__FUNCTION__));
	}
}