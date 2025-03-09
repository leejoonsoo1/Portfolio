#include "CAttachment.h"
#include "CWeapon.h"
#include "CGreatSword.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

UCAttachment::UCAttachment()
{
	
}

void UCAttachment::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	if (!OwnerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCAttachment : OwnerCharacter is null!"));

		return;
	}

	if (!OwnerCharacter->GetMesh())
	{
		UE_LOG(LogTemp, Warning, TEXT("UCAttachment : OwnerCharacter has no mesh"));

		return;
	}
	
	/*
	*	2025 03 06
	*	무기 충돌 감지를 위한 Collision 셋.
	*/
	if (!Mesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCAttachment : Mesh is null!"));

		return;
	}
	
	Mesh->SetCollisionProfileName(TEXT("Weapon"));

	SpawnWeapon();
}

void UCAttachment::ComponentAttachTo(USkeletalMeshComponent* OwnerMesh, FName SocketName)
{
	if (!OwnerMesh)
	{
		if (!OwnerCharacter || !OwnerCharacter->GetMesh())
		{
			UE_LOG(LogTemp, Error, TEXT("UCAttachment: Failed to attch - OwnerCharacter or Mesh is null!"));

			return;
		}

		OwnerMesh = OwnerCharacter->GetMesh();
	}

	if (!Mesh)
	{
		UE_LOG(LogTemp, Error, TEXT("UCAttachment: Failed to attch - Attach Mesh is null!"));

		return;
	}

	Mesh->AttachToComponent(OwnerMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), SocketName);
}

void UCAttachment::SpawnWeapon()
{
	if (!WeaponClass)
	{
		UE_LOG(LogTemp, Error, TEXT("WeaponClass is not set in Attachment Component."));
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("SpawnWeapon: World is null!"));
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = OwnerCharacter;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn; // 충돌 문제 방지

	ACWeapon* DeferredWeapon = World->SpawnActorDeferred<ACWeapon>(WeaponClass, FTransform(FRotator(0, 0, 0), FVector(0, 0, 0)), OwnerCharacter, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);

	if (DeferredWeapon)
	{
		DeferredWeapon->SetWeaponOwner(OwnerCharacter);

		DeferredWeapon->FinishSpawning(FTransform(FRotator(0, 0, 0), FVector(0, 0, 0)));

		CurrentWeapon = DeferredWeapon;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SpawnWeapon: SpawnActorDeferred failed!"));
	}

	if (CurrentWeapon)
	{
		Damage = CurrentWeapon->GetDamage();
		WeaponType = CurrentWeapon->GetWeaponType();

		if (Mesh && !Mesh->SkeletalMesh)
		{
			Mesh->SetSkeletalMesh(CurrentWeapon->GetMesh());
		}
	}
}

void UCAttachment::Attack()
{
	CurrentWeapon->Attack();
}

void UCAttachment::SwitchWeaponType(EWeaponType NewType)
{
	TSubclassOf<ACWeapon> NewWeaponClass = nullptr;

	switch (NewType)
	{
	case EWeaponType::Unarmed:
		break;
	case EWeaponType::SwordNShield:
		break;
	case EWeaponType::GreatSword:
		NewWeaponClass = ACGreatSword::StaticClass();
		break;
	case EWeaponType::LongSword:
		break;
	case EWeaponType::Hammer:
		break;
	case EWeaponType::LightBowgun:
		break;
	case EWeaponType::Bow:
		break;
	case EWeaponType::Lance:
		break;
	case EWeaponType::DualBlades:
		break;
	case EWeaponType::ChargeBlade:
		break;
	case EWeaponType::GunLance:
		break;
	case EWeaponType::HeavyBowgun:
		break;
	case EWeaponType::SwitchAxe:
		break;
	}

	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
		CurrentWeapon = nullptr;
	}

	if (NewWeaponClass)
	{
		WeaponClass = NewWeaponClass;
		SpawnWeapon();
	}
}