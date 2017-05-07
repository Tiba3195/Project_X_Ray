// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Project_X_Ray.h"
#include "GameFramework/Pawn.h"
#include "FPSProjectile.h"
#include "Project_X_RayGameModeBase.h"
#include "TurretHardPoint.h"
#include "TurretActor.h"
#include "MotherShip.generated.h"

UCLASS()
class PROJECT_X_RAY_API AMotherShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMotherShip();
	AMotherShip(const FObjectInitializer & PCIP);



protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	/** Get actor derived from UsableActor currently looked at by the player */
	class AUsableActor* GetUsableInView();

	/* Max distance to use/focus on actors. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float MaxUseDistance;

	/* True only in first frame when focused on new usable actor. */
	bool bHasNewFocus;

	/* Actor derived from UsableActor currently in center-view. */
	AUsableActor* FocusedUsableActor;


public:	

	UFUNCTION(Exec, Category = ExecFunctions)
		void DoSomething();

	/*Function with one parameter*/
	UFUNCTION(Exec, Category = ExecFunctions)
		void DoSomethingElse(float param);

	/*Function with two parameters*/
	UFUNCTION(Exec, Category = ExecFunctions)
		void DoubleParamFunction(float param1, int32 param2);

	/*Function with two parameters*/
	UFUNCTION(Exec, Category = ExecFunctions)
		void AddTurretToHardPoint(FString TurretName);

	/*Function with two parameters*/
	UFUNCTION(Exec, Category = ExecFunctions)
		void ToggleGrid();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void PanShipCamera(float Val);

	void DoWork(float val);

	void ClearSelection();

	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;

	APlayerController* OurPlayerController;



	int HeavyTurretCount=0;
	int MidTurretCount=0;
	int SmallTurretCount=0;

	//Input functions
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);

	void SetHeavyTurretsActive();
	void SetMidTurretsActive();
	void SetSmallTurretsActive();

	void AddHeavyTurret();
	void AddMidTurret();
	void AddSmallTurret();
	void TakeControl(float timeToNextCameraChange);
	void BeginTakeControl();
	void HandlePlayerInput();

	void EnterFirstPersonMode();

	bool SwitchCamera2 = false;

	bool SwitchCamera1 = false;

	bool InFirstPersonMode = false;

	UPROPERTY(EditAnywhere)
		AActor* CameraOne;

	UPROPERTY(EditAnywhere)
		AActor* CameraTwo;

	float TimeToNextCameraChange;

	//UPROPERTY(EditAnywhere)
	//AMainCharacter* Player;

	//Sets the Camera Rotation
	UPROPERTY(EditAnywhere)
		FRotator ThirdPersonCameraRotation = FRotator(0.0f, 0.0f, 0.0f);	

	/** Use the actor currently in view (if derived from UsableActor) */
	UFUNCTION(BlueprintCallable, Category = PlayerAbility)
		virtual void Use();



	  void GetMouseRay(bool Onclick);
	  void DummyGetMouseRay();
	  void	ShowMenu();
	  void RotateMainCamera(float value);

	static  int CurrentHardPointIndex;
	void AddControllerPitchInputEX(float Val);

	void AddControllerYawInputEX(float Val);
};


