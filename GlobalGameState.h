// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MainCharacter.h"
#include "MotherShip.h"
#include "TurretHardPoint.h"
#include "GridManagerActor.h"
#include "GridNodeActor.h"
#include "TurretActor.h"
#include "IngameHUD.h"
#include "ControlPointActor.h"
#include "GameFramework/GameStateBase.h"
#include "GlobalGameState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API AGlobalGameState : public AGameStateBase
{
	GENERATED_BODY()

	AGlobalGameState(const class FObjectInitializer& PCIP);
	AGlobalGameState();



protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:


	static void ToggleViewMode();

	INT32 GetCurrentHardPointIndex();
	void SetCurrentHardPointIndex(INT32 index);

	 void DisableInputEX();
	 void EnableInputEX();
	 void UsableInView();
	 void NoUsableInView();
	 void HardPointInView();
	 void NoHardPointInView();
	 void showMenu();
	 void ClearSelected();

	 void SetTurret(ATurretActor* turret);

	 void SetHardPoint(ATurretHardPoint* hardpoint);

	 void AddControlPoint(AControlPointActor* controlPoint);

	 AControlPointActor* GetControlPoint();

	UPROPERTY(EditAnywhere)
	AMotherShip* MainShip;

	UPROPERTY(EditAnywhere)
	AMainCharacter* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TArray<ATurretHardPoint*> TurretHardPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		TArray<AControlPointActor*> ControlPointActors;

	void AddTurretToHardPoint(FString TurretName, INT32 index);

	UPROPERTY(EditAnywhere)
		AGridManagerActor* GridManager;
};
