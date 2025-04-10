#include "CAttachment.h"
#include "CWeapon.h"
#include "CGreatSword.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "CMonster.h"
#include "Engine/DamageEvents.h"

UCAttachment::UCAttachment()
{
	Damage = 1000.f;
	DamageRatio = 1.f;
	VolumeMultiplier = 1.f;
	PitchMultiplier = 1.f;
}

void UCAttachment::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	if (!OwnerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : OwnerCharacter is null!"), *FString(__FUNCTION__));

		return;
	}

	if (!OwnerCharacter->GetMesh())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : OwnerCharacter has no mesh"), *FString(__FUNCTION__));

		return;
	}
	
	/*
	*	2025 03 06
	*	무기 충돌 감지를 위한 Collision 셋.
	*/
	if (!Mesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s : Mesh is null!"), *FString(__FUNCTION__));

		return;
	}
	
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->SetCollisionProfileName(TEXT("Weapon"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &UCAttachment::OnMeshOverlap);

	SpawnWeapon();
}

void UCAttachment::ComponentAttachTo(USkeletalMeshComponent* OwnerMesh, FName SocketName)
{
	if (!OwnerMesh)
	{
		if (!OwnerCharacter || !OwnerCharacter->GetMesh())
		{
			UE_LOG(LogTemp, Error, TEXT("%s : Failed to attch - OwnerCharacter or Mesh is null!"), *FString(__FUNCTION__));

			return;
		}

		OwnerMesh = OwnerCharacter->GetMesh();
	}

	if (!Mesh)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : Failed to attch - Attach Mesh is null!"), *FString(__FUNCTION__));

		return;
	}

	Mesh->AttachToComponent(OwnerMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), SocketName);
}

void UCAttachment::SpawnWeapon()
{
	if (!WeaponClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : WeaponClass is not set in Attachment Component."), *FString(__FUNCTION__));
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("%s : SpawnWeapon: World is null!"), *FString(__FUNCTION__));
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
		UE_LOG(LogTemp, Error, TEXT("%s : SpawnActorDeferred failed!"), *FString(__FUNCTION__));
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

void UCAttachment::SetDamage(float InDamage)
{
	Damage = InDamage;
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

void UCAttachment::ClearDamagedActors()
{
	DamagedActors.Empty();
}

void UCAttachment::SetDamageRatio(float InDamageRatio)
{
	DamageRatio = InDamageRatio;
}

void UCAttachment::OnMeshOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != GetOwner())
	{
		if (OtherActor)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%s : Overlap"), *FString(__FUNCTION__)));
		}

		if (DamagedActors.Contains(OtherActor))
			return;

		DamagedActors.Add(OtherActor);

		if (HitSound)
		{
			FVector SoundLocation = Mesh->GetComponentLocation();
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, SoundLocation, VolumeMultiplier, PitchMultiplier);
		}

		ACMonster* Monster = Cast<ACMonster>(OtherActor);
		FDamageEvent DamageEvent;
		APawn* Pawn = Cast<APawn>(GetOwner());

		Monster->ApplyDamage((Damage * DamageRatio), DamageEvent, Pawn->GetController(), GetOwner());
	}
}