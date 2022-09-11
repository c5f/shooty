// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"

#include "Kismet/GameplayStatics.h"
#include "Tank.h"


//////////////////////
// unreal overrides

// Called every frame
void ATower::Tick(float DeltaTime)
{
	if (Target == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("tower has no target"));
		return;
	}

	auto TargetLocation = Target->GetActorLocation();
	auto Distance = FVector::Dist(GetActorLocation(), TargetLocation);
	if (false)  // todo: add range property
	{
		// out of range -- nothing to do
		return;
	}

	RotateTurret(TargetLocation);
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Target = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}
