// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"


UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:

	ABasePawn();

	void HandleDestruction();

protected:

	void RotateTurret(FVector Target);

	void FireProjectile();

private:

	UPROPERTY(EditAnywhere, Category = "Shooty")
	class UCapsuleComponent* Collider;

	UPROPERTY(EditAnywhere, Category = "Shooty")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, Category = "Shooty")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditAnywhere, Category = "Shooty")
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Shooty")
	float TurretRotationInterpolationSpeed = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "Shooty")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Shooty")
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Shooty")
	class USoundBase* DeathSound;
};
