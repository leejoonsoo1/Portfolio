#include "CPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CStateComponent.h"
#include "CMontagesComponent.h"
#include "InputActionValue.h"
#include "Engine/Engine.h"
#include "CAttachment.h"

/*
*  2025. 03. 02 AM 04:03
*  이동 중 UnEquip 함수 호출 시 원인 불명의 버그 발생.
*  AnimNotify_UnEquip에서 EndUnEquipping 함수가 예상보다 비정상적으로 빠르게 호출됨.
*  Move에서 UnEquipping을 호출하는 방식이 아니라, UnEquip 함수에서 이동 상태를 먼저 확인하는 것이 필요할 수도 있음.
*/

// Sets default values
ACPlayerCharacter::ACPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	SpringArmComp->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	CameraComp->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Montage Comp
	MontagesComp = CreateDefaultSubobject<UCMontagesComponent>("MontagesComp");

	// State Comp
	StateComp = CreateDefaultSubobject<UCStateComponent>("StateComp");

	// Attachment Comp
	AttachmentComp = CreateDefaultSubobject<UCAttachment>("AttachComp");

	// Status
	OriginWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	SprintSpeed = GetCharacterMovement()->MaxWalkSpeed + 350.f;
	RunningSpeed = GetCharacterMovement()->MaxWalkSpeed;

	// Great Sword DataTable에서 받아올 예정.
	EqWalkSpeed = OriginWalkSpeed - 200.f;
}

// Called when the game starts or when spawned
void ACPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// On StateType Changed
	if (StateComp)
	{
		StateComp->OnStateTypeChanged.AddDynamic(this, &ACPlayerCharacter::OnStateTypeChanged);
		StateComp->OnWeaponTypeChanged.AddDynamic(this, &ACPlayerCharacter::OnWeaponTypeChanged);
	}
}

void ACPlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}

	/*
		*	2025.03.02 AM 03:31
		*	Move에 사용되는 W, S, A, D 키와 조합되는 애니메이션이 많아 이곳에서 처리함.
		*	GetBoundAction을 사용해 Sprint의 Get<bool>() 값을 가져오는 것이 어려웠음.
		*	대안으로 PlayerController의 IsInputKeyDown()을 활용하여 현재 눌린 키를 직접 반환받아 조합하여 사용.
	 */
	APlayerController* PC = Cast<APlayerController>(GetController());

	if (PC->IsInputKeyDown(EKeys::LeftShift) && !StateComp->IsUnarmedMode() && !StateComp->IsUnEquipMode())
	{
		MontagesComp->PlayUnEquipping(TEXT("MovingUnEquip"), StateComp->GetEWeaponType());
	}
}

// 어떤함수인지 모름
void ACPlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACPlayerCharacter::Evade(const FInputActionValue& value)
{
	if (StateComp->IsIdleMode())
	{
		StateComp->SetEvadeMode();
	}
}

void ACPlayerCharacter::BeginEvade()
{
	if (MontagesComp && StateComp->IsUnarmedMode())
	{
		MontagesComp->PlayEvade();
	}
	else
	{
		MontagesComp->PlayEvade(TEXT("Evade"), StateComp->GetEWeaponType());
	}
}

void ACPlayerCharacter::EndEvade()
{
	StateComp->SetIdleMode();
}

void ACPlayerCharacter::BeginEquipping()
{
	if (MontagesComp)
	{
		UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();

		MontagesComp->PlayEquipping(TEXT("Equip"), StateComp->GetEWeaponType());
	}
}

void ACPlayerCharacter::EndEquipping()
{
	StateComp->SetIdleMode();
	StateComp->SetGreatSwordMode();
}

void ACPlayerCharacter::UnEquip()
{
	if (StateComp->IsEquipMode()) return;



	if (!StateComp->IsUnEquipMode() && !StateComp->IsUnarmedMode())
	{
		StateComp->SetUnEquipMode();
	}
}

void ACPlayerCharacter::BeginUnEquipping()
{
	if (MontagesComp)
	{
		MontagesComp->PlayUnEquipping(TEXT("UnEquip"), StateComp->GetEWeaponType());
	}
}

void ACPlayerCharacter::EndUnEquipping()
{
	//GetCharacterMovement()->MaxWalkSpeed = OriginWalkSpeed;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ACPlayerCharacter::EndEquipping() 1"));
	}

	StateComp->SetIdleMode();
	StateComp->SetUnarmedMode();
}

void ACPlayerCharacter::Sprint(const FInputActionValue& value)
{
	if (StateComp->IsIdleMode() && StateComp->IsUnarmedMode() && !StateComp->IsUnEquipMode())
	{
		
		if (GEngine)
		{
			EWeaponType WeaponType = StateComp->GetEWeaponType();

			FString EnumString = StaticEnum<EWeaponType>()->GetNameByValue((int64)WeaponType).ToString();

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, EnumString);
		}

		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void ACPlayerCharacter::Running(const FInputActionValue& value)
{
	if (StateComp->IsIdleMode() && StateComp->IsUnarmedMode() && !StateComp->IsUnEquipMode())
	{
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	}
}

void ACPlayerCharacter::Attack(const FInputActionValue& value)
{
	if (StateComp->IsUnEquipMode()) return;
	
	// EquipWalkSpeed
	GetCharacterMovement()->MaxWalkSpeed = EqWalkSpeed;

	if (StateComp->IsUnarmedMode())
	{
		StateComp->SetEquipMode();
	}
}

void ACPlayerCharacter::Attack2(const FInputActionValue& value)
{

}

void ACPlayerCharacter::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
	case EStateType::Idle:
		break;

	case EStateType::Evade:
		BeginEvade();
		break;

	case EStateType::Equip:
		BeginEquipping();
		break;

	case EStateType::UnEquip:
		BeginUnEquipping();
		break;

	default:
		break;
	}
}

void ACPlayerCharacter::OnWeaponTypeChanged(EWeaponType InPrevType, EWeaponType InNewType)
{
	switch (InNewType)
	{
	case EWeaponType::Unarmed:
		break;

	case EWeaponType::GreatSword:
		break;

	default:
		break;
	}
}

// Called to bind functionality to input
void ACPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// Set up action bindings
	if (EnhancedInputComponent)
	{
		// Attack
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Attack);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Ongoing, this, &ACPlayerCharacter::Attack2);

		// Jumping
		EnhancedInputComponent->BindAction(EvadeAction, ETriggerEvent::Triggered, this,	&ACPlayerCharacter::Evade);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,	&ACPlayerCharacter::Move);

		// Sprint
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::UnEquip);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Ongoing, this, &ACPlayerCharacter::Sprint);
		
		// Running 
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Canceled, this, &ACPlayerCharacter::Running);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this,	&ACPlayerCharacter::Look);
	}
	else
	{
		//UE_LOG(LogTemplate, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}