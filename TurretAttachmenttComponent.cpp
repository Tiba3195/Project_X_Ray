// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "TurretAttachmenttComponent.h"


// Sets default values for this component's properties
UTurretAttachmenttComponent::UTurretAttachmenttComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship VisibleComponent"));
	//OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	//CameraOne->SetupAttachment(RootComponent);
	//CameraOne->SetRelativeLocation(CameraOffset);
	//CameraOne->SetRelativeRotation(CameraRotation);
//	OurVisibleComponent->SetupAttachment(GetAttachParent());

	//static ConstructorHelpers::FClassFinder<ATurretActor> TheTurretBod(TEXT("/Game/BP_TurretActor.BP_TurretActor_C"));
	//if (TheTurretBod.Class != NULL)
	//{
		//Turret = TheTurretBod.Class.GetDefaultObject();
		//Turret->SetActorLocation(RelativeLocation);
	//	Turret->SetActorHiddenInGame(false);
		//Turret->Par(this);
		//Turret->set
	//}
	// ...
}


// Called when the game starts
void UTurretAttachmenttComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTurretAttachmenttComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//	PropertyChangedEvent

	// ...
}




