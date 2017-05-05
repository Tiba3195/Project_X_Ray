// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TurretActor.h"
#include "HeavyTurretActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API AHeavyTurretActor : public ATurretActor
{
	GENERATED_BODY()


public:
		// Sets default values for this actor's properties
	AHeavyTurretActor();
	AHeavyTurretActor(const FObjectInitializer & PCIP);
	
	

	UPROPERTY(EditAnywhere)
	USceneComponent* NewMuzOffSet;

	UPROPERTY(EditAnywhere)
	USceneComponent* NewMuzOffSet1;
};
