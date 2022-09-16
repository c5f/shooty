// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(
		TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	Mover = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Mover"));
	Mover->InitialSpeed = 400.f;
	Mover->MaxSpeed = 800.f;

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		FVector NormalImpulse,
		const FHitResult& HitResult)
{
	UE_LOG(
		LogTemp,
		Display,
		TEXT("projectile hit detected between %s and %s (%s)"),
		*HitComponent->GetName(),
		*OtherActor->GetName(),
		*OtherComponent->GetName());
}

//////////////////////
// unreal overrides

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
