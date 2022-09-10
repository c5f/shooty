// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:
	ATank();

	UPROPERTY(EditAnywhere, Category = "Shooty", BlueprintReadWrite)
	float Speed = 400.0;

	UPROPERTY(EditAnywhere, Category = "Shooty", BlueprintReadWrite)
	float TurnRate = 90.0;

private:
	UPROPERTY(EditAnywhere, Category = "Shooty")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "Shooty")
	class UCameraComponent* Camera;

	void Move(float Value);

	void Turn(float Value);

	class APlayerController* Controller;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(
		class UInputComponent* PlayerInputComponent
	) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
