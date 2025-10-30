// Copyright FerroByte Studio


#include "Character/Player/SZ_PlayerController.h"
#include "Character/Player/SZ_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Character/Player/SZ_PlayerCharacter.h"
#include "Components/SZ_StaminaComponent.h"
#include "GameFramework/Character.h"

void ASZ_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(InputSubsystem)) return;
	
	for (UInputMappingContext* Context : InputMappingContexts)
	{
		InputSubsystem->AddMappingContext(Context, 0);
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent)) return;

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ThisClass::OnSprintpStarted);
	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ThisClass::OnSprintCompleted);
	EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &ASZ_PlayerController::Reload);
}


void ASZ_PlayerController::Reload()
{
	ASZ_PlayerCharacter* Char = Cast<ASZ_PlayerCharacter>(GetPawn());

	Char->Reload();
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Playing Reload Animation"));
}

void ASZ_PlayerController::Jump()
{
	if (!IsValid(GetCharacter())) return;

	GetCharacter()->Jump();
}

void ASZ_PlayerController::StopJumping()
{
	if (!IsValid(GetCharacter())) return;

	GetCharacter()->StopJumping();
}

void ASZ_PlayerController::Move(const FInputActionValue& Value)
{
	if (!IsValid(GetPawn())) return;

	const FVector2D MovementVector = Value.Get<FVector2D>();

	// Find which way is forward
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetPawn()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetPawn()->AddMovementInput(RightDirection, MovementVector.X);
}

void ASZ_PlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void ASZ_PlayerController::OnSprintpStarted(const FInputActionValue& Value)
{
	if (ASZ_PlayerCharacter* C = GetSZCharacter())
	{
		if (C->StaminaComp)
		{
			const bool bStarted = C->StaminaComp->StartSprinting();
		}
	}
}

void ASZ_PlayerController::OnSprintCompleted(const FInputActionValue& Value)
{
	if (ASZ_PlayerCharacter* C = GetSZCharacter())
	{
		if (C->StaminaComp)
		{
			C->StaminaComp->StopSprinting();
		}
	}
}

class ASZ_PlayerCharacter* ASZ_PlayerController::GetSZCharacter() const
{
	return Cast<ASZ_PlayerCharacter>(GetPawn());
}

