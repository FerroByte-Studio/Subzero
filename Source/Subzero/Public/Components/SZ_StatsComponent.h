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
	float GetHealth() { return Health; }
	
	UFUNCTION(BlueprintCallable, Category="Subzero|Stats")
	float GetMaxHealth() { return MaxHealth; }
	
	UFUNCTION(BlueprintCallable, Category="Subzero|Stats")
	float GetHunger() { return Hunger; }
	
	UFUNCTION(BlueprintCallable, Category="Subzero|Stats")
	float GetMaxHunger() { return MaxHunger; }
	
	UFUNCTION(BlueprintCallable, Category="Subzero|Stats")
	float GetThirst() { return Thirst; }
	
	UFUNCTION(BlueprintCallable, Category="Subzero|Stats")
	float GetMaxThirst() { return MaxThirst; }

	UFUNCTION(BlueprintCallable, Category="Subzero|Stats")
	bool DecreaseThirst(float Amount);
	UFUNCTION(BlueprintCallable, Category="Subzero|Stats")
	bool DecreaseHunger(float Amount);
	

private:
	UPROPERTY(EditAnywhere, Category="Subzero|Stats")
	float Health = 100.f;

	UPROPERTY(EditAnywhere, Category="Subzero|Stats")
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, Category="Subzero|Stats")
	float Hunger = 100.f;

	UPROPERTY(EditAnywhere, Category="Subzero|Stats")
	float MaxHunger = 100.f;

	UPROPERTY(EditAnywhere, Category="Subzero|Stats")
	float Thirst = 100.f;

	UPROPERTY(EditAnywhere, Category="Subzero|Stats")
	float MaxThirst = 100.f;
};
