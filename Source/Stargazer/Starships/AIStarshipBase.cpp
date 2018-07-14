// Fill out your copyright notice in the Description page of Project Settings.

#include "AIStarshipBase.h"
#include "ProjectileBase.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAIStarshipBase::AAIStarshipBase(const FObjectInitializer &objectInitializer) : Super(objectInitializer)
{

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Lul names dont matter"));
	WidgetComponent->SetDrawSize(FVector2D(600, 50));
}

// Called when the game starts or when spawned
void AAIStarshipBase::BeginPlay()
{
	Super::BeginPlay();

}

void AAIStarshipBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

// Called every frame
void AAIStarshipBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerCameraManager *camManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
	FRotator rot = UKismetMathLibrary::FindLookAtRotation(WidgetComponent->GetComponentLocation(), camManager->GetCameraLocation());
	WidgetComponent->SetWorldRotation(rot);
}

// Called to bind functionality to input
void AAIStarshipBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AAIStarshipBase::ToggleShoot(bool status)
{
	bool result = false;

	if (isFiring != status)
	{
		isFiring = status;
		result = true;
		if (isFiring)
		{
			GetWorld()->GetTimerManager().SetTimer(ShootHandle, this, &AAIStarshipBase::Shoot, fireRate, true);
			//UE_LOG(LogTemp, Log, TEXT("Fire ON, FireRate is: %f"), GetWorld()->GetTimerManager().GetTimerRate(ShootHandle));
		}
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(ShootHandle);
			//UE_LOG(LogTemp, Log, TEXT("Fire OFF"));
		}
	}
	
	return result;
}

void AAIStarshipBase::Shoot()
{
	if (Controller != NULL)
	{
		FVector location = GetActorLocation() + GetActorForwardVector() * shipHalfLength;
		FRotator rotation = GetActorRotation(); // (0.0f, 0.0f, 0.0f);
		FActorSpawnParameters spawnInfo;

		if (!ensure(ProjectileSpawn)) { return; }

		AProjectileBase *projBase = GetWorld()->SpawnActor<AProjectileBase>(ProjectileSpawn, location, rotation, spawnInfo);

		projBase->direction = GetActorForwardVector();
		projBase->ownerStarship = this;
	}
}

void AAIStarshipBase::ModifyValues(int32 healthChange, int32 shieldChange)
{
	shipHealth += healthChange;
	shipShields += shieldChange;
}