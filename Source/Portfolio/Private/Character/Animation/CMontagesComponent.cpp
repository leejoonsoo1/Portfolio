#include "CMontagesComponent.h"
#include "GameFramework/Character.h"
#include "Animation/AnimInstance.h"

// Sets default values
UCMontagesComponent::UCMontagesComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
}

// Called when the game starts or when spawned
void UCMontagesComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!DataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable is not set"));
		return;
	}

	StateComponent = Cast<UCStateComponent>(GetOwner()->FindComponentByClass<UCStateComponent>());

	if (!StateComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("StateComponent not found"));
		return;
	}

	// 델리게이트 구독
	StateComponent->OnStateTypeChanged.AddDynamic(this, &UCMontagesComponent::StateChanged);
	StateComponent->OnWeaponTypeChanged.AddDynamic(this, &UCMontagesComponent::WeaponChanged);
	
	// 델리게이트 초기값 설정.
	StateChanged(StateComponent->GetEStateType(), StateComponent->GetEStateType());
	WeaponChanged(StateComponent->GetEWeaponType(), StateComponent->GetEWeaponType());
}

void UCMontagesComponent::PlayEquipping()
{
	PlayAnimMontage(EStateType::Equip);
}

void UCMontagesComponent::PlayUnEquipping()
{
	PlayAnimMontage(EStateType::UnEquip);
}

void UCMontagesComponent::PlayEvade()
{
	PlayAnimMontage(EStateType::Evade);
}

void UCMontagesComponent::PlayHitted()
{
	PlayAnimMontage(EStateType::Hitted);
}

void UCMontagesComponent::PlayGimmicked()
{
}

void UCMontagesComponent::StateChanged(EStateType InPrevType, EStateType InNewType)
{
	UpdateMontage();
}

void UCMontagesComponent::WeaponChanged(EWeaponType InPrevType, EWeaponType InNewType)
{
	UpdateMontage();
}

void UCMontagesComponent::UpdateMontage()
{
	if (!StateComponent) return;

	EStateType CurrentState = StateComponent->GetEStateType();
	EWeaponType CurrentWeapon = StateComponent->GetEWeaponType();

	TArray<FMontageData*> AllMontages;
	DataTable->GetAllRows<FMontageData>("", AllMontages);

	for (FMontageData* Montage : AllMontages)
	{
		if (Montage->StateType == CurrentState && Montage->WeaponType == CurrentWeapon)
		{
			CurrentMontage = Montage;
			UE_LOG(LogTemp, Log, TEXT("Montage Updated: %s"), *Montage->Name);
		}
	}
}

void UCMontagesComponent::PlayAnimMontage(EStateType InType)
{
	if (!CurrentMontage || !CurrentMontage->AnimMontage) return;

	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter) return;
	
	OwnerCharacter->PlayAnimMontage(CurrentMontage->AnimMontage, CurrentMontage->PlayRate, CurrentMontage->StartSection);

}