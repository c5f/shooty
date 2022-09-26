// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"


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

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(
		TEXT("TrailParticles"));
	TrailParticles->SetupAttachment(RootComponent);

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		FVector NormalImpulse,
		const FHitResult& HitResult)
{
	if (HitParticles == nullptr)
	{
		// fixme: this type of runtime check seems egregious
		UE_LOG(LogTemp, Warning, TEXT("no hit particles configured"));
	}
	else
	{ 
		UGameplayStatics::SpawnEmitterAtLocation(
			this, HitParticles, GetActorLocation(), GetActorRotation());
	}

	auto MyOwner = GetOwner();
	if (MyOwner == nullptr || OtherActor == nullptr)
	{
		// missing necessary information to apply damage
		return;
	}

	// extract `bool AProjectile::IsFriendlyFire(OtherActor);` if necessary
	if ((OtherActor == this || OtherActor == MyOwner) && !IsFriendlyFireEnabled)
	{
		return;
	}

	UGameplayStatics::PlaySoundAtLocation(
		this, HitSound, GetActorLocation());
	UGameplayStatics::ApplyDamage(
		OtherActor,
		Damage,
		MyOwner->GetInstigatorController(),
		this,
		UDamageType::StaticClass());
	Destroy();
}

//////////////////////
// unreal overrides

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySoundAtLocation(
		this, LaunchSound, GetActorLocation());
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
