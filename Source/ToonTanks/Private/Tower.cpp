// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"

#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Tank.h"


void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::FireTimerThunk()
{
	if (IsTargetInRange() && Target->bIsAlive)
	{
		ATower::FireProjectile();
	}
}

bool ATower::IsTargetInRange()
{
	if (Target == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("tower has no target"));
		return false;
	}

	return FVector::Dist(GetActorLocation(), Target->GetActorLocation()) <= FireRange;
}

//////////////////////
// unreal overrides

// Called every frame
void ATower::Tick(float DeltaTime)
{
	if (IsTargetInRange())
	{
		RotateTurret(Target->GetActorLocation());
	}
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Target = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(
		FireTimerHandle, this, &ATower::FireTimerThunk, FireRateInSeconds, true);
}
