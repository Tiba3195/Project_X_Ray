// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "TPPCharacter.h"
#include "GlobalGameState.h"


//////////////////////////////////////////////////////////////////////////
// ATPPCharacter


UClass* AIControllerClassHolder;

ATPPCharacter::ATPPCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);	
	//GetCapsuleComponent()->SetupAttachment(RootComponent);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;



	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	//GetMesh()->SetupAttachment(RootComponent);

	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
  //  FP_Gun->SetupAttachment(RootComponent);
	// Disable some environmental shadowing to preserve the illusion of having a single mesh.
	FP_Gun->bCastDynamicShadow = false;
	//SEt Shadows
	FP_Gun->CastShadow = false;

	MuzzleOffset = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Offset"));
	MuzzleOffset->SetupAttachment(FP_Gun);

	ProjectileFireControlComponent = CreateDefaultSubobject<UProjectileFireControlComponent>(TEXT("Projectile Fire Control"));

}

//////////////////////////////////////////////////////////////////////////
// Input

void ATPPCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	
	
}


// Called every frame
void ATPPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!HaveTarget)
	{
		OurPlayerController->MoveToMouseCursor();
	}
}

// Called when the game starts or when spawned
void ATPPCharacter::BeginPlay()
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
		//	}
	}
//	OurPlayerController = GetWorld()->SpawnActor<ATopdownCppPlayerController>(GetActorLocation(), GetActorRotation());
  //  OurPlayerController->SetPawn(this);
}







void ATPPCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATPPCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ATPPCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);



}
