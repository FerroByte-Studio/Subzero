// Copyright FerroByte Studio


#include "Character/SZ_BaseCharacter.h"

// Sets default values
ASZ_BaseCharacter::ASZ_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASZ_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASZ_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASZ_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

