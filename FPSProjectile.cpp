// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "FPSProjectile.h"


// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Use a sphere as a simple collision representation.
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

	// Set the sphere's collision radius.
	CollisionComponent->InitSphereRadius(8.0f);
	// Set the root component to be the collision component.
	RootComponent = CollisionComponent;

	// Use this component to drive this projectile's movement.
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 4000.0f;
	ProjectileMovementComponent->MaxSpeed = 4000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	TrailFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailFX"));
	TrailFX->SetupAttachment(CollisionComponent);
	// Die after 3 seconds.
	InitialLifeSpan = MaxAge;

	
}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	RegisterDelegate();
}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

		if (TrailFX)
		{
			TrailFX->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
			TrailFX->Activate();

			//UGameplayStatics::SpawnEmitterAtLocation(this, TrailFX, GetActorLocation(), GetActorRotation());

		}
}

// Function that initializes the projectile's velocity in the shoot direction.
void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}
// Function that is called when the projectile hits something.

void AFPSProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{


	if (OtherActor != this )
	{

		if (OtherComponent->IsSimulatingPhysics())
		{
			OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
		}
		if (OtherActor->bCanBeDamaged)
		{
			FRadialDamageEvent DamageType = FRadialDamageEvent();
			DamageType.Params.BaseDamage = 2000;
			DamageType.Params.DamageFalloff = 750;
			DamageType.Params.MinimumDamage = 350;
			DamageType.Params.OuterRadius = 200;
			DamageType.Origin = Hit.ImpactPoint;
			//DamageType.DamageTypeClass
			OtherActor->TakeDamage(2000, DamageType,GetOwner()->GetInstigatorController(),this);
		}
	}


	if (ImpactFX)
	{
	
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactFX, Hit.ImpactPoint, GetActorRotation());

	}

	ProjectileMovementComponent->Deactivate();
	LifeSpanExpired();

}

void AFPSProjectile::RegisterDelegate()
{
	if (CollisionComponent == nullptr)
		return;

	if (!CollisionComponent->OnComponentHit.IsAlreadyBound(this, &AFPSProjectile::OnHit))
	{
		CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);
	}

}

void AFPSProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (CollisionComponent == nullptr)
	{
		if (CollisionComponent->OnComponentHit.IsAlreadyBound(this, &AFPSProjectile::OnHit))
		{
			CollisionComponent->OnComponentHit.RemoveDynamic(this, &AFPSProjectile::OnHit);
		}
	}
	Super::EndPlay(EndPlayReason);

}



