#include "CUserWidget_DamageFont.h"
#include "Components/TextBlock.h"

void UCUserWidget_DamageFont::SetDamage(int32 InDamageAmount)
{
	if (DamageText)
	{
		DamageText->SetText(FText::AsNumber(InDamageAmount));
	}
}