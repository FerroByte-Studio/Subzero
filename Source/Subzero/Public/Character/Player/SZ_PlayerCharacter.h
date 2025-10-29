// Copyright FerroByte Studio

#pragma once

#include "CoreMinimal.h"
#include "Character/SZ_BaseCharacter.h"
#include "SZ_PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SUBZERO_API ASZ_PlayerCharacter : public ASZ_BaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASZ_PlayerCharacter();

private:
	UPROPERTY(EditDefaultsOnly, Category="SubZero|Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(EditDefaultsOnly, Category="SubZero|Camera")
	TObjectPtr<UCameraComponent> FollowCamera;
};
