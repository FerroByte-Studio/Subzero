// Copyright FerroByte Studio

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SZ_StatsComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SUBZERO_API USZ_StatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USZ_StatsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	/***************** Getters *******************/
	UFUNCTION(BlueprintCallable, Category="Subzero|Stats")
	float GetCurrentHealth() { return CurrentHealth; }
	
	UFUNCTION(BlueprintCallable, Category="Subzero|Stats")
	float GetMaxHealth() { return MaxHealth; }

	UFUNCTION(BlueprintCallable, Category="Subzero|Stats")
	float GetHealthPercent() { return CurrentHealth / MaxHealth; }
	
	UFUNCTION(BlueprintCallable, Category="Subzero|Stats")
	float GetCurrentHunger() { return CurrentHunger; }
	
	UFUNCTION(BlueprintCallable, Category="Subzero|Stats")
	float GetMaxHunger() { return MaxHunger; }

	UFUNCTION(BlueprintCallable, Category="Subzero|Stats")
	float GetHungerPercent() { return CurrentHunger / MaxHunger; }
	
	UFUNCTION(BlueprintCallable, Category="Subzero|Stats")
	float GetCurrentThirst() { return CurrentThirst; }
	
	UFUNCTION(BlueprintCallable, Category="Subzero|Stats")
	float GetMaxThirst() { return MaxThirst; }

	UFUNCTION(BlueprintCallable, Category="Subzero|Stats")
	float GetThirstPercent() { return CurrentThirst / MaxThirst; }

	UFUNCTION(BlueprintCallable, Category="Subzero|Stats")
	void DrainThirst(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category="Subzero|Stats")
	void DrainHunger(float DeltaTime);
	
	UFUNCTION(BlueprintCallable, Category="Subzero|Stats")
	void TakeDamage(float Amount);
	
	UFUNCTION(BlueprintCallable, Category="Subzero|Stats")
	bool IsDead() const { return CurrentHealth <= 0.f; }

	UPROPERTY(EditAnywhere, Category="Subzero|Stats|Damage Ramps")
	TObjectPtr<UCurveFloat> StarvationDamageCurve = nullptr;
	
	UPROPERTY(EditAnywhere, Category="Subzero|Stats|Damage Ramps")
	TObjectPtr<UCurveFloat> DehydrationDamageCurve = nullptr;

	UFUNCTION(BlueprintPure, Category="Subzero|Stats|Damage Ramps")
	float NormalizeBelowThreshold(float Percent, float ThresholdPercent) const;
	
	

protected:
	UPROPERTY(EditAnywhere, Category="Subzero|Stats")
	float CurrentHealth = 100.f;

	UPROPERTY(EditAnywhere, Category="Subzero|Stats")
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, Category="Subzero|Stats")
	float CurrentHunger = 100.f;

	UPROPERTY(EditAnywhere, Category="Subzero|Stats")
	float MaxHunger = 100.f;

	UPROPERTY(EditAnywhere, Category="Subzero|Stats")
	float CurrentThirst = 100.f;

	UPROPERTY(EditAnywhere, Category="Subzero|Stats")
	float MaxThirst = 100.f;

	UPROPERTY(EditAnywhere, Category="Subzero|Stats", meta=(ClampMin="0"))
	float ThirstDrainPerSecond = 0.1666f; // ~ 10 per minute

	UPROPERTY(EditAnywhere, Category="Subzero|Stats", meta=(ClampMin="0"))
	float HungerDrainPerSecond = 0.0833f; // ~ 5 per minute
	
	UPROPERTY(EditAnywhere, Category="Subzero|Stats", meta=(ClampMin="0", ClampMax="1"))
	float StarvingThresholdPercent = 0.25f; // 25%

	UPROPERTY(EditAnywhere, Category="Subzero|Stats", meta=(ClampMin="0", ClampMax="1"))
	float DehydratedThresholdPercent = 0.15f; // 15%

	UPROPERTY(EditAnywhere, Category="Subzero|Stats", meta=(ClampMin="0"))
	float StarvingDamagePerSecond = 1.0f;

	UPROPERTY(EditAnywhere, Category="Subzero|Stats", meta=(ClampMin="0"))
	float DehydratedDamagePerSecond = 1.5f;
	
};
