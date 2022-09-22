// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"

#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	// You can turn these features off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::DamageTaken(
	AActor* DamagedActor,
	float Damage,
	const UDamageType* DamageType,
	class AController* Instigator,
	AActor* DamageCauser)
{
	if (Damage <= 0.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("invalid damage value received"));
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("applying %f damage to %s"), Damage, *DamagedActor->GetName());

	Health -= Damage;

	if (Health > 0.f)
	{
		return;
	}

	if (GameMode == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("game mode was unset"));
		return;
	}

	GameMode->ActorDied(DamagedActor);
}

//////////////////////
// unreal overrides

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));

	Health = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
