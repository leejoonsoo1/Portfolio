#include "CAnimInstance.h"

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	UCStateComponent* StateComp = Cast<UCStateComponent>(TryGetPawnOwner()->GetComponentByClass(UCStateComponent::StaticClass()));
	StateComp->OnWeaponTypeChanged.AddDynamic(this, &UCAnimInstance::OnWeaponTypeChanged);
}

void UCAnimInstance::OnWeaponTypeChanged(EWeaponType InPrevType, EWeaponType InNewType)
{
	WeaponType = InNewType;
}