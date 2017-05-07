// Fill out your copyright notice in the Description page of Project Settings.
// <--------------------------------------INFO---------------------------------------->
/*

Anything with a ***The Rage*** = Not sure if this is the best way but i spent 6hrs playing with different things and for now this is the best way i could think of to control the first person camera, many kittens were 
harmed while writing this code!

The idea here is that the mother ship is the center of the players world, it holds a ref to the player that we will use to run around in first person.
This class will control camera switching, passing of commands to the player object, will hold an array of turrets, will place said turrets aswell as flipping the turrets around for the thing.

Keep the first person movment code and stuff like that out of here, this is just for the mothership!

Time 3:11am time for bed, last thing added selectable turrets! well boxes but they will be turrets!

*/
// <-------------------------------------END INFO------------------------------------->








#include "Project_X_Ray.h"
#include "MotherShip.h"
#include "Project_X_RayGameModeBase.h"
#include "UsableActor.h"
#include "GlobalGameState.h"
#include "TurretHardPoint.h"


INT32 fCounter = 0;
static ATurretHardPoint* SelectedHardPoint;
static ATurretActor* SelectedTurret;

 int AMotherShip::CurrentHardPointIndex = -1;


AMotherShip::AMotherShip(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	/* the default properties from FPStemplate */

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	// Create a dummy root component we can attach things to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	// Create a camera and a visible object

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship VisibleComponent"));
	//OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	//CameraOne->SetupAttachment(RootComponent);
	//CameraOne->SetRelativeLocation(CameraOffset);
	//CameraOne->SetRelativeRotation(CameraRotation);

	OurVisibleComponent->SetupAttachment(RootComponent);
	MaxUseDistance = 8000;
	bHasNewFocus = true;
}

// Sets default values
AMotherShip::AMotherShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	// Create a dummy root component we can attach things to.
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
void AMotherShip::BeginPlay()
{
	Super::BeginPlay();
	OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
//	OurPlayerController->CheatClass = UICommandRunner::StaticClass();
	UWorld* World = GetWorld();
	AGlobalGameState* GS = Cast<AGlobalGameState>(World->GetGameState());
	if (World)
	{
		//this was a bug, was crashing the game because the gamestae was carrying over from runs.... very bad! needs to be a new one eash time!
		//if (!GS)
	//	{
			GS = Cast<AGlobalGameState>(World->GetGameState());
			GS->MainShip = this;
	//	}
	}

	if (OurPlayerController)
	{
		if (CameraOne != nullptr)
		{
			GS->EnableInputEX();			
			// Cut instantly to camera one.
			OurPlayerController->SetViewTarget(CameraOne);
		}
	}	
}

void AMotherShip::ToggleGrid()
{
	AGridNodeActor::ToggleVisibilty();
}

// Called every frame
void AMotherShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DoWork(DeltaTime);

	AGlobalGameState* GS;
	UWorld* World = GetWorld();
	if (World)
	{
		//this was a bug, was crashing the game because the gamestae was carrying over from runs.... very bad! needs to be a new one eash time!
		//if (!GS)
		//	{
		GS = Cast<AGlobalGameState>(World->GetGameState());

		if (GEngine)
		{

		}

		const float TimeBetweenCameraChanges = 2.0f;
		const float SmoothBlendTime = 0.75f;
		TimeToNextCameraChange -= DeltaTime;

		fCounter += 1;
		//this is reall bad, can do much better!
		if (fCounter >= 3)
		{
			GetMouseRay(false);
			fCounter = 0;
		}
		if (SwitchCamera2 == true)
		{
			if (TimeToNextCameraChange <= 0.0f)
			{
				TimeToNextCameraChange += TimeBetweenCameraChanges;
				// Find the actor that handles control for the local player.
				OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);

				if (OurPlayerController)
				{
					if ((OurPlayerController->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr))
					{
						// Blend smoothly to camera two.				
						OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
						InFirstPersonMode = true;
						GS->Player->IsActive = true;
						OurPlayerController->UnPossess();
						// Posses the controller we clicked on  
						OurPlayerController->Possess(GS->Player);

						GS->ToggleViewMode();
						GS->DisableInputEX();
					}
				}

				SwitchCamera2 = false;
			}
		}

		if (SwitchCamera1 == true)
		{
			TakeControl(TimeToNextCameraChange);
		}


		if (Controller && Controller->IsLocalController())
		{
			AUsableActor* usable = GetUsableInView();

			// End Focus
			if (FocusedUsableActor != usable)
			{
				if (FocusedUsableActor)
				{
					FocusedUsableActor->EndFocusItem();
				}

				bHasNewFocus = true;
			}

			// Assign new Focus
			FocusedUsableActor = usable;

			// Start Focus.
			if (usable)
			{
				if (bHasNewFocus)
				{
					usable->StartFocusItem();
					bHasNewFocus = false;
				}
			}
		}

	}
}



