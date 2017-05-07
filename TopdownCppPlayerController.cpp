// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Project_X_Ray.h"
#include "TPPCharacter.h"
#include "TopdownCppPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "GlobalGameState.h"



//static AGlobalGameState* GS;
ATopdownCppPlayerController::ATopdownCppPlayerController()
{

}

void ATopdownCppPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
		MoveToMouseCursor();
		

}

void ATopdownCppPlayerController::MoveToMouseCursor()
{
	UWorld* World = GetWorld();
	AGlobalGameState* GS = Cast<AGlobalGameState>(World->GetGameState());
		if (World)
		{
			GS = Cast<AGlobalGameState>(World->GetGameState());
		}

		if (GS)
		{
			if (!CurrentTarget)
			{
				CurrentTarget = GS->GetControlPoint();
			}
			else
			{

				APawn* const MyPawn = GetPawn();
				if (MyPawn)
				{
					UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
					float const Distance = FVector::Dist(CurrentTarget->GetActorLocation(), MyPawn->GetActorLocation());

					// We need to issue move command only if far enough in order for walk animation to play correctly
					if (NavSys)
					{
						if (Distance > 300.0f)
						{
							NavSys->SimpleMoveToLocation(this, CurrentTarget->GetActorLocation());
						}
						else
						{
							CurrentTarget = nullptr;
						}
					}

				}


				//	UNavigationSystem::SimpleMoveToLocation(this, );

			}
		}

}


void ATopdownCppPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	
}


