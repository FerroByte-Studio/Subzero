// Copyright FerroByte Studio

#pragma once

#include "CoreMinimal.h"
#include "Character/SZ_BaseCharacter.h"
#include "SZ_PlayerCharacter.generated.h"

class USZ_StaminaComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SUBZERO_API ASZ_PlayerCharacter : public ASZ_BaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASZ_PlayerCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Subzero|Movement")
	float WalkSpeed = 450.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Subzero|Movement")
	float SprintSpeed = 700.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Subzero|Movement")
	float JumpStaminaCost = 15.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Subzero|Components")
	USZ_StaminaComponent* StaminaComp;

	bool RequestJumpWithStamina();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSprintStateChanged(bool bIsSprinting);

	void ApplyWalkSpeed();
	void ApplySprintSpeed();

private:
	UPROPERTY(EditDefaultsOnly, Category="SubZero|Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(EditDefaultsOnly, Category="SubZero|Camera")
	TObjectPtr<UCameraComponent> FollowCamera;
};