void AMotherShip::ClearSelection()
{
	AGlobalGameState* GS;
	UWorld* World = GetWorld();
	if (World)
	{

		GS = Cast<AGlobalGameState>(World->GetGameState());
		//Always check for null! EVERY TIME!!!!!
		if (SelectedTurret != nullptr)
		{
			SelectedTurret = nullptr;
		}
		if (SelectedHardPoint != nullptr)
		{
			SelectedHardPoint = nullptr;
		}
		GS->ClearSelected();
		if (GEngine)
		{
			// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Selected Cleared"));
		}
	}
}

void AMotherShip::AddControllerPitchInputEX(float Val)
{
	if (Val != 0.f )
	{
		APlayerController* const PC = UGameplayStatics::GetPlayerController(this, 0);
		PC->AddPitchInput(Val);
	}
}

void AMotherShip::AddControllerYawInputEX(float Val)
{
	if (Val != 0.f )
	{
		APlayerController* const PC = UGameplayStatics::GetPlayerController(this, 0);
		PC->AddYawInput(Val);
	}
}


// Called to bind functionality to input
void AMotherShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Respond when our "Grow" key is pressed or released.
	PlayerInputComponent->BindAction("ThirdPersonMode", IE_Pressed, this, &AMotherShip::EnterFirstPersonMode);	

	PlayerInputComponent->BindAction("MothershipMouseClick", IE_Pressed, this, &AMotherShip::DummyGetMouseRay);
	// Respond when our "Grow" key is pressed or released.
	PlayerInputComponent->BindAction("Use", IE_Pressed, this, &AMotherShip::Use);
	PlayerInputComponent->BindAction("ClearSelection", IE_Pressed, this, &AMotherShip::ClearSelection);

	//Fire!!
//	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMotherShip::Fire);

	PlayerInputComponent->BindAction("ShowMenu", IE_Pressed, this, &AMotherShip::ShowMenu);
	PlayerInputComponent->BindAxis("RotateMainCamera", this, &AMotherShip::RotateMainCamera);
	

	//This is really bad!
	//PlayerInputComponent->BindAxis("PanShipCamera", this, &AMotherShip::PanShipCamera);

	

	// Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
	//InputComponent->BindAxis("MoveX", this, &AMotherShip::Move_XAxis);
	//InputComponent->BindAxis("MoveY", this, &AMotherShip::Move_YAxis);
	
}
void AMotherShip::ShowMenu()
{
	UWorld* World = GetWorld();
	AGlobalGameState* GS = Cast<AGlobalGameState>(World->GetGameState());
	GS->showMenu();
}
void AMotherShip::DoSomething()
{
	if (GEngine)
	{
		// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("DoSomething"));
	}
}

void AMotherShip::DoSomethingElse(float param)
{
	if (GEngine)
	{
		// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("DoSomethingElse"));
	}
}

