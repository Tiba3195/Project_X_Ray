// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TurretHardPoint.h"
#include "GridNodeActor.generated.h"

UCLASS()
class PROJECT_X_RAY_API AGridNodeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridNodeActor();
	AGridNodeActor(const class FObjectInitializer& PCIP);
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static void ToggleVisibilty();

	FVector2D Index;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* NodeMesh;

};
