// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "HardPointAttachment.h"

UHardPointAttachment::UHardPointAttachment(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	PrimaryComponentTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Vis Box"));
	Box->bHiddenInGame = true;
	Box->SetupAttachment(this);
}
// Sets default values for this component's properties
UHardPointAttachment::UHardPointAttachment()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Vis Box"));
	Box->bHiddenInGame = true;
	Box->SetupAttachment(this);
	// ...
}


// Called when the game starts
void UHardPointAttachment::BeginPlay()
{
	Super::BeginPlay();


	
}


// Called every frame
void UHardPointAttachment::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

