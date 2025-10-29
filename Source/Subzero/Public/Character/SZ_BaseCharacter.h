// Copyright FerroByte Studio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SZ_BaseCharacter.generated.h"

UCLASS()
class SUBZERO_API ASZ_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASZ_BaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