void AMotherShip::DoubleParamFunction(float param1, int32 param2)
{
	if (GEngine)
	{
		// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("DoubleParamFunction"));
	}
}
void AMotherShip::AddTurretToHardPoint(FString TurretName)
{
	UWorld* World = GetWorld();
	AGlobalGameState* GS = Cast<AGlobalGameState>(World->GetGameState());
	if (GS)
	{
		int counter = GS->TurretHardPoints.Num();
		if (CurrentHardPointIndex >= 0 && CurrentHardPointIndex <= counter)
		{
			GS->TurretHardPoints[CurrentHardPointIndex]->BuildTurret(TurretName);

		}
	}

	CurrentHardPointIndex = -1;
}
void AMotherShip::RotateMainCamera(float value)
{
	FRotator current = CameraOne->GetActorRotation();
	FRotator newrot = FRotator(current.Pitch, current.Yaw + value, 0.0f);
	CameraOne->SetActorRotation(newrot);
}

void AMotherShip::PanShipCamera(float Val)
{
	if (!InFirstPersonMode)
	{		
			if (Val != 0.f )
			{
				//ACameraActor* const PC = CastChecked<ACameraActor>(CameraTwo);

				//This is really bad! it makes the mother ship spin round super fast 
			    //CameraOne->SetActorRotation(FRotator(0.0f, 0.0f, Val));
			}		
	}
}

void AMotherShip::DoWork(float val)
{

//	for (ATurretHardPoint* TurretHardPoint : TurretHardPoints)
	//{
		//if (TurretHardPoint->HasTurret == true)
		//{
			//TurretHardPoint = TurretHardPoint;
			//TurretHardPoint->SetHiddenInGame(true);
			//break;
		//}
	//}
}

//Laying out the stuff
void AMotherShip::Move_XAxis(float AxisValue)
{

}
void AMotherShip::Move_YAxis(float AxisValue)
{
	
}
void AMotherShip::SetHeavyTurretsActive()
{

}
void AMotherShip::SetMidTurretsActive()
{

}
void AMotherShip::SetSmallTurretsActive()
{

}
void AMotherShip::AddHeavyTurret()
{

}
void AMotherShip::AddMidTurret()
{

}
void AMotherShip::AddSmallTurret()
{

}
void AMotherShip::TakeControl(float timeToNextCameraChange)
{
	if (TimeToNextCameraChange <= 0.0f)
	{
		UWorld* World = GetWorld();
		AGlobalGameState* GS = Cast<AGlobalGameState>(World->GetGameState());

		const float TimeBetweenCameraChanges = 2.0f;
		const float SmoothBlendTime = 0.75f;
		timeToNextCameraChange += TimeBetweenCameraChanges;
		// Find the actor that handles control for the local player.
		OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (OurPlayerController)
		{
			if ((OurPlayerController->GetViewTarget() != CameraOne) && (CameraOne != nullptr))
			{
				OurPlayerController->UnPossess();
				// Posses the controller we clicked on  
				OurPlayerController->Possess(this);
				// Blend smoothly to camera one.
				OurPlayerController->SetViewTargetWithBlend(CameraOne, SmoothBlendTime);
				InFirstPersonMode = false;
				GS->Player->IsActive = false;
		
				GS->ToggleViewMode();
				GS->EnableInputEX();
			}			
		}
		SwitchCamera1 = false;
	}
}

void AMotherShip::BeginTakeControl()
{
	SwitchCamera1 = true;
}

void AMotherShip::HandlePlayerInput()
{

}

//Flips some Switches 
void AMotherShip::EnterFirstPersonMode()
{

	SwitchCamera2 = true;
	SwitchCamera1 = false;	
}
/*
Performs raytrace to find closest looked-at UsableActor.
*/
AUsableActor* AMotherShip::GetUsableInView()
{
	FVector camLoc;
	FRotator camRot;

	if (Controller == NULL)
		return NULL;

	Controller->GetPlayerViewPoint(camLoc, camRot);
	const FVector start_trace = camLoc;
	const FVector direction = camRot.Vector();
	const FVector end_trace = start_trace + (direction * MaxUseDistance);

	FCollisionQueryParams TraceParams(FName(TEXT("")), true, this);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.bTraceComplex = true;

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, start_trace, end_trace, COLLISION_PROJECTILE, TraceParams);

	return Cast<AUsableActor>(Hit.GetActor());
}
/*
Runs on Server. Perform "OnUsed" on currently viewed UsableActor if implemented.
*/
void AMotherShip::Use()
{	
	UWorld* World = GetWorld();
	AGlobalGameState* GS = Cast<AGlobalGameState>(World->GetGameState());
	GS->Player->Use();
}

