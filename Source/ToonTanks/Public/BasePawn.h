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

	UPROPERTY(EditAnywhere, Category = "Shooty", BlueprintReadWrite)
	float Speed = 400.0;

	UPROPERTY(EditAnywhere, Category = "Shooty")
	class UCapsuleComponent* Collider;

	UPROPERTY(EditAnywhere, Category = "Shooty")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, Category = "Shooty")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditAnywhere, Category = "Shooty")
	USceneComponent* ProjectileSpawnPoint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(
		class UInputComponent* PlayerInputComponent
	) override;
};