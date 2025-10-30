// Copyright FerroByte Studio


#include "Components/SZ_StaminaComponent.h"


// Sets default values for this component's properties
USZ_StaminaComponent::USZ_StaminaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void USZ_StaminaComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentStamina = MaxStamina;
	LastUseTime = 0.0f;
}

void USZ_StaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bIsSprinting && SprintDrainPerSec > 0.f)
	{
		const float Drain = SprintDrainPerSec + DeltaTime;
		if (TryConsume(Drain))
		{
			// ran out mid-spring
			bIsSprinting = false;
			OnSprintStateChanged.Broadcast(false);
		}
	}
}


bool USZ_StaminaComponent::StartSprinting()
{
	if (bIsSprinting) return true;
	if (CurrentStamina < MinSprintStamina) return false;

	bIsSprinting = true;
	OnSprintStateChanged.Broadcast(true);
	return true;
}

void USZ_StaminaComponent::StopSprinting()
{
	if (!bIsSprinting) return;
	bIsSprinting = false;
	OnSprintStateChanged.Broadcast(false);
}

bool USZ_StaminaComponent::TryConsume(float Amount)
{
	if (Amount <= 0.f) return true;

	if (CurrentStamina >= Amount)
	{
		SetStamina(CurrentStamina - Amount);
		BumpLastUseTime();
		return true;
	}

	// consume whats left, clamp to 0
	if (CurrentStamina > 0.f)
	{
		SetStamina(0.f);
		BumpLastUseTime();
	}
	return false;
}

void USZ_StaminaComponent::SetStamina(float NewValue)
{
	const float Clamped = FMath::Clamp(NewValue, 0.f, MaxStamina);
	if (!FMath::IsNearlyEqual(Clamped, CurrentStamina))
	{
		CurrentStamina = Clamped;
		OnStaminaChanged.Broadcast(CurrentStamina);
	}
}

void USZ_StaminaComponent::BumpLastUseTime()
{
	if (UWorld* World = GetWorld())
	{
		LastUseTime = World->GetTimeSeconds();
	}
}

