// Copyright FerroByte Studio

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SZ_StaminaComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSprintStateChanged, bool, bIsSprinting);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChanged, float, NewStamina);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SUBZERO_API USZ_StaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USZ_StaminaComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stamina")
	float MaxStamina = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stamina")
	float SprintDrainPerSec = 15.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stamina")
	float RegenPerSec = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stamina")
	float RegenDelay = 1.0f; // seconds after last use

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stamina")
	float MinSprintStamina = 5.f; // need at least this to (re)start sprint

	UPROPERTY(BlueprintAssignable, Category="Stamina")
	FOnSprintStateChanged OnSprintStateChanged;

	UPROPERTY(BlueprintAssignable, Category="Stamina")
	FOnStaminaChanged OnStaminaChanged;

	UFUNCTION(BlueprintCallable, Category="Stamina")
	bool StartSprinting();          // returns true if sprint started

	UFUNCTION(BlueprintCallable, Category="Stamina")
	void StopSprinting();

	UFUNCTION(BlueprintCallable, Category="Stamina")
	bool TryConsume(float Amount);  // returns true if consumed

	UFUNCTION(BlueprintPure, Category="Stamina")
	float GetStamina() const { return CurrentStamina; }

	UFUNCTION(BlueprintCallable, Category="Stamina")
	float GetStaminaPercent() const { return MaxStamina > 0 ? CurrentStamina / MaxStamina : 0.f; }

	UFUNCTION(BlueprintPure, Category="Stamina")
	bool IsSprinting() const { return bIsSprinting; }

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void SetStamina(float NewValue);
	void BumpLastUseTime();

	float CurrentStamina = 0.f;
	bool bIsSprinting = false;
	double LastUseTime = 0.0; // for regen delay
};
