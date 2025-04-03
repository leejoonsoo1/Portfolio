#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "CStateComponent.h"
#include "CPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UCStateComponent;
class UCMontagesComponent;
class UCAttachment;
class UEnhancedInputComponent;
struct FInputActionValue;

UCLASS()
class PORTFOLIO_API ACPlayerCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPlayerCharacter();

public:
	void BeginEvade();
	void EndEvade();

	void BeginEquipping();
	void EndEquipping();
	
	void UnEquip();
	void BeginUnEquipping();
	void EndUnEquipping();

	void BeginAction();
	void EndAction();

public:
	UFUNCTION()
	void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

	UFUNCTION()
	void OnWeaponTypeChanged(EWeaponType InPrevType, EWeaponType InNewType);

protected:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComp;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComp;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* EvadeAction;

	/** Sprint Inupt Action **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	/** Attack2 Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackTwoAction;

	/** UnEquipAction **/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* UnEquipAction;

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UCStateComponent* StateComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UCMontagesComponent* MontagesComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UCAttachment* AttachmentComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Evade(const FInputActionValue& value);
	void Sprint(const FInputActionValue& value);
	void Running(const FInputActionValue& value);
	void Attack(const FInputActionValue& value);
	void Charge(const FInputActionValue& value);
	void AttackTwo(const FInputActionValue& value);
	
	void HandleSprintStaminaDrain();
	bool UseStamina(float Amount);
	void TickRecoverStamina();
	void RecoverStamina(float DeltaTime);
	void ClearStaminaDelay();

	// bCanCombo를 False로 만드는 함수.
	// 접근지정자는 바뀔 수 있음.
	void ReleaseAttack(const FInputActionValue& value);
	void ReleaseAttackTwo(const FInputActionValue& value);

public:
	void Hitted();
	void Groggy();
	void BeDead();

protected:
	//virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Get Team ID
	virtual FGenericTeamId GetGenericTeamId() const override;

public:
	UFUNCTION(BlueprintCallable)
	void ApplyDamage(float InDamage, FDamageEvent const& InDamageEvent, AController* InEventInstigator, AActor* InDamageCauser);

	virtual float TakeDamage(float InDamageAmount, struct FDamageEvent const& InDamageEvent, class AController* InEventInstigator, class AActor* InDamageCauser) override;

public:
	FORCEINLINE class USpringArmComponent*	GetCameraBoom()		const { return SpringArmComp; }
	FORCEINLINE class UCameraComponent*		GetFollowCamera()	const { return CameraComp; }

	FORCEINLINE bool GetCharge() const { return bCharge; }

private:
	APlayerController* PC;

	//UEnhancedInputComponent* EnhancedInputComponent;

	// 안 쓰는 중
	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* EvadeMontage;

private:
	float DesiredEvadeDistance;
	float SprintSpeed;
	float RunningSpeed;
	float OriginWalkSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Team", meta = (AllowPrivateAccess = "true"))
	uint8 TeamID;

private:
	// 장비를 착용한 후에 반영되는 WalkSpeed.
	// Great Sword Class에서 받아올 예정.
	float EqWalkSpeed;
	bool bCharge;

private:
	UPROPERTY(EditAnywhere, Category = "Stats", meta = (ClampMin = "0"))
	float MaxHP;

	UPROPERTY(VisibleAnywhere, Category = "Stats")
	float CurrentHP;

	// Stamina (기력)
	UPROPERTY(EditAnywhere, Category = "Stats|Stamina", meta = (ClampMin = "0"))
	float MaxStamina;

	UPROPERTY(VisibleAnywhere, Category = "Stats|Stamina")
	float CurrentStamina;

	UPROPERTY(EditAnywhere, Category = "Stats|Stamina")
	float StaminaRecoverRate; // 초당 회복량

	UPROPERTY(EditAnywhere, Category = "Stats|Stamina")
	float StaminaRecoverDelay; // 행동 후 회복 대기 시간

	UPROPERTY(EditAnywhere, Category = "Status|Stamina", meta = (AllowPrivateAccess = "true"))
	float StaminaSprintDrainRate;

	UPROPERTY(EditAnywhere, Category = "Status|Stamina", meta = (AllowPrivateAccess = "true"))
	float StaminaEvadeDrainRate;

private:
	FTimerHandle SprintStaminaTimer;
	FTimerHandle StaminaRecoverTimer;
};