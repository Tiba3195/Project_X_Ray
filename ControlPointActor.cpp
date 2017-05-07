// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "ControlPointActor.h"
#include "GlobalGameState.h"


// Sets default values
AControlPointActor::AControlPointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// Create a camera and a visible object

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship VisibleComponent"));
	//OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	//CameraOne->SetupAttachment(RootComponent);
	//CameraOne->SetRelativeLocation(CameraOffset);
	//CameraOne->SetRelativeRotation(CameraRotation);

	OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AControlPointActor::BeginPlay()
{
	Super::BeginPlay();
	AGlobalGameState* GS;
	UWorld* World = GetWorld();
	if (World)
	{
		//this was a bug, was crashing the game because the gamestae was carrying over from runs.... very bad! needs to be a new one eash time!
		//if (!GS)
		//	{
		GS = Cast<AGlobalGameState>(World->GetGameState());		
		GS->AddControlPoint(this);
		//	}
	}
	
}

// Called every frame
void AControlPointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

