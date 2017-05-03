// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "GridNodeActor.h"


AGridNodeActor::AGridNodeActor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	NodeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Node Mesh"));
	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	NodeMesh->SetupAttachment(RootComponent);
}
static bool Hidden = true;

// Sets default values
AGridNodeActor::AGridNodeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	NodeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Node Mesh"));
	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	NodeMesh->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AGridNodeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridNodeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Hidden)
	{
		NodeMesh->SetVisibility(false);
	}
	else
	{
		NodeMesh->SetVisibility(true);
	}

}

void AGridNodeActor::ToggleVisibilty()
{
	if (Hidden)
	{
		Hidden = false;
	}
	else
	{
		Hidden = true;
	}
}

