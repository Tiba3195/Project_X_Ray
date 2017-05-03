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
#include "IngameHUD.h"
#include "TurretHardPoint.h"
#include "UICommandRunner.h"

INT32 fCounter = 0;
static ATurretHardPoint* CurrentSelectedHardPoint;
static ATurretActor* CurrentSelectedTurret;

 int AMotherShip::CurrentHardPointIndex = -1;
 UClass* GridNodeActorClassHolder;

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



	static ConstructorHelpers::FClassFinder<AGridNodeActor> TheTurret(TEXT("/Game/WorldObjects/BP_GridNodeActor.BP_GridNodeActor_C"));
	if (TheTurret.Class != NULL)
	{
		GridNodeActorClassHolder = TheTurret.Class;
	}


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
	if (GridNodeActorClassHolder != NULL)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			AGridNodeActor* temp = Cast<AGridNodeActor>(GridNodeActorClassHolder->GetDefaultObject());
			GridManager->Grid.Rows.SetNum(16);

			for (int x = 0; x < 16; x++)
			{
				for (int y = 0; y < 16; y++)
				{
					FVector2D pos = FVector2D(x * 256 , y * 256);
					FActorSpawnParameters SpawnParams;							
					AGridNodeActor* NewGridCell = World->SpawnActor<AGridNodeActor>(GridNodeActorClassHolder, FVector(pos.X, pos.Y, 55) + FTransform(FRotator(0.0f, 0.0f, 0.0f)).TransformVector(FVector(-2048,-2048,0)), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
					NewGridCell->Index = FVector2D(x, y);
					FGridNodeHolder NodeHolder = FGridNodeHolder();
					NodeHolder.GridNode = NewGridCell;					
					GridManager->Grid.Rows[x].Cols.Add(NodeHolder);
				};
			};
		}
	}

	for (int i = 0; i < TurretHardPoints.Num(); i++)
	{
		if (TurretHardPoints[i]->HardPointIndex == -1)
		{
			TurretHardPoints[i]->HardPointIndex = i;
		}
	};

	//AProject_X_RayGameModeBase* gm = (AProject_X_RayGameModeBase*)GetWorld()->GetAuthGameMode();
	OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	OurPlayerController->CheatClass = UICommandRunner::StaticClass();
