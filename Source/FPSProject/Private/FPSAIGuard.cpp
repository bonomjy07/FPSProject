// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "FPSProjectGameMode.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();

	// Save the its orginal rotation
	OriginalRotation = GetActorRotation();
	
}

void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
	{
		return;
	}

	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 64.f, 8, FColor::Green, false, 2.f);

	// When the player is found, game is over
	UWorld* World = GetWorld();
	if (World)
	{
		AFPSProjectGameMode* GM = Cast<AFPSProjectGameMode>(World->GetAuthGameMode());
		if (GM)
		{
			GM->CompleteMission(SeenPawn, false);
		}
	}
}

void AFPSAIGuard::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	DrawDebugSphere(GetWorld(), Location, 64.f, 8, FColor::Red, false, 2.f);

	// Get direction
	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	// Get rotation from direction
	FRotator Rotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	FRotator NoiseLookAt = FRotator(0.f, Rotation.Yaw, 0.f);
	SetActorRotation(NoiseLookAt);

	// Set timer to reset its rotation
	GetWorldTimerManager().SetTimer(RotationTimer, this, &AFPSAIGuard::ResetOriginalRotation, 2.f, false);
}

void AFPSAIGuard::ResetOriginalRotation()
{
	SetActorRotation(OriginalRotation);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSAIGuard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

