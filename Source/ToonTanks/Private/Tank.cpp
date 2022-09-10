// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}
void ATank::Move(float Value)
{
	AddActorLocalOffset(FVector(
		Value * UGameplayStatics::GetWorldDeltaSeconds(this) * Speed, 0.f, 0.f),
		true
	);
}

void ATank::Turn(float Value)
{
	AddActorLocalRotation(
		FRotator(0.f, Value, 0.f) * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnRate,
		true
	);
}

//////////////////////
// unreal overrides

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Controller != nullptr)
	{
		FHitResult Hit;
		if (!Controller->GetHitResultUnderCursor(ECC_Visibility, false, Hit))
		{
			return;
		}

		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 10.0, 20, FColor::Orange, false);

		RotateTurret(Hit.ImpactPoint);
	}
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	Controller = Cast<APlayerController>(GetController());
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}
