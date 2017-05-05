// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "HeavyTurretActor.h"




AHeavyTurretActor::AHeavyTurretActor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	/* the default properties from FPStemplate */

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	 NewMuzOffSet = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Off Set 0"));

	AddMuzzleOffSet(NewMuzOffSet);

	 NewMuzOffSet1 = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Off Set 1"));

	AddMuzzleOffSet(NewMuzOffSet1);


}


AHeavyTurretActor::AHeavyTurretActor()
	: Super()
{
	/* the default properties from FPStemplate */

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

 NewMuzOffSet = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Off Set 0"));

	AddMuzzleOffSet(NewMuzOffSet);

	 NewMuzOffSet1 = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Off Set 1"));

	AddMuzzleOffSet(NewMuzOffSet1);

}