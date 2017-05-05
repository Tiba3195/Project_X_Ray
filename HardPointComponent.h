// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/PrimitiveComponent.h"
#include "TurretHardPoint.h"
#include "HardPointComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECT_X_RAY_API UHardPointComponent : public UPrimitiveComponent
{
	GENERATED_BODY()
	
		UHardPointComponent();
	UHardPointComponent(const FObjectInitializer & PCIP);
	
public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		ATurretHardPoint* TurretHardPoint;

	UPROPERTY(EditAnywhere)
		UBoxComponent* Box;
};
