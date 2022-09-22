// Fill out your copyright notice in the Description page of Project Settings.
#include "ToonTanksGameMode.h"

#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"


void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    if (DeadActor != Tank)
    {
        ATower* DeadTower = Cast<ATower>(DeadActor);
        if (DeadTower == nullptr)
        {
            UE_LOG(LogTemp, Display, TEXT("unable to cast dead actor to tower"));
            return;
        }
        
        DeadTower->HandleDestruction();
        return;
    }

    // game over
    Tank->HandleDestruction();

    if (Tank->GetPlayerController() == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("missing tank player controller"));
        return;
    }

    Tank->DisableInput(Cast<APlayerController>(Tank->GetController()));
    Tank->GetPlayerController()->bShowMouseCursor = false;
}
