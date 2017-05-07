// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseCharacter.h"
#include "TopdownCppPlayerController.h"
#include "TPPCharacter.generated.h"


UCLASS(config = Game)
class ATPPCharacter : public ABaseCharacter
{
	GENERATED_BODY()


public:
	ATPPCharacter();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	void EndPlay(const EEndPlayReason::Type EndPlayReason);
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:	



	// Called every frame
	virtual void Tick(float DeltaTime) override;
	ATopdownCppPlayerController* OurPlayerController;

};

