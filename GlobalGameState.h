// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MainCharacter.h"
#include "MotherShip.h"
#include "GameFramework/GameStateBase.h"
#include "GlobalGameState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API AGlobalGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	AActor* MainShip;

	UPROPERTY(EditAnywhere)
	AActor* Player;
	
};
