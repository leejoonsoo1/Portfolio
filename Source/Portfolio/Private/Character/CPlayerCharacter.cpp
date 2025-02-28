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
}

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

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ACPlayerCharacter::Evade"));
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

	}
}

void ACPlayerCharacter::EndEvade()
{
	StateComp->SetIdleMode();
}

void ACPlayerCharacter::BeginEquipping()
{
	if (MontagesComp && !StateComp->IsUnarmedMode())
	{
		UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();

		MontagesComp->PlayEquipping();
	}
}

void ACPlayerCharacter::EndEquipping()
{
	StateComp->SetIdleMode();
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void ACPlayerCharacter::BeginUnEquipping()
{
	if (MontagesComp && !StateComp->IsUnarmedMode())
	{
		MontagesComp->PlayUnEquipping();
	}
}

void ACPlayerCharacter::EndUnEquipping()
{
	StateComp->SetUnarmedMode();
	StateComp->SetIdleMode();
	
	GetCharacterMovement()->MaxWalkSpeed = OriginWalkSpeed;
}

void ACPlayerCharacter::Sprint(const FInputActionValue& value)
{
	if (StateComp->IsEquipMode()) return;

	if (!StateComp->IsUnEquipMode() && !StateComp->IsUnarmedMode())
	{
		StateComp->SetUnEquipMode();
	}

	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void ACPlayerCharacter::Running(const FInputActionValue& value)
{
	GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
}

void ACPlayerCharacter::Attack(const FInputActionValue& value)
{
	if (StateComp->IsUnEquipMode()) return;

	GetCharacterMovement()->MaxWalkSpeed = EqWalkSpeed;

	if (!StateComp->IsEquipMode() && StateComp->IsUnarmedMode())
	{
		GetCharacterMovement()->SetMovementMode(MOVE_None);
		StateComp->SetGreatSwordMode();
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

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		// Attack
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Attack);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Ongoing, this, &ACPlayerCharacter::Attack2);

		// Jumping
		EnhancedInputComponent->BindAction(EvadeAction, ETriggerEvent::Triggered, this,	&ACPlayerCharacter::Evade);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,	&ACPlayerCharacter::Move);

		// Sprint
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Sprint);
		
		// Running 
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ACPlayerCharacter::Running);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this,	&ACPlayerCharacter::Look);
	}
	else
	{
		//UE_LOG(LogTemplate, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}