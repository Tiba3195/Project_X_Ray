// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "ProjectileFireControlComponent.h"
#include "BaseCharacter.generated.h"

UCLASS()
class PROJECT_X_RAY_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();
	ABaseCharacter(const class FObjectInitializer& PCIP);

	ABaseCharacter* found;
	/** animation played on death */
	UPROPERTY(EditAnywhere)
		bool HaveTarget = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health)
		bool bInRagdoll = false;

	/** Identifies if pawn is in its dying state */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health)
		bool bIsDying = false;

	// Current health of the Pawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float Health;

	// Current health of the Pawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float MaxHealth;
	/** Identifies if pawn is in its dying state */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health)
		bool bDead = false;


	//Check to see if its shooting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		bool IsShooting = false;

	bool IsActive = false;

	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		USkeletalMeshComponent* FP_Gun;

	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		USceneComponent* MuzzleOffset;

	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		float FireRate = 3;

	 float CurrentFireRate;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UProjectileFireControlComponent* ProjectileFireControlComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	/** Pawn suicide */
	virtual void Suicide();

	/** Kill this pawn */
	virtual void KilledBy(class APawn* EventInstigator);

	/** Returns True if the pawn can die in the current state */
	virtual bool CanDie(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser) const;


	/**
	* Kills pawn.  Server/authority only.
	* @param KillingDamage - Damage amount of the killing blow
	* @param DamageEvent - Damage event of the killing blow
	* @param Killer - Who killed this pawn
	* @param DamageCauser - the Actor that directly caused the damage (i.e. the Projectile that exploded, the Weapon that fired, etc)
	* @returns true if allowed
	*/
	virtual bool Die(float KillingDamage, struct FDamageEvent const& DamageEvent, class AController* Killer, class AActor* DamageCauser);



	/** play effects on hit */
	virtual void PlayHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

	/** switch to ragdoll */
	void SetRagdollPhysics();

	void StopAllAnimMontages();

	/** play anim montage */
	virtual float PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None) override;

	/** stop playing montage */
	virtual void StopAnimMontage(class UAnimMontage* AnimMontage) override;
	/** animation played on death */
	UPROPERTY(EditAnywhere)
		float DetectionRange = 256;
	/** animation played on death */
	UPROPERTY(EditAnywhere)
		int Team = 0;

	UPROPERTY(EditAnywhere)
		bool IsBot=false;

	void TurnToFace(AActor* other);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

	/** animation played on death */
	UPROPERTY(EditAnywhere, Category = Animation)
		UAnimMontage* DeathAnim;



	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	static FORCEINLINE bool VTraceSphere(
		AActor* ActorToIgnore,
		const FVector& Start,
		const FVector& End,
		const float Radius,
		TArray<FOverlapResult>& HitOut,
		ECollisionChannel TraceChannel = ECC_Pawn
	) {
		FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, ActorToIgnore);
		//TraceParams.bTraceComplex = true;
	//	TraceParams.bTraceAsyncScene = true;
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


	

};
