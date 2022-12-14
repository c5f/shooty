// Fill out your copyright notice in the Description page of Project Settings.
#include "ToonTanksGameMode.h"

#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"


void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);

    TowerCount = Towers.Num();

    HandleGameStart();
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
        if (--TowerCount == 0)
        {
            GameOver(true);
        }

        return;
    }

    // game over
    Tank->HandleDestruction();

    if (ToonTanksPlayerController == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("missing tank player controller"));
        return;
    }

    ToonTanksPlayerController->SetPlayerEnabledState(false);
    GameOver(false);
}

void AToonTanksGameMode::HandleGameStart()
{
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(
        UGameplayStatics::GetPlayerController(this, 0));

    StartGame();
    
    if (ToonTanksPlayerController == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("no player controller detected"));
        return;
    }

    ToonTanksPlayerController->SetPlayerEnabledState(false);
    FTimerHandle PlayerEnableTimerHandle;
    FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
        ToonTanksPlayerController,
        &AToonTanksPlayerController::SetPlayerEnabledState,
        true
    );

    GetWorldTimerManager().SetTimer(
        PlayerEnableTimerHandle,
        PlayerEnableTimerDelegate,
        StartDelaySeconds,
        false
    );
}