//	Player->Controller = OurPlayerController;
	if (OurPlayerController)
	{
		if (CameraOne != nullptr)
		{
			AIngameHUD::EnableInputEX();
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



	if (SwitchCamera2==true)
	{	
		if (TimeToNextCameraChange <= 0.0f)
		{
			TimeToNextCameraChange += TimeBetweenCameraChanges;
			// Find the actor that handles control for the local player.
			 OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		//	UGameplayStatics::SetPlayerControllerID(OurPlayerController, 0);
			if (OurPlayerController)
			{
				//if ((OurPlayerController->GetViewTarget() != CameraOne) && (CameraOne != nullptr))
			//	{
					// Cut instantly to camera one.
				//	OurPlayerController->SetViewTarget(CameraOne);
				//}
				if ((OurPlayerController->GetViewTarget() != CameraTwo) && (CameraTwo != nullptr))
				{
					// Blend smoothly to camera two.
				
					OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
					InFirstPersonMode = true;
					Player->IsActive = true;
					AIngameHUD::ToggleViewMode();
					AIngameHUD::DisableInputEX();
				}
			}

			SwitchCamera2 = false;
		}	
	}

	if (SwitchCamera1 == true)
	{
		if (TimeToNextCameraChange <= 0.0f)
		{
			TimeToNextCameraChange += TimeBetweenCameraChanges;

			// Find the actor that handles control for the local player.
		 OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
			if (OurPlayerController)
			{			
				if ((OurPlayerController->GetViewTarget() != CameraOne) && (CameraOne != nullptr))
				{
					// Blend smoothly to camera one.
					OurPlayerController->SetViewTargetWithBlend(CameraOne, SmoothBlendTime);
					InFirstPersonMode = false;
					Player->IsActive = false;
					AIngameHUD::ToggleViewMode();
					AIngameHUD::EnableInputEX();
				}
			}

			SwitchCamera1 = false;
		}
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
void AMotherShip::ClearSelection()
{
	if (CurrentSelectedTurret != nullptr)
	{
		CurrentSelectedTurret = nullptr;
	}
	if (CurrentSelectedHardPoint != nullptr)
	{
		CurrentSelectedHardPoint = nullptr;
	}
	AIngameHUD::ClearSelected();
	if (GEngine)
	{
		// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Selected Cleared"));
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
	//***The Rage***
	PlayerInputComponent->BindAxis("MoveForward", this, &AMotherShip::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMotherShip::MoveRight);
	// Set up "look" bindings.
	PlayerInputComponent->BindAxis("Turn", this, &AMotherShip::AddControllerYawInputEX);
	PlayerInputComponent->BindAxis("LookUp", this, &AMotherShip::AddControllerPitchInputEX);
	// Set up "action" bindings.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMotherShip::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMotherShip::StopJump);
	//Fire!!
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMotherShip::Fire);

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
	AIngameHUD::showMenu();
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
	int counter = TurretHardPoints.Num();
	if (CurrentHardPointIndex >0 && CurrentHardPointIndex <= counter)
	{
		TurretHardPoints[CurrentHardPointIndex]->BuildTurret(TurretName);

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

				//This is really bad!
			    //CameraOne->SetActorRotation(FRotator(0.0f, 0.0f, Val));
			}		
	}
}

void AMotherShip::DoWork(float val)
{

	for (ATurretHardPoint* TurretHardPoint : TurretHardPoints)
	{
		if (TurretHardPoint->HasTurret == true)
		{
			//TurretHardPoint = TurretHardPoint;
			//TurretHardPoint->SetHiddenInGame(true);
			//break;
		}
	}
}

//***The Rage*** Forwarding input to the player
void AMotherShip::MoveForward(float Value)
{	
	if (InFirstPersonMode)
	{
		Player->MoveForward(Value);
	}	
}
void AMotherShip::MoveRight(float Value)
{
	if (InFirstPersonMode)
	{
		Player->MoveRight(Value);
	}	
}
void AMotherShip::StartJump()
{
	if (InFirstPersonMode)
	{
		Player->StartJump();
	}
}
void AMotherShip::StopJump()
{
	if (InFirstPersonMode)
	{
		Player->StopJump();
	}	
}
void AMotherShip::Fire()
{
	if (InFirstPersonMode)
	{
		Player->Fire();
	}
}

//***End The Rage***


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
void AMotherShip::HandlePlayerInput()
{

}

//Flips some Switches 
void AMotherShip::EnterFirstPersonMode()
{
	if (InFirstPersonMode == true)
	{
		SwitchCamera1 = true;
		SwitchCamera2 = false;
	}
	else
	{
		SwitchCamera2 = true;
		SwitchCamera1 = false;
	}	

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
		Player->Use();	
}

void AMotherShip::DummyGetMouseRay()
{
	if (InFirstPersonMode)
	{
		return;
	}
	GetMouseRay(true);
}


bool CheckUseable(AActor* actor, bool Onclick)
{
	ATurretActor* ClickedPawn = Cast<ATurretActor>(actor);

	if (ClickedPawn != nullptr)
	{
		if (Onclick)
		{
			// Unposses ourselves  
			//playerController->UnPossess();
			// Posses the controller we clicked on  
			//playerController->Possess(ClickedPawn);
			if (GEngine)
			{
				// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Selected Turret"));
			}
			CurrentSelectedTurret = ClickedPawn;
			AIngameHUD::SetTurret(CurrentSelectedTurret);
			return true;
		}
		else
		{
			AIngameHUD::UsableInView();
			return true;
		}
	}
	else
	{
		AIngameHUD::NoUsableInView();
		return false;
	}

	//return false;
}
bool CheckTurretHardpoint(AActor* actor, bool Onclick)
{
	ATurretHardPoint* ClickedPawn = Cast<ATurretHardPoint>(actor);

	if (ClickedPawn != nullptr)
	{
		if (Onclick)
		{
			// Unposses ourselves  
			//playerController->UnPossess();
			// Posses the controller we clicked on  
			//playerController->Possess(ClickedPawn);
			if (GEngine)
			{
				// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Selected Hardpoint"));
			}
			CurrentSelectedHardPoint = ClickedPawn;
			AIngameHUD::SetHardPoint(CurrentSelectedHardPoint);
			return true;
		}
		else
		{
			AIngameHUD::HardPointInView();
			return true;
		}
	}
	else
	{
		AIngameHUD::NoHardPointInView();
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
				if(CheckUseable(HitResult.GetActor(), Onclick))
				{
					Hit = true;
			    }

				if (!Hit)
				{
					if (CheckTurretHardpoint(HitResult.GetActor(), Onclick))
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
				AIngameHUD::NoUsableInView();
				AIngameHUD::NoHardPointInView();
			}
		}

		//playerController->DeprojectMousePositionToWorld(mouseLocation, mouseDirection);

		//FRotator currentCharacterRotation = this->GetActorRotation();
		//FRotator targetRotation = mouseDirection.Rotation();

		//FRotator newRotation = FRotator(currentCharacterRotation.Pitch, targetRotation.Yaw, currentCharacterRotation.Roll);
		//this->SetActorRotation(newRotation);
	}
}
