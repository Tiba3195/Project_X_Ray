// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_X_Ray.h"
#include "TurretActor.h"




ATurretActor::ATurretActor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	/* the default properties from FPStemplate */

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	Gun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));


	//OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	//OurCamera->SetupAttachment(RootComponent);
	//OurCamera->SetRelativeLocation(FirstPersonCameraOffset + BaseEyeHeight);
	//OurCamera->SetRelativeLocation(FirstPersonCameraOffset);
	// Allow the pawn to control camera rotation.
	//OurCamera->bUsePawnControlRotation = true;

	//This was a super sucky bug, took me hrs to find out the correct way to do this!!
	TurretAttachment = CreateDefaultSubobject<UTurretAttachmenttComponent>(TEXT("Turret Attachment"));
	TurretAttachment->SetupAttachment(RootComponent);
	//TurretAttachment->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));


    //TriggerBox = &ATriggerVolume::ATriggerVolume(PCIP);
	//TriggerBox->SetActorLocation(TurretAttachment->RelativeLocation);
	// Attach the Gun mesh to the FPS camera.
	
	// Attach the Base mesh to the FPS camera.
	Base->SetupAttachment(TurretAttachment);

	Forward = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Attachment"));
	Forward->SetupAttachment(Base);
	Gun->SetupAttachment(Forward);
//	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Volume"));
	//Box->bHiddenInGame = false;
	//Box->SetupAttachment(RootComponent);	

	ProjectileFireControlComponent = CreateDefaultSubobject<UProjectileFireControlComponent>(TEXT("Projectile Fire Control"));
	MuzzleOffsets = TArray<USceneComponent*>();


}

// Sets default values
ATurretActor::ATurretActor()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	Gun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));


//	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	// Attach our camera and visible object to our root component. Offset and rotate the camera.
//	OurCamera->SetupAttachment(RootComponent);
	//OurCamera->SetRelativeLocation(FirstPersonCameraOffset);


	TurretAttachment = CreateDefaultSubobject<UTurretAttachmenttComponent>(TEXT("Turret Attachment"));
	TurretAttachment->SetupAttachment(RootComponent);
//	TurretAttachment->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	// Allow the pawn to control camera rotation.
	//OurCamera->bUsePawnControlRotation = true;


	// Attach the Base mesh to the FPS camera.
	Base->SetupAttachment(TurretAttachment);
	// Attach the Gun mesh to the FPS camera.
	Gun->SetupAttachment(Base);
   // Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Volume"));
	//Box->bHiddenInGame = false;
	//Box->SetupAttachment(RootComponent);

	ProjectileFireControlComponent = CreateDefaultSubobject<UProjectileFireControlComponent>(TEXT("Projectile Fire Control"));
	MuzzleOffsets = TArray<USceneComponent*>();
}


void ATurretActor::BeginPlay()
{
	Super::BeginPlay();
	RegisterDelegate();
}

void ATurretActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TArray<FOverlapResult> HitOut;
	TArray<ABaseCharacter*> ListtoSort = TArray<ABaseCharacter*>();

		// Find objects in range
		if (VTraceSphere(this, GetActorLocation(), GetActorLocation() + AttackRange, AttackRange, HitOut) == true)
		{
			// Filter objects in range
			for (FOverlapResult hit : HitOut)
			{
				found = Cast<ABaseCharacter>(hit.GetActor());
				if (found )
				{					
					if (!found->bDead && !found->bIsDying)
					{
						ListtoSort.Add(found);
					}				
				}
				else
				{
					found = nullptr;
				}
			}		

			ListtoSort.Sort(ConstPredicate);

			if (ListtoSort.Num() > 0)
			{
				found = nullptr;
				found = ListtoSort[0];
			}		
		}

		if (found != nullptr)
		{
			if (!found->bDead && !found->bIsDying)
			{
				FVector target = found->GetActorLocation();
				float d = FVector::Distance(target, GetActorLocation());
				if (d >= AttackRange + 200)
				{
					found = nullptr;
				}
				else
				{
					TurnToFace(found);
				}
			}
		}	
}
void ATurretActor::RegisterDelegate()
{
	
	//if (Box != nullptr)
	//{
	//	if (!Box->OnComponentBeginOverlap.IsAlreadyBound(this, &ATurretActor::OnBeginBoxOverlap))
	//	{
		
	//		Box->OnComponentBeginOverlap.AddDynamic(this, &ATurretActor::OnBeginBoxOverlap);
	//	}
	//}
}

void ATurretActor::TurnToFace(AActor* other)
{
	FVector Direction = other->GetActorLocation() - GetActorLocation();
	FRotator NewControlRotation = Direction.Rotation();

	NewControlRotation.Yaw = FRotator::ClampAxis(NewControlRotation.Yaw);
	Forward->SetRelativeRotation(FRotator(0.0f, NewControlRotation.Yaw, 0.0f));
}

void ATurretActor::AddMuzzleOffSet(USceneComponent * MuzzleOffset)
{
	
	MuzzleOffset->SetupAttachment(Gun);
	MuzzleOffsets.Add(MuzzleOffset);
}

void ATurretActor::OnBeginTriggerOverlap(AActor* OverlappedActor ,AActor* OtherActor)
{
	// This gets called when an actor begins to overlap with the current trigger volume
	if (GEngine)
	{
		TurnToFace(OtherActor);
		// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Inside Turret Trigger Volume"));
	}
}
void ATurretActor::OnBeginBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// This gets called when an actor begins to overlap with the current trigger volume
	if (GEngine)
	{
		// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Inside Turret Trigger Volume"));
	}
}

void ATurretActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

	//if (Box != nullptr)
	//{
	//	if (Box->OnComponentBeginOverlap.IsAlreadyBound(this, &ATurretActor::OnBeginBoxOverlap))
	//	{
		//	Box->OnComponentBeginOverlap.RemoveDynamic(this, &ATurretActor::OnBeginBoxOverlap);
		//}
	//}
	Super::EndPlay(EndPlayReason);
}
