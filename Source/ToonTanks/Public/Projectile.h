// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Shooty")
	class UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Shooty")
	class UProjectileMovementComponent* Mover;

private:
	UPROPERTY(EditAnywhere, Category = "Shooty")
	bool IsFriendlyFireEnabled = false;

	UPROPERTY(EditAnywhere, Category = "Shooty")
	float Damage = 50.f;

	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		FVector NormalImpulse,
		const FHitResult& HitResult);

	UPROPERTY(EditAnywhere, Category = "Shooty")
	class UParticleSystem* HitParticles;

	UPROPERTY(VisibleAnywhere, Category = "Shooty")
	class UParticleSystemComponent* TrailParticles;

	UPROPERTY(EditAnywhere, Category = "Shooty")
	class USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Shooty")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Shooty")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;
};
