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

/*
*	2025. 03. 03
*	캐릭터의 우클릭 공격 구현.
*	좌클릭 차징 동작은 아직 구상중, 우클릭의 세 단계
*	베어 넘기기 -> 태클 -> 뛰어들어 베어 넘기기까지 구현 예정.
*	가능하면, 회피 동작도 추가 예정.
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

	// 키 입력을 확인하고 여러 키 조합을 판단하기 위해 추가된 코드
	PC = Cast<APlayerController>(GetController());
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
	if (!PC) return;

	if (PC->IsInputKeyDown(EKeys::Tab) && !StateComp->IsUnarmedMode() && !StateComp->IsUnEquipMode())
	{
		StateComp->SetUnEquipMode();
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
		MontagesComp->PlayEquipping(TEXT("Equip"), StateComp->GetEWeaponType());
	}
}

void ACPlayerCharacter::EndEquipping()
{
	StateComp->SetIdleMode();

	/*
	*	2025 03 04
	*	여기서 실행되면 안 됨. 
	*	OnEWeaponChanged에서 실행됐어야할 함수.
	*/
	StateComp->SetGreatSwordMode();
}

void ACPlayerCharacter::UnEquip()
{
	if (StateComp->IsEquipMode()) return;
	if (StateComp->IsActionMode()) return;

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
	GetCharacterMovement()->MaxWalkSpeed = OriginWalkSpeed;

	StateComp->SetIdleMode();
	StateComp->SetUnarmedMode();
}

void ACPlayerCharacter::Sprint(const FInputActionValue& value)
{
	if (StateComp->IsIdleMode() && StateComp->IsUnarmedMode() && !StateComp->IsUnEquipMode())
	{
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
	if (StateComp->IsEquipMode()) return;
	if (StateComp->IsUnEquipMode()) return;
	if (StateComp->IsActionMode()) return;

	if (!PC) return;

	if (PC->IsInputKeyDown(EKeys::LeftShift))
	{
		if (MontagesComp)
		{
			StateComp->SetEquipMode();
			MontagesComp->PlayEquipping(TEXT("MovingEquip"), StateComp->GetEWeaponType());
			return;
		}
	}

	if (StateComp->IsUnarmedMode())
	{
		StateComp->SetEquipMode();
	}
}


// 아직 사용안함
void ACPlayerCharacter::ReleaseAttack(const FInputActionValue& value)
{
}


void ACPlayerCharacter::AttackTwo(const FInputActionValue& value)
{
	if (!StateComp->IsActionMode() && !StateComp->IsUnarmedMode())
	{
		if (MontagesComp) 
		{
			StateComp->SetActionMode();
			MontagesComp->PlayAttack(TEXT("CleavingArc"), StateComp->GetEWeaponType());
		}
	}
}

// 삭제 예정
void ACPlayerCharacter::ReleaseAttackTwo(const FInputActionValue& value)
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

// 기능 없음.
void ACPlayerCharacter::OnWeaponTypeChanged(EWeaponType InPrevType, EWeaponType InNewType)
{
	switch (InNewType)
	{
	case EWeaponType::Unarmed:
		break;
	case EWeaponType::GreatSword:

		// EquipWalkSpeed
		GetCharacterMovement()->MaxWalkSpeed = EqWalkSpeed;

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
		//EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, this, &);
		//EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Ongoiong, this, &);

		EnhancedInputComponent->BindAction(AttackTwoAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::AttackTwo);
		//EnhancedInputComponent->BindAction(AttackTwoAction, ETriggerEvent::Completed, this, &);

		// Jumping
		EnhancedInputComponent->BindAction(EvadeAction, ETriggerEvent::Triggered, this,	&ACPlayerCharacter::Evade);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,	&ACPlayerCharacter::Move);

		// Sprint
		EnhancedInputComponent->BindAction(UnEquipAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::UnEquip);
		
		// Sprint, Running
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Ongoing, this, &ACPlayerCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ACPlayerCharacter::Running);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this,	&ACPlayerCharacter::Look);
	}
	else
	{
		//UE_LOG(LogTemplate, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}