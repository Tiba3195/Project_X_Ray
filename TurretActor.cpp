// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "TurretActor.h"




ATurretActor::ATurretActor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	/* the default properties from FPStemplate */

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	Gun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));


	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	OurCamera->SetupAttachment(RootComponent);
	//OurCamera->SetRelativeLocation(FirstPersonCameraOffset + BaseEyeHeight);
	OurCamera->SetRelativeLocation(FirstPersonCameraOffset);
	// Allow the pawn to control camera rotation.
	//OurCamera->bUsePawnControlRotation = true;
	TurretAttachment = CreateDefaultSubobject<UTurretAttachmenttComponent>(TEXT("Turret Attachment"));
	TurretAttachment->SetupAttachment(OurCamera);
	TurretAttachment->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));



	// Attach the Gun mesh to the FPS camera.
	Gun->SetupAttachment(OurCamera);
	// Attach the Base mesh to the FPS camera.
	Base->SetupAttachment(OurCamera);

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Volume"));
	Box->bHiddenInGame = false;
	Box->SetupAttachment(RootComponent);	
}

// Sets default values
ATurretActor::ATurretActor()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	Gun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));


	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FirstPersonCameraOffset);


	TurretAttachment = CreateDefaultSubobject<UTurretAttachmenttComponent>(TEXT("Turret Attachment"));
	TurretAttachment->SetupAttachment(OurCamera);
	TurretAttachment->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	// Allow the pawn to control camera rotation.
	//OurCamera->bUsePawnControlRotation = true;

	// Attach the Gun mesh to the FPS camera.
    Gun->SetupAttachment(OurCamera);
	// Attach the Base mesh to the FPS camera.
	Base->SetupAttachment(OurCamera);
	
Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Volume"));
	Box->bHiddenInGame = false;
	Box->SetupAttachment(RootComponent);
}


void ATurretActor::BeginPlay()
{
	Super::BeginPlay();
	RegisterDelegate();
}

void ATurretActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	//if (GEngine)
	//{
	//	OurCamera->SetRelativeLocation(FirstPersonCameraOffset);
	//}


	// Get the camera transform.
//	FVector CameraLocation;
//	FRotator CameraRotation;
//	GetActorEyesViewPoint(CameraLocation, CameraRotation);
//	FHitResult HitOut;

	//VTraceSphere(this, CameraLocation, CameraLocation + 1000, 2000, HitOut,ECC_MAX);
}

void ATurretActor::RegisterDelegate()
{
	if (TriggerBox != nullptr)
	{
		if (!TriggerBox->OnActorBeginOverlap.IsAlreadyBound(this, &ATurretActor::OnBeginTriggerOverlap))
		{
			TriggerBox->OnActorBeginOverlap.AddDynamic(this, &ATurretActor::OnBeginTriggerOverlap);
		}
	}


	if (Box != nullptr)
	{
		if (!Box->OnComponentBeginOverlap.IsAlreadyBound(this, &ATurretActor::OnBeginBoxOverlap))
		{
		
			Box->OnComponentBeginOverlap.AddDynamic(this, &ATurretActor::OnBeginBoxOverlap);
		}
	}



}

void ATurretActor::OnBeginTriggerOverlap(AActor* OverlappedActor ,AActor* OtherActor)
{
	// This gets called when an actor begins to overlap with the current trigger volume
	if (GEngine)
	{
		// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Inside Turret Trigger Volume"));
	}
}
void ATurretActor::OnBeginBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// This gets called when an actor begins to overlap with the current trigger volume
	if (GEngine)
	{
		// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Inside Turret Trigger Volume"));
	}
}

void ATurretActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (TriggerBox != nullptr)
	{
		if (TriggerBox->OnActorBeginOverlap.IsAlreadyBound(this, &ATurretActor::OnBeginTriggerOverlap))
		{
			TriggerBox->OnActorBeginOverlap.RemoveDynamic(this, &ATurretActor::OnBeginTriggerOverlap);
		}
	}
	if (Box != nullptr)
	{
		if (Box->OnComponentBeginOverlap.IsAlreadyBound(this, &ATurretActor::OnBeginBoxOverlap))
		{
			Box->OnComponentBeginOverlap.RemoveDynamic(this, &ATurretActor::OnBeginBoxOverlap);
		}
	}
	Super::EndPlay(EndPlayReason);
}
