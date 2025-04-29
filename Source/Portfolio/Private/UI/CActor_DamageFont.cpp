#include "CActor_DamageFont.h"
#include "Components/WidgetComponent.h"
#include "CUserWidget_DamageFont.h"

ACActor_DamageFont::ACActor_DamageFont()
{
	PrimaryActorTick.bCanEverTick = false;

	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComp"));
	RootComponent = WidgetComp;

	WidgetComp->SetWidgetSpace(EWidgetSpace::World);
	WidgetComp->SetDrawSize(FVector2D(300.f, 100.f));

	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Game/UI/WB_DamageFont"));
	if (WidgetClass.Succeeded())
	{
		WidgetComp->SetWidgetClass(WidgetClass.Class);
	}

	SetLifeSpan(4.f);
}

void ACActor_DamageFont::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(4.f);
}

void ACActor_DamageFont::SetDamageText(int32 DamageAmount)
{
	UUserWidget* Widget = WidgetComp->GetUserWidgetObject();
	
	if (!Widget)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Widget is nullptr"), *FString(__FUNCTION__));

		return;
	}
	
	UCUserWidget_DamageFont* DamageWidget = Cast<UCUserWidget_DamageFont>(Widget);
	if (DamageWidget)
	{
		DamageWidget->SetDamage(DamageAmount);
	}
}