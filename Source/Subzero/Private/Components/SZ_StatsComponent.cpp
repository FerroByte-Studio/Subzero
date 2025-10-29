// Copyright FerroByte Studio


#include "Components/SZ_StatsComponent.h"


// Sets default values for this component's properties
USZ_StatsComponent::USZ_StatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USZ_StatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USZ_StatsComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool USZ_StatsComponent::DecreaseThirst(float Amount)
{
	if (Amount <= 0.f || Thirst < Amount)
	{
		return false;
	}

	Thirst -= Amount;
	return true;
}

bool USZ_StatsComponent::DecreaseHunger(float Amount)
{
	if (Amount <= 0.f || Hunger < Amount)
	{
		return false;
	}

	Hunger -= Amount;
	return true;
}


