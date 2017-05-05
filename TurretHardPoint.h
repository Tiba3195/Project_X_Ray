// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "UsableActor.h"
#include "TurretAttachmenttComponent.h"
#include "TurretComponent.h"
#include "TurretActor.h"
#include "MediumTurretActor.h"
#include "LightTurretActor.h"
#include "HeavyTurretActor.h"
#include "HardPointAttachment.h"
#include "TurretHardPoint.generated.h"


/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API ATurretHardPoint : public AUsableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATurretHardPoint();
	ATurretHardPoint(const FObjectInitializer & PCIP);

	void RegisterDelegate();
	void EndPlay(const EEndPlayReason::Type EndPlayReason);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	 void BuildTurret();
	 void BuildTurret(FString TurretName);
	
	 bool HasTurret;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UStaticMeshComponent* HardpointBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UTurretAttachmenttComponent* TurretAttachment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UHardPointAttachment* HardPointAttachment;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	//UTurretComponent* TurretComponent;

	//Sets the Camera Rotation
	UPROPERTY(EditAnywhere)
		FVector AttachmentOffset = FVector(0.0f, 0.0f, 0.0f);
	//Sets the Camera Rotation
	//UPROPERTY(EditAnywhere)
		int HardPointIndex =-1;

	
};
