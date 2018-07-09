// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileBase.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	bulletSpeed = 10000.0f;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(DestroyHandle, this, &AProjectileBase::RemoveWhenDone, 3.0f);
}

void AProjectileBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// Ensure the fuze timer is cleared by using the timer handle
	GetWorld()->GetTimerManager().ClearTimer(DestroyHandle);

	// Alternatively you can clear ALL timers that belong to this (Actor) instance.
	//GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Log, TEXT("Direction is: %s"), *(direction.ToString()));

	FVector dirMult = direction * bulletSpeed;
	dirMult *= DeltaTime;

	AddActorWorldOffset(dirMult);
}

void AProjectileBase::RemoveWhenDone()
{
	Destroy();
}