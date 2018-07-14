// Fill out your copyright notice in the Description page of Project Settings.

#include "StarshipBase.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "../Controllers/PlayerStarshipControllerBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AStarshipBase::AStarshipBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	shipHealth = 100;
	shipShields = 100;
	shipHalfLength = 50.f;

	isFiring = false;
	shotsPerSecond = 5;
	fireRate = 1.0f / shotsPerSecond;

	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;
	bUseControllerRotationYaw = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("N/A"));
	RootComponent = SphereCollision;

	SphereCollision->CanCharacterStepUpOn = ECB_No;
	SphereCollision->BodyInstance.SetCollisionProfileName("Pawn");

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("The Name Doesn't Matter"));
	StaticMesh->SetupAttachment(SphereCollision);

	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Ok Gotta Have New Names"));

	FloatingMovement->MaxSpeed = 8000.0f;
	FloatingMovement->Acceleration = 12000.0f;
	FloatingMovement->Deceleration = 4000.0f;
	FloatingMovement->TurningBoost = 0.0f;
}

// Called to bind functionality to input
void AStarshipBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UE_LOG(LogTemp, Log, TEXT("StarshipBase SetUpPlayerInputComponent Called"));
}

// Called when the game starts or when spawned
void AStarshipBase::BeginPlay()
{
	Super::BeginPlay();
	
	//GetWorld()->GetTimerManager().SetTimer(ShootHandle, this, &AStarshipBase::Shoot, fireRate);
	//GetWorld()->GetTimerManager().PauseTimer(ShootHandle);
}

void AStarshipBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// Ensure the fuze timer is cleared by using the timer handle
	//GetWorld()->GetTimerManager().ClearTimer(ShootHandle);

	// Alternatively you can clear ALL timers that belong to this (Actor) instance.
	//GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

// Called every frame
void AStarshipBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//For later: Camera shake on movement?

	/*UE_LOG(LogTemp, Log, TEXT("Rotation is: %s"), *(GetActorRotation().ToString()));

	if (GetActorRotation().Roll != 0)
	{
		float normVal = FGenericPlatformMath::Abs(GetActorRotation().Roll) / 180.f;
		AddControllerRollInput(FGenericPlatformMath::Pow(normVal, 2) * rollRate);
		UE_LOG(LogTemp, Log, TEXT("Normalized Value is: %f"), normVal);
	}*/
}

bool AStarshipBase::ToggleShoot(bool status)
{
	UE_LOG(LogTemp, Warning, TEXT("StarshipBase ToggleShoot Called"));
	return false;
	/*isFiring = !isFiring;
	if (isFiring)
	{
		GetWorld()->GetTimerManager().SetTimer(ShootHandle, this, &AStarshipBase::Shoot, fireRate, true);
		Shoot();
		//UE_LOG(LogTemp, Log, TEXT("Fire ON, FireRate is: %f"), GetWorld()->GetTimerManager().GetTimerRate(ShootHandle));
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(ShootHandle);
		//UE_LOG(LogTemp, Log, TEXT("Fire OFF"));
	}*/
}

void AStarshipBase::Shoot()
{
	UE_LOG(LogTemp, Warning, TEXT("StarshipBase Shoot Called"));
	/*if (Controller != NULL && GetWorld()->GetTimerManager().IsTimerActive(ShootHandle))
	{
		FVector location = GetActorLocation() + GetActorForwardVector() * shipHalfLength;
		FRotator rotation = GetActorRotation(); // (0.0f, 0.0f, 0.0f);
		FActorSpawnParameters spawnInfo;

		if (!ensure(ProjectileSpawn)) { return; }

		AProjectileBase *projBase = GetWorld()->SpawnActor<AProjectileBase>(ProjectileSpawn, location, rotation, spawnInfo);

		FRotator rot = GetActorRotation();
		FVector veloc = rot.UnrotateVector(GetVelocity();//);

		//Veloc covers the negative, need any multipliers to be positive
		float scalar = FMath::Abs(veloc.Y / FloatingMovement->GetMaxSpeed());
		veloc.Normalize();

		projBase->direction = GetActorForwardVector() + (0.75f * scalar * veloc);

		//UE_LOG(LogTemp, Log, TEXT("Yaw: %f"), GetActorRotation().Yaw);
		//UE_LOG(LogTemp, Log, TEXT("Scalar: %f"), scalar);
		//UE_LOG(LogTemp, Log, TEXT("Forward Vec: %s, Veloc: %s, Dir: %s"), *(GetActorForwardVector().ToString()), *(veloc.ToString()), *(projBase->direction.ToString()));
	}*/
}