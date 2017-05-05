// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Components/PrimitiveComponent.h"
#include "TurretAttachmenttComponent.h"
#include "TurretComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API UTurretComponent : public UPrimitiveComponent
{
	GENERATED_BODY()
	
	
public:
	// Sets default values for this actor's properties
	UTurretComponent();
	UTurretComponent(const FObjectInitializer & PCIP);

	void RegisterDelegate();

	//	void OnBeginTriggerOverlap( AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		void OnBeginTriggerOverlap(AActor* OverlappedActor, AActor* OtherActor);

	void EndPlay(const EEndPlayReason::Type EndPlayReason);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:
	// Called every frame
	void TickEX(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		ATriggerVolume* Box;

	 UTurretAttachmenttComponent* TurretAttachmenttComponent;

	 UPROPERTY(EditAnywhere)
		 UBoxComponent* VisBox;
};
