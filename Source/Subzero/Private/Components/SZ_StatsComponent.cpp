// Copyright FerroByte Studio


#include "Components/SZ_StatsComponent.h"


USZ_StatsComponent::USZ_StatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void USZ_StatsComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	CurrentThirst = MaxThirst;
	CurrentHunger = MaxHunger;

	UE_LOG(LogTemp, Log, TEXT("HungerDrain/s=%.4f, ThirstDrain/s=%.4f"),
	HungerDrainPerSecond, ThirstDrainPerSecond);

	
}

void USZ_StatsComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DrainThirst(DeltaTime);
	DrainHunger(DeltaTime);

	const float ThirstPct = GetThirstPercent();
	const float HungerPct = GetHungerPercent();

	float DamagePerSecond = 0.f;

	if (ThirstPct <= DehydratedThresholdPercent)
	{
		float t = NormalizeBelowThreshold(ThirstPct, DehydratedThresholdPercent);
		float mult = DehydrationDamageCurve ? DehydrationDamageCurve->GetFloatValue(t) : t;
		DamagePerSecond += DehydratedDamagePerSecond * mult;
	}

	if (HungerPct <= StarvingThresholdPercent)
	{
		float t = NormalizeBelowThreshold(HungerPct, StarvingThresholdPercent);
		float mult = StarvationDamageCurve ? StarvationDamageCurve->GetFloatValue(t) : t;
		DamagePerSecond += StarvingDamagePerSecond * mult;
	}

	if (DamagePerSecond > 0.f)
	{
		TakeDamage(DamagePerSecond * DeltaTime);
	}

	UE_LOG(LogTemp, Log, TEXT("Hunger: %.4f, Thirst: %.4f, Health: %.4f"), CurrentHunger, CurrentThirst, CurrentHealth);
}


void USZ_StatsComponent::DrainThirst(float DeltaTime)
{
	if (ThirstDrainPerSecond <= 0.f) return;
	CurrentThirst = FMath::Clamp(CurrentThirst - ThirstDrainPerSecond * DeltaTime, 0.f, MaxThirst);
}

void USZ_StatsComponent::DrainHunger(float DeltaTime)
{
	if (HungerDrainPerSecond <= 0.f) return;
	CurrentHunger = FMath::Clamp(CurrentHunger - HungerDrainPerSecond * DeltaTime, 0.f, MaxHunger);
}

void USZ_StatsComponent::TakeDamage(float Amount)
{
	if (Amount <= 0 || IsDead()) return;

	CurrentHealth = FMath::Clamp(CurrentHealth - Amount, 0.f, MaxHealth);

	if (IsDead())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has died."), *GetOwner()->GetName());
	}
		
}

float USZ_StatsComponent::NormalizeBelowThreshold(float Percent, float ThresholdPercent) const
{
	// Percent and ThresholdPercent are 0..1 (e.g., 0.25f)
	if (ThresholdPercent <= 0.f) return 1.f; // degenerate: all below
	// t = 0 at threshold (no damage), t = 1 at zero (max damage)
	const float t = (ThresholdPercent - Percent) / ThresholdPercent;
	return FMath::Clamp(t, 0.f, 1.f);
}


