// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "TurretComponent.h"


UTurretComponent::UTurretComponent(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	VisBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Vis Box"));
	VisBox->bHiddenInGame = true;
	VisBox->SetupAttachment(this);
}

// Sets default values
UTurretComponent::UTurretComponent()
{
	VisBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Vis Box"));
	VisBox->bHiddenInGame = true;
	VisBox->SetupAttachment(this);
}


void UTurretComponent::BeginPlay()
{
	Super::BeginPlay();
	RegisterDelegate();
}

void UTurretComponent::TickEX(float DeltaTime)
{

}

void UTurretComponent::RegisterDelegate()
{
	if (Box == nullptr)
		return;

	if (!Box->OnActorBeginOverlap.IsAlreadyBound(this, &UTurretComponent::OnBeginTriggerOverlap))
	{
		Box->OnActorBeginOverlap.AddDynamic(this, &UTurretComponent::OnBeginTriggerOverlap);
	}
}

void UTurretComponent::OnBeginTriggerOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	// This gets called when an actor begins to overlap with the current trigger volume
	if (GEngine)
	{
		// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Inside Turret Trigger Volume"));
	}
}

void UTurretComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Box == nullptr)
		return;
	if (Box->OnActorBeginOverlap.IsAlreadyBound(this, &UTurretComponent::OnBeginTriggerOverlap))
	{
		Box->OnActorBeginOverlap.RemoveDynamic(this, &UTurretComponent::OnBeginTriggerOverlap);
	}
	Super::EndPlay(EndPlayReason);
}
