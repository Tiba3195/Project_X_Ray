// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "HardPointAttachment.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_X_RAY_API UHardPointAttachment : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHardPointAttachment();
	UHardPointAttachment(const FObjectInitializer & PCIP);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	UPROPERTY(EditAnywhere)
		UBoxComponent* Box;
};
