// Copyright FerroByte Studio


#include "Character/Player/SZ_PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SZ_StaminaComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ASZ_PlayerCharacter::ASZ_PlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void ASZ_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	ApplyWalkSpeed();

	if (StaminaComp)
	{
		StaminaComp->OnSprintStateChanged.AddDynamic(this, &ThisClass::OnSprintStateChanged);
	}
}

void ASZ_PlayerCharacter::OnSprintStateChanged(bool bIsSprinting)
{
	if (bIsSprinting) ApplySprintSpeed();
	else ApplyWalkSpeed();
}


void ASZ_PlayerCharacter::ApplyWalkSpeed()
{
	if (!GetCharacterMovement()) return;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ASZ_PlayerCharacter::ApplySprintSpeed()
{
	if (!GetCharacterMovement()) return;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

bool ASZ_PlayerCharacter::RequestJumpWithStamina()
{
	if (!StaminaComp) { Jump(); return true; }

	if (StaminaComp->TryConsume(JumpStaminaCost))
	{
		Jump();
		return true;
	}
	return false;
}


