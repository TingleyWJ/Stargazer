// Fill out your copyright notice in the Description page of Project Settings.

#include "StarshipBase.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "StarshipController.h"
#include "ProjectileBase.h"

// Sets default values
AStarshipBase::AStarshipBase()
{
	turnRate = 0.25f;
	rollRate = 10.0f;

	shipHalfLength = 50.f;

	isFiring = false;
	shotsPerSecond = 5;
	fireRate = 1.0f / shotsPerSecond;

	GetCharacterMovement()->DefaultLandMovementMode = EMovementMode::MOVE_Flying;

	GetCharacterMovement()->MaxAcceleration = 12000.f;
	GetCharacterMovement()->MaxFlySpeed = 8000.f;
	GetCharacterMovement()->BrakingDecelerationFlying = 4000.f;

	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;
	bUseControllerRotationYaw = true;
	//GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

// Called to bind functionality to input
void AStarshipBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Thrust", this, &AStarshipBase::Thrust);
	PlayerInputComponent->BindAxis("ThrustStrafe", this, &AStarshipBase::ThrustStrafe);

	PlayerInputComponent->BindAxis("Turn", this, &AStarshipBase::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AStarshipBase::LookUp);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AStarshipBase::ToggleShoot);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &AStarshipBase::ToggleShoot);
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

void AStarshipBase::Thrust(float value)
{
	if (Controller != NULL && value != 0.0f)
	{
		//if (GetCharacterMovement()->getspeed)
		AddMovementInput(FRotationMatrix(Controller->GetControlRotation()).GetUnitAxis(EAxis::X), value);
	}
}

void AStarshipBase::ThrustStrafe(float value)
{
	if (Controller != NULL && value != 0.0f)
	{
		AddMovementInput(FRotationMatrix(Controller->GetControlRotation()).GetUnitAxis(EAxis::Y), value);
	}
}

void AStarshipBase::Turn(float value)
{
	if (Controller != NULL && value != 0.0f)
	{
		AddControllerYawInput(value * turnRate);
	}
}

void AStarshipBase::LookUp(float value)
{
	if (Controller != NULL && value != 0.0f)
	{
		AddControllerPitchInput(value * turnRate);
	}
}

void AStarshipBase::ToggleShoot()
{
	isFiring = !isFiring;
	if (isFiring)
	{
		GetWorld()->GetTimerManager().SetTimer(ShootHandle, this, &AStarshipBase::Shoot, fireRate, true);
		//UE_LOG(LogTemp, Log, TEXT("Fire ON, FireRate is: %f"), GetWorld()->GetTimerManager().GetTimerRate(ShootHandle));
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(ShootHandle);
		//UE_LOG(LogTemp, Log, TEXT("Fire OFF"));
	}
}

void AStarshipBase::Shoot()
{
	if (Controller != NULL && GetWorld()->GetTimerManager().IsTimerActive(ShootHandle))
	{
		FVector location = GetActorLocation() + GetActorForwardVector() * shipHalfLength;
		FRotator rotation = GetActorRotation(); // (0.0f, 0.0f, 0.0f);
		FActorSpawnParameters spawnInfo;
		AProjectileBase *projBase = GetWorld()->SpawnActor<AProjectileBase>(ProjectileSpawn, location, rotation, spawnInfo);

		projBase->direction = GetActorForwardVector();
	}
}