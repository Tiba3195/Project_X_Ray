// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "EnemySpawnPoint.h"

UClass* ATPPCharacterClassHolder;
AEnemySpawnPoint::AEnemySpawnPoint(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	// Set this pawn to call Tick() every 
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<ATPPCharacter> TheATPPCharacter(TEXT("/Game/BP_TPPCharacter.BP_TPPCharacter_C"));
	if (TheATPPCharacter.Class != NULL)
	{
		ATPPCharacterClassHolder = TheATPPCharacter.Class;
	}

}
AEnemySpawnPoint::AEnemySpawnPoint()
{
	// Set this pawn to call Tick() every 
	PrimaryActorTick.bCanEverTick = true;

}

void AEnemySpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	Player = GetWorld()->SpawnActor<ATPPCharacter>(ATPPCharacterClassHolder,GetActorLocation(), GetActorRotation());
	Player->OurPlayerController = GetWorld()->SpawnActor<ATopdownCppPlayerController>(Player->GetActorLocation(), Player->GetActorRotation());
	//OurPlayerController->Set
	Player->OurPlayerController->SetPawn(Player);
	Player->OurPlayerController->Possess(Player);

	RegisterDelegate();
}

void AEnemySpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (Player->bDead)
	//{
		//Player->SetLifeSpan(0.001);
		//Player->LifeSpanExpired();
	//	Player->K2_DestroyActor();
		//Player->Destroy(false, true);

		//Player = GetWorld()->SpawnActor<ATPPCharacter>(ATPPCharacterClassHolder, GetActorLocation(), GetActorRotation());
		//Player->OurPlayerController = GetWorld()->SpawnActor<ATopdownCppPlayerController>(Player->GetActorLocation(), Player->GetActorRotation());
		//OurPlayerController->Set
		//Player->OurPlayerController->SetPawn(Player);
		//Player->OurPlayerController->Possess(Player);
		//Player->Set;
		
	//}
	if (IsValid(Player))
	{
		if (Player->bDead)
		{
			Player->OurPlayerController->Destroy(false, true);
			Player->OurPlayerController->RemoveFromRoot();
			Player->OurPlayerController = nullptr;
			Player->LifeSpanExpired();
			Player->Destroy(false, true);
			Player = nullptr;

			HandleReSpawn();
		}
	}
	else
	{
		Player->OurPlayerController->Destroy(false, true);
		Player->OurPlayerController->RemoveFromRoot();
		Player->OurPlayerController = nullptr;
		Player->LifeSpanExpired();
		Player->Destroy(false, true);
		Player = nullptr;

		HandleReSpawn();
	}
}

void AEnemySpawnPoint::RegisterDelegate()
{


	

}
void AEnemySpawnPoint::HandleReSpawn()
{	

	Player = GetWorld()->SpawnActor<ATPPCharacter>(ATPPCharacterClassHolder, GetActorLocation(), GetActorRotation());
	Player->OurPlayerController = GetWorld()->SpawnActor<ATopdownCppPlayerController>(Player->GetActorLocation(), Player->GetActorRotation());
	
	Player->OurPlayerController->SetPawn(Player);
	Player->OurPlayerController->Possess(Player);

	RegisterDelegate();
}
void AEnemySpawnPoint::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	
	Super::EndPlay(EndPlayReason);

}