// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Project_X_Ray.h"
#include "BaseCharacter.h"
#include "MainCharacter.generated.h"

UCLASS()
class PROJECT_X_RAY_API AMainCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();
	AMainCharacter(const FObjectInitializer & PCIP);
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	/** Get actor derived from UsableActor currently looked at by the player */
	class AUsableActor* GetUsableInView();

	/* Max distance to use/focus on actors. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float MaxUseDistance;

	/* True only in first frame when focused on new usable actor. */
	bool bHasNewFocus;

	/* Actor derived from UsableActor currently in center-view. */
	AUsableActor* FocusedUsableActor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	// Handles input for moving forward and backward.
	UFUNCTION()
		void MoveForward(float Value);

	// Handles input for moving right and left.
	UFUNCTION()
		void MoveRight(float Value);
	// Sets jump flag when key is pressed.
	UFUNCTION()
		void StartJump();

	// Clears jump flag when key is released.
	UFUNCTION()
		void StopJump();

	UPROPERTY(EditAnywhere)
	   UCameraComponent* OurCamera;


	//Sets the Camera Offset
	UPROPERTY(EditAnywhere)
		FVector FirstPersonCameraOffset = FVector(0.0f, 0.0f, 0.0f);	
	 
	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* FPSMesh;

	// Function that handles firing projectiles.
	UFUNCTION()
		void Fire();

	// Gun muzzle's offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		int PlayerID=0;


	/** Use the actor currently in view (if derived from UsableActor) */
	UFUNCTION(BlueprintCallable, Category = PlayerAbility)
		virtual void Use();

	/** Use the actor currently in view (if derived from UsableActor) */
	UFUNCTION(BlueprintCallable, Category = PlayerAbility)
		virtual void CheckInView();

	void AddControllerPitchInputEX(float Val);

	void AddControllerYawInputEX(float Val);
	void	ShowMenu();

	void SwitchToMotherShip();
	
	void StopShooting();

};
