// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/GameModeBase.h"
#include "Project_X_RayGameModeBase.generated.h"
/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API AProject_X_RayGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	

	AProject_X_RayGameModeBase(const FObjectInitializer & ObjectInitializer);

	virtual void StartPlay() override;



public:



};
