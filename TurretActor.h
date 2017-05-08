// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "TurretAttachmenttComponent.h"
#include "UsableActor.h"
#include "ProjectileFireControlComponent.h"
#include "BaseCharacter.h"
#include "TurretActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_X_RAY_API ATurretActor : public AUsableActor
{
	GENERATED_BODY()
	

		

public:
	// Sets default values for this actor's properties
	ATurretActor();
	ATurretActor(const FObjectInitializer & PCIP);

	ABaseCharacter* found;

	void RegisterDelegate();

	void AddMuzzleOffSet(USceneComponent* MuzzleOffset);
//	void OnBeginTriggerOverlap( AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void OnBeginTriggerOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OnBeginBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	void EndPlay(const EEndPlayReason::Type EndPlayReason);

	UPROPERTY(EditAnywhere)
		TArray<USceneComponent*> MuzzleOffsets;

	//Sets the Camera Offset
	UPROPERTY(EditAnywhere)
		FVector FirstPersonCameraOffset = FVector(0.0f, 0.0f, 50.0f);

	//Sets the Camera Offset
	UPROPERTY(EditAnywhere)
		FVector ThirdPersonCameraOffset = FVector(0.0f, 0.0f, 0.0f);

	//Sets the Camera Rotation
	UPROPERTY(EditAnywhere)
		FRotator ThirdPersonCameraRotation = FRotator(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Gun;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Base;

//	UPROPERTY(EditAnywhere)
	//	UCameraComponent* OurCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UTurretAttachmenttComponent* TurretAttachment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UProjectileFireControlComponent* ProjectileFireControlComponent;
	void TurnToFace(AActor* other);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float AttackRange = 500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UArrowComponent* Forward;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	//UPROPERTY(EditAnywhere)
	//	UBoxComponent* Box;

	static FORCEINLINE bool VTraceSphere(
		AActor* ActorToIgnore,
		const FVector& Start,
		const FVector& End,
		const float Radius,
		TArray<FOverlapResult>& HitOut,
		ECollisionChannel TraceChannel = ECC_Pawn
	){
		FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, ActorToIgnore);
		//TraceParams.bTraceComplex = true;
		//TraceParams.bTraceAsyncScene = true;
		TraceParams.bReturnPhysicalMaterial = false;

		//Ignore Actors
		TraceParams.AddIgnoredActor(ActorToIgnore);
		//TraceParams.AddIgnoredComponent(UStaticMeshComponent::GetArchetype)
		//Re-initialize hit info
		HitOut = TArray<FOverlapResult>();

		//Get World Source
		TObjectIterator< APlayerController > ThePC;
		if (!ThePC) return false;


		return ThePC->GetWorld()->OverlapMultiByProfile(
			HitOut,
			Start,			
			FQuat(),
			"pawn",
			FCollisionShape::MakeSphere(Radius),
			TraceParams
		);
	}
	inline static bool ConstPredicate(const ABaseCharacter& ip1, const ABaseCharacter& ip2)
	{
		return (ip1.Health < ip2.Health);
	}

};
