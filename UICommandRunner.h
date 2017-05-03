// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/HUD.h"
#include "UICommandRunner.generated.h"
/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API UICommandRunner : public UCheatManager
{
	GENERATED_BODY()
	UICommandRunner(const FObjectInitializer & PCIP);

	/*Function with no parameters*/

public:
	UICommandRunner();

	
};
