// Fill out your copyright notice in the Description page of Project Settings.



#include "Project_X_Ray.h"
#include "GlobalGameState.h"

UClass* GridNodeActorClassHolder;
UClass* GridManagerActorClassHolder;

AGlobalGameState::AGlobalGameState(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	static ConstructorHelpers::FClassFinder<AGridNodeActor> TheTurret(TEXT("/Game/WorldObjects/BP_GridNodeActor.BP_GridNodeActor_C"));
	if (TheTurret.Class != NULL)
	{
		GridNodeActorClassHolder = TheTurret.Class;
	}
	static ConstructorHelpers::FClassFinder<AGridManagerActor> TheTurret2(TEXT("/Game/BP_GridManager.BP_GridManager_C"));
	if (TheTurret2.Class != NULL)
	{
		GridManagerActorClassHolder = TheTurret2.Class;
	}

	TurretHardPoints = TArray<ATurretHardPoint*>();
}

AGlobalGameState::AGlobalGameState()
{
	static ConstructorHelpers::FClassFinder<AGridNodeActor> TheTurret(TEXT("/Game/WorldObjects/BP_GridNodeActor.BP_GridNodeActor_C"));
	if (TheTurret.Class != NULL)
	{
		GridNodeActorClassHolder = TheTurret.Class;
	}
	static ConstructorHelpers::FClassFinder<AGridManagerActor> TheTurret2(TEXT("/Game/BP_GridManager.BP_GridManager_C"));
	if (TheTurret2.Class != NULL)
	{
		GridManagerActorClassHolder = TheTurret2.Class;
	}

	TurretHardPoints = TArray<ATurretHardPoint*>();

}

void AGlobalGameState::BeginPlay()
{
	Super::BeginPlay();
	
	if (GridNodeActorClassHolder != NULL && GridManagerActorClassHolder != NULL)
	{
		UWorld* World = GetWorld();
		if (World)
		{
		
			FActorSpawnParameters SpawnParams;
			GridManager = World->SpawnActor<AGridManagerActor>(GridManagerActorClassHolder, FVector(0, 0, 0) , FRotator(0.0f, 0.0f, 0.0f), SpawnParams);

			GridManager->Grid.Rows.SetNum(16);

			for (int x = 0; x < 16; x++)
			{
				for (int y = 0; y < 16; y++)
				{
					FVector2D pos = FVector2D(x * 256, y * 256);
		
					AGridNodeActor* NewGridCell = World->SpawnActor<AGridNodeActor>(GridNodeActorClassHolder, FVector(pos.X, pos.Y, 55) + FTransform(FRotator(0.0f, 0.0f, 0.0f)).TransformVector(FVector(-2048, -2048, 0)), FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
					NewGridCell->Index = FVector2D(x, y);
					FGridNodeHolder NodeHolder = FGridNodeHolder();
					NodeHolder.GridNode = NewGridCell;
					GridManager->Grid.Rows[x].Cols.Add(NodeHolder);
				};
			};
		}
	}
}

void AGlobalGameState::ToggleViewMode()
{
	AIngameHUD::ToggleViewMode();
}



INT32 AGlobalGameState::GetCurrentHardPointIndex()
{
	return INT32();
}

void AGlobalGameState::SetCurrentHardPointIndex(INT32 index)
{
	MainShip->CurrentHardPointIndex = index;
}

void AGlobalGameState::DisableInputEX()
{
	AIngameHUD::DisableInputEX();
}

void AGlobalGameState::EnableInputEX()
{
	AIngameHUD::EnableInputEX();
}

void AGlobalGameState::UsableInView()
{
	AIngameHUD::UsableInView();
}

void AGlobalGameState::NoUsableInView()
{
	AIngameHUD::NoUsableInView();
}

void AGlobalGameState::HardPointInView()
{
	AIngameHUD::HardPointInView();
}

void AGlobalGameState::NoHardPointInView()
{
	AIngameHUD::NoHardPointInView();
}

void AGlobalGameState::showMenu()
{
	AIngameHUD::showMenu();
}

void AGlobalGameState::ClearSelected()
{
	AIngameHUD::ClearSelected();
}

void AGlobalGameState::SetTurret(ATurretActor * turret)
{
	AIngameHUD::SetTurret(turret);
}

void AGlobalGameState::SetHardPoint(ATurretHardPoint * hardpoint)
{
	AIngameHUD::SetHardPoint(hardpoint);
}


void AGlobalGameState::AddTurretToHardPoint(FString TurretName,INT32 index)
{
	int counter = TurretHardPoints.Num();
	if (index >= 0 && index <= counter)
	{
	  TurretHardPoints[index]->BuildTurret(TurretName);
	}
}