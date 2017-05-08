// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
//#include "GameFramework/PlayerController.h"
#include "ControlPointActor.h"
#include "TopdownCppPlayerController.generated.h"


UCLASS()
class ATopdownCppPlayerController : public AAIController
{
	GENERATED_BODY()

public:
	ATopdownCppPlayerController();

	AControlPointActor* CurrentTarget;

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

<<<<<<< HEAD
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

=======
>>>>>>> origin/master
protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void Tick(float DeltaTime) override;
	
	// End PlayerController interface


	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);



};