void AMotherShip::DummyGetMouseRay()
{
	if (InFirstPersonMode)
	{
		return;
	}
	GetMouseRay(true);
}
bool CheckUseable(AActor* actor, bool Onclick, UWorld* World, AGlobalGameState* GS)
{
	ATurretActor* ClickedPawn = Cast<ATurretActor>(actor);	
	
	if (ClickedPawn != nullptr)
	{
		if (Onclick)
		{
		
			if (GEngine)
			{
				// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Selected Turret"));
			}
			SelectedTurret = ClickedPawn;
			GS->SetTurret(SelectedTurret);
			return true;
		}
		else
		{
			GS->UsableInView();
			return true;
		}
	}
	else
	{
		GS->NoUsableInView();
		return false;
	}

	//return false;
}
bool CheckTurretHardpoint(AActor* actor, bool Onclick, UWorld* World, AGlobalGameState* GS)
{
	ATurretHardPoint* ClickedPawn = Cast<ATurretHardPoint>(actor);

	
	if (ClickedPawn != nullptr)
	{
		if (Onclick)
		{
	
			if (GEngine)
			{
				// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Selected Hardpoint"));
			}
			SelectedHardPoint = ClickedPawn;
			GS->SetHardPoint(SelectedHardPoint);
			return true;
		}
		else
		{
			GS->HardPointInView();
			return true;
		}
	}
	else
	{
		GS->NoHardPointInView();
		return false;
	}

	//return false;
}
void AMotherShip::GetMouseRay(bool Onclick)
{
	if (InFirstPersonMode)
	{
		return;
	}
	if (Controller != NULL)
	{
		FVector mouseLocation, mouseDirection;
		APlayerController* playerController = Cast<APlayerController>(GetController());
	
		UWorld* World = GetWorld();
		AGlobalGameState* GS = Cast<AGlobalGameState>(World->GetGameState());

		if (playerController != nullptr)
		{
			// Get the coordinates of the mouse from our controller  
			float LocationX;
			float LocationY;
			playerController->GetMousePosition(LocationX, LocationY);
			// Do a trace and see if there the position intersects something in the world  
			FVector2D MousePosition(LocationX, LocationY);
			FHitResult HitResult;
			const bool bTraceComplex = false;
			if (playerController->GetHitResultAtScreenPosition(MousePosition, ECC_Visibility, bTraceComplex, HitResult) == true)
			{
				bool Hit = false;
				// If the actor we intersected with is a controller posses it  
				//AUsableActor* ClickedPawn = Cast<AUsableActor>(HitResult.GetActor());
				if(CheckUseable(HitResult.GetActor(), Onclick, World, GS))
				{
					Hit = true;
			    }

				if (!Hit)
				{
					if (CheckTurretHardpoint(HitResult.GetActor(), Onclick, World, GS))
					{
						Hit = true;
					}
				}

				if (!Hit)
				{
					//if (CheckTurretHardpoint(HitResult.GetActor(), Onclick))
					//{
					//	Hit = true;  Follow this pattern if adding more clickables
					//}
				}

				//CheckTurretHardpoint
			}
			else
			{
				GS->NoUsableInView();
				GS->NoHardPointInView();
			}
		}

		//playerController->DeprojectMousePositionToWorld(mouseLocation, mouseDirection);

		//FRotator currentCharacterRotation = this->GetActorRotation();
		//FRotator targetRotation = mouseDirection.Rotation();

		//FRotator newRotation = FRotator(currentCharacterRotation.Pitch, targetRotation.Yaw, currentCharacterRotation.Roll);
		//this->SetActorRotation(newRotation);
	}
}
