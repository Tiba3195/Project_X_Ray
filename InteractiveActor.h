// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InteractiveActor.generated.h"

UCLASS()
class PROJECT_X_RAY_API AInteractiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractiveActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Defines a Context Area. All input outside its reach is ignored */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trigger")
		USphereComponent* Trigger;

	/** Called when an Action Input happens within the Context Area of this Actor */
	UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "OnAction"))
		void OnContextAction();
	
};

