#include "CStateComponent.h"

UCStateComponent::UCStateComponent()
{

}

void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCStateComponent::SetIdleMode()
{
	ChangeStateType(EStateType::Idle);
}

void UCStateComponent::SetEvadeMode()
{
	ChangeStateType(EStateType::Evade);
}

void UCStateComponent::SetEquipMode()
{
	ChangeStateType(EStateType::Equip);
}

void UCStateComponent::SetActionMode()
{
	ChangeStateType(EStateType::Action);
}

void UCStateComponent::SetHittedMode()
{
	ChangeStateType(EStateType::Hitted);
}

void UCStateComponent::setDeadMode()
{
	ChangeStateType(EStateType::Dead);
}

void UCStateComponent::SetUnarmedMode()
{
	ChangeWeaponType(EWeaponType::Unarmed);
}

void UCStateComponent::SetSwordNShieldMode()
{
	ChangeWeaponType(EWeaponType::SwordNShield);
}

void UCStateComponent::SetGreatSwordMode()
{
	ChangeWeaponType(EWeaponType::GreatSword);
}

void UCStateComponent::SetLongSwordMode()
{
	ChangeWeaponType(EWeaponType::LongSword);
}

void UCStateComponent::SetHammerMode()
{
	ChangeWeaponType(EWeaponType::Hammer);
}

void UCStateComponent::SetLightBowgunMode()
{
	ChangeWeaponType(EWeaponType::LightBowgun);
}

void UCStateComponent::SetBowMode()
{
	ChangeWeaponType(EWeaponType::Bow);
}

void UCStateComponent::SetLanceMode()
{
	ChangeWeaponType(EWeaponType::Lance);
}

void UCStateComponent::SetDualBladesMode()
{
	ChangeWeaponType(EWeaponType::DualBlades);
}

void UCStateComponent::SetGunLanceMode()
{
	ChangeWeaponType(EWeaponType::GunLance);
}

void UCStateComponent::SetHeavyBowgunMode()
{
	ChangeWeaponType(EWeaponType::HeavyBowgun);
}

void UCStateComponent::SetSwitchAxeMode()
{
	ChangeWeaponType(EWeaponType::SwitchAxe);
}

void UCStateComponent::ChangeStateType(EStateType InNewType)
{
	EStateType PrevType = StateType;
	StateType = InNewType;

	OnStateTypeChanged.Broadcast(PrevType, StateType);
}

void UCStateComponent::ChangeWeaponType(EWeaponType InNewType)
{
	EWeaponType PrevType = WeaponType;
	WeaponType = InNewType;

	OnWeaponTypeChanged.Broadcast(PrevType, WeaponType);
}