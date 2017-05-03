// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "TurretHardPoint.h"

#include "MediumTurretActor.h"
#include "LightTurretActor.h"
#include "HeavyTurretActor.h"


UClass* HeavyTurretActorClassHolder;
UClass* MediumTurretActorClassHolder;
UClass* LightTurretActorClassHolder;
UClass* TurretActorClassHolder;

static FString HeavyTurretName = "/Game/Turrets/BP_HeavyTurretActor.BP_HeavyTurretActor_C";
static FString MediumTurretTurretName = "/Game/Turrets/BP_MediumTurretActor.BP_MediumTurretActor_C";
static FString LightTurretName = "/Game/Turrets/BP_LightTurretActor.BP_LightTurretActor_C";


ATurretHardPoint::ATurretHardPoint(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	HardpointBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HardpointBase Mesh"));
    HardpointBase->SetupAttachment(RootComponent);

	TurretAttachment = CreateDefaultSubobject<UTurretAttachmenttComponent>(TEXT("Turret Attachment"));
	TurretAttachment->SetupAttachment(HardpointBase);
	//TurretAttachment->SetRelativeLocation(FVector(0.0f, 0.0f, 113.179932));

	static ConstructorHelpers::FClassFinder<ATurretActor> TheTurret(TEXT("/Game/Turrets/BP_LightTurretActor.BP_LightTurretActor_C"));
	if (TheTurret.Class != NULL)
	{
		LightTurretActorClassHolder = TheTurret.Class;
	}
	static ConstructorHelpers::FClassFinder<ATurretActor> TheTurret2(TEXT("/Game/Turrets/BP_MediumTurretActor.BP_MediumTurretActor_C"));
	if (TheTurret2.Class != NULL)
	{
		MediumTurretActorClassHolder = TheTurret2.Class;
	}
	static ConstructorHelpers::FClassFinder<ATurretActor> TheTurret3(TEXT("/Game/Turrets/BP_HeavyTurretActor.BP_HeavyTurretActor_C"));
	if (TheTurret3.Class != NULL)
	{
		HeavyTurretActorClassHolder = TheTurret3.Class;
	}
	static ConstructorHelpers::FClassFinder<ATurretActor> TheTurret4(TEXT("/Game/Turrets/BP_TurretActor.BP_TurretActor_C"));
	if (TheTurret4.Class != NULL)
	{
		TurretActorClassHolder = TheTurret4.Class;
	}
}


ATurretHardPoint::ATurretHardPoint()
{

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	HardpointBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HardpointBase Mesh"));
	HardpointBase->SetupAttachment(RootComponent);


	TurretAttachment = CreateDefaultSubobject<UTurretAttachmenttComponent>(TEXT("Turret Attachment"));
	TurretAttachment->SetupAttachment(HardpointBase);
	//TurretAttachment->SetRelativeLocation(FVector(0.0f, 0.0f,113.179932));

	static ConstructorHelpers::FClassFinder<ATurretActor> TheTurret(TEXT("/Game/Turrets/BP_TurretActor.BP_TurretActor_C"));
	if (TheTurret.Class != NULL)
	{
		TurretActorClassHolder = TheTurret.Class;
	}
}


void ATurretHardPoint::RegisterDelegate()
{
}

void ATurretHardPoint::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

	Super::EndPlay(EndPlayReason);

}

void ATurretHardPoint::BeginPlay()
{
	Super::BeginPlay();
	RegisterDelegate();
//	BuildTurret();
}

void ATurretHardPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ATurretHardPoint::BuildTurret()
{
	if (TurretActorClassHolder != NULL)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			//SpawnParams.Instigator = this;
			ATurretActor* temp = Cast<ATurretActor>(TurretActorClassHolder->GetDefaultObject());
			FVector tempV = temp->TurretAttachment->RelativeLocation;
			FVector tempV2 = TurretAttachment->RelativeLocation;
			FVector tempV3 = GetActorLocation() + tempV2 + tempV;
			
			ATurretActor* NewTurret = World->SpawnActor<ATurretActor>(TurretActorClassHolder, tempV3, FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
			//temp->TurretAttachment->RelativeLocation + TurretAttachment->RelativeLocation
			//NewTurret = TheTurret.Object;
		// NewTurret->SetActorLocation(tempV3);

		//	if (DroppedItem)
		//	{
			//	DroppedItem->DoTheThings();
			//}

		}
	}
}






void ATurretHardPoint::BuildTurret(FString TurretName)
{
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;

		if (TurretName == HeavyTurretName)
		{
			if (HeavyTurretActorClassHolder != NULL)
			{			
				AHeavyTurretActor* temp = Cast<AHeavyTurretActor>(HeavyTurretActorClassHolder->GetDefaultObject());
				FVector tempV = temp->TurretAttachment->RelativeLocation;
				FVector tempV2 = TurretAttachment->RelativeLocation;
				FVector tempV3 = GetActorLocation() + tempV2 + tempV;
				AHeavyTurretActor* NewTurret = World->SpawnActor<AHeavyTurretActor>(HeavyTurretActorClassHolder, tempV3, FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
			}
		}
		if (TurretName == MediumTurretTurretName)
		{
			if (MediumTurretActorClassHolder != NULL)
			{
				AMediumTurretActor* temp = Cast<AMediumTurretActor>(MediumTurretActorClassHolder->GetDefaultObject());
				FVector tempV = temp->TurretAttachment->RelativeLocation;
				FVector tempV2 = TurretAttachment->RelativeLocation;
				FVector tempV3 = GetActorLocation() + tempV2 + tempV;
				AMediumTurretActor* NewTurret = World->SpawnActor<AMediumTurretActor>(MediumTurretActorClassHolder, tempV3, FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
			}
		}
		if (TurretName == LightTurretName)
		{
			if (LightTurretActorClassHolder != NULL)
			{
				ALightTurretActor* temp = Cast<ALightTurretActor>(LightTurretActorClassHolder->GetDefaultObject());
				FVector tempV = temp->TurretAttachment->RelativeLocation;
				FVector tempV2 = TurretAttachment->RelativeLocation;
				FVector tempV3 = GetActorLocation() + tempV2 + tempV;
				ALightTurretActor* NewTurret = World->SpawnActor<ALightTurretActor>(LightTurretActorClassHolder, tempV3, FRotator(0.0f, 0.0f, 0.0f), SpawnParams);
			}
		}
	}
}
