// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "GlobalGameState.h"
#include "Project_X_RayGameModeBase.h"



AProject_X_RayGameModeBase::AProject_X_RayGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// You can obtain the asset path of your HUD blueprint through the editor 
	// by right-clicking the Blueprint asset and choosing "Copy Reference".
	// You should then add the "_C" suffix so that the class finder properly 
	// points to the actual class used by the game, as opposed to its Blueprint
	// which is an editor-only concept).
	// 
	// For instance, given a blueprint named BP_JoyHUD, the class path would be
	//	"/Game/Blueprints/BP_JoyHUD_C"
	static ConstructorHelpers::FClassFinder<AHUD> TheHUDOb(TEXT("/Game/HUD/BP_IngameHUD.BP_IngameHUD_C"));
	if (TheHUDOb.Class != NULL)
	{
		HUDClass = TheHUDOb.Class;
	}

	static ConstructorHelpers::FClassFinder<AGlobalGameState> TheGameStateOb(TEXT("/Game/BP_GlobalGameState.BP_GlobalGameState_C"));
	if (TheGameStateOb.Class != NULL)
	{
		GameStateClass = TheGameStateOb.Class;
	}

	
}
// Note that engine version 4.3 changed the method's name to StartPlay(), because of this engine versions before 4.3, or older tutorials, use BeginPlay()
void AProject_X_RayGameModeBase::StartPlay()
{
	Super::StartPlay();

//	StartMatch();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("HELLO WORLD"));
	}
}