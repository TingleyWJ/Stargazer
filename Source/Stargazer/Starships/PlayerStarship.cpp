// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerStarship.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"

APlayerStarship::APlayerStarship(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//Super::AStarshipBase();
	turnRate = 0.25f;
	rollRate = 10.0f;

	strafeVal = 0.0f;
}

void APlayerStarship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Thrust", this, &APlayerStarship::Thrust);
	PlayerInputComponent->BindAxis("ThrustStrafe", this, &APlayerStarship::ThrustStrafe);

	PlayerInputComponent->BindAxis("Turn", this, &APlayerStarship::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerStarship::LookUp);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerStarship::ToggleShoot);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &APlayerStarship::ToggleShoot);
}

void APlayerStarship::BeginPlay()
{
	Super::BeginPlay();

	//GetWorld()->GetTimerManager().SetTimer(ShootHandle, this, &AStarshipBase::Shoot, fireRate);
	//GetWorld()->GetTimerManager().PauseTimer(ShootHandle);
}

void APlayerStarship::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// Ensure the fuze timer is cleared by using the timer handle
	//GetWorld()->GetTimerManager().ClearTimer(ShootHandle);

	// Alternatively you can clear ALL timers that belong to this (Actor) instance.
	//GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void APlayerStarship::Thrust(float value)
{
	if (Controller != NULL && value != 0.0f)
	{
		//if (GetCharacterMovement()->getspeed)
		AddMovementInput(FRotationMatrix(Controller->GetControlRotation()).GetUnitAxis(EAxis::X), value);
	}
}

void APlayerStarship::ThrustStrafe(float value)
{
	strafeVal = value;
	if (Controller != NULL && value != 0.0f)
	{
		AddMovementInput(FRotationMatrix(Controller->GetControlRotation()).GetUnitAxis(EAxis::Y), value);
	}
}

void APlayerStarship::Turn(float value)
{
	if (Controller != NULL && value != 0.0f)
	{
		//UE_LOG(LogTemp, Log, TEXT("Pitch is: %s"), *(GetActorRotation().Euler().ToString()));
		if (FMath::IsNearlyEqual(GetActorRotation().Euler().X, -180.0f, .0001f))
		{
			AddControllerYawInput(value * turnRate * -1);
		}
		else
		{
			AddControllerYawInput(value * turnRate);
		}
	}
}

void APlayerStarship::LookUp(float value)
{
	if (Controller != NULL && value != 0.0f)
	{
		AddControllerPitchInput(value * turnRate);
	}
}

bool APlayerStarship::ToggleShoot(bool status)
{
	return false;
}

void APlayerStarship::ToggleShoot()
{
	isFiring = !isFiring;
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
	}
}

void APlayerStarship::Shoot()
{
	if (Controller != NULL && GetWorld()->GetTimerManager().IsTimerActive(ShootHandle))
	{
		FVector location = GetActorLocation() + GetActorForwardVector() * shipHalfLength;
		FRotator rotation = GetActorRotation(); // (0.0f, 0.0f, 0.0f);
		FActorSpawnParameters spawnInfo;

		if (!ensure(ProjectileSpawn)) { return; }

		AProjectileBase *projBase = GetWorld()->SpawnActor<AProjectileBase>(ProjectileSpawn, location, rotation, spawnInfo);

		FRotator rot = GetActorRotation();
		FVector veloc = /*rot.UnrotateVector(*/GetVelocity();//);

		//Veloc covers the negative, need any multipliers to be positive
		float scalar = FMath::Abs(veloc.Y / FloatingMovement->GetMaxSpeed());
		veloc.Normalize();

		projBase->direction = GetActorForwardVector() + (0.75f * scalar * veloc);
		projBase->ownerStarship = this;

		//UE_LOG(LogTemp, Log, TEXT("Yaw: %f"), GetActorRotation().Yaw);
		//UE_LOG(LogTemp, Log, TEXT("Scalar: %f"), scalar);
		//UE_LOG(LogTemp, Log, TEXT("Forward Vec: %s, Veloc: %s, Dir: %s"), *(GetActorForwardVector().ToString()), *(veloc.ToString()), *(projBase->direction.ToString()));
	}
}