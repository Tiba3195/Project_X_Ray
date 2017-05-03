// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Actor.h"
#include "UsableActor.generated.h"

UCLASS()
class PROJECT_X_RAY_API AUsableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUsableActor();
	AUsableActor(const FObjectInitializer & PCIP);
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
		bool OnUsedPlayer(AMainCharacter* Player);


	UFUNCTION(BlueprintImplementableEvent)
		bool OnUsed(AMotherShip* mothership);

	UFUNCTION(BlueprintImplementableEvent)
		bool StartFocusItem();

	UFUNCTION(BlueprintImplementableEvent)
		bool EndFocusItem();
	
};
