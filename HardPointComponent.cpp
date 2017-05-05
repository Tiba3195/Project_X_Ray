// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"

#include "HardPointComponent.h"


UClass* TurretHardPointClass;

UHardPointComponent::UHardPointComponent(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	static ConstructorHelpers::FClassFinder<ATurretHardPoint> TheTurret(TEXT("/Game/BP_TurretHardPoint.BP_TurretHardPoint_C"));
	if (TheTurret.Class != NULL)
	{
		TurretHardPointClass = TheTurret.Class;
	}
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Vis Box"));
	Box->bHiddenInGame = true;
	Box->SetupAttachment(this);

}

// Sets default values
UHardPointComponent::UHardPointComponent()
{
	static ConstructorHelpers::FClassFinder<ATurretHardPoint> TheTurret(TEXT("/Game/BP_TurretHardPoint.BP_TurretHardPoint_C"));
	if (TheTurret.Class != NULL)
	{
		TurretHardPointClass = TheTurret.Class;
	}
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Vis Box"));
	Box->bHiddenInGame = true;
	Box->SetupAttachment(this);
}


void UHardPointComponent::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		ATurretHardPoint* NewTurret = World->SpawnActor<ATurretHardPoint>(TurretHardPointClass, RelativeLocation, FRotator(0.0f, 0.0f, 0.0f), SpawnParams);

		FVector Neloc = NewTurret->GetActorLocation() + NewTurret->HardPointAttachment->RelativeLocation;
		NewTurret->SetActorLocation(Neloc);
	}
}