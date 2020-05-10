// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "FPSProjectGameMode.h"
#include "AIController.h"
#include "FPSAIGuardController.h"
#include "NavigationSystem.h"
#include "Net/UnrealNetwork.h"
//#include "Blueprint/AIBlueprintHelperLibrary.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create pawn sensing component
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);

	// Set default guard state
	GuardState = EAIGuardState::Idle;
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();

	if (Role == ROLE_Authority)
	{
		// Save the its orginal rotation
		OriginalRotation = GetActorRotation();

		// Pass the patrols actors to controller
		AFPSAIGuardController* AC = Cast<AFPSAIGuardController>(GetController());
		if (AC)
		{
			AC->TargetActor1 = FirstPatrolPoint;
			AC->TargetActor2 = SecondPatrolPoint;
			AC->GoToNextTargetPoint();
		}
	}
}

void AFPSAIGuard::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFPSAIGuard, GuardState);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSAIGuard::ResetOriginalRotation()
{
	// Player is already caught, No turning back
	if (GuardState == EAIGuardState::Alert)
	{
		return;
	}

	// Reset actor's rotation
	SetActorRotation(OriginalRotation);

	// Reset actor's gaurd-state
	SetGuardState(EAIGuardState::Idle);

	// Continue to move again
	AFPSAIGuardController* AC = Cast<AFPSAIGuardController>(GetController());
	if (AC)
	{
		AC->GoToNextTargetPoint();
	}
}

void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
	{
		return;
	}

	// Debug ...
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

	// Set A.I's state 'Alert'
	SetGuardState(EAIGuardState::Alert);

	// Stop movement
	AFPSAIGuardController* AC = Cast<AFPSAIGuardController>(GetController());
	if (AC)
	{
		AC->StopMovement();
	}

}

void AFPSAIGuard::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	// Debug ...
	DrawDebugSphere(GetWorld(), Location, 64.f, 8, FColor::Red, false, 2.f);

	// Player is already caught, No turning back
	if (GuardState == EAIGuardState::Alert)
	{
		return;
	}

	// Get direction
	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();
	// Get rotation from direction
	FRotator Rotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	FRotator NoiseLookAt = FRotator(0.f, Rotation.Yaw, 0.f);
	SetActorRotation(NoiseLookAt);
	// Set timer to reset its rotation
	GetWorldTimerManager().ClearTimer(RotationTimer);
	GetWorldTimerManager().SetTimer(RotationTimer, this, &AFPSAIGuard::ResetOriginalRotation, 2.f, false);

	// New state is suspicious
	SetGuardState(EAIGuardState::Suspicious);

	AFPSAIGuardController* AC = Cast<AFPSAIGuardController>(GetController());
	if (AC)
	{
		AC->StopMovement();
	}
}

void AFPSAIGuard::SetGuardState(EAIGuardState NewGuardState)
{
	if (Role == ROLE_Authority)
	{
		GuardState = NewGuardState;

		OnRep_GuardState(); // Fake function call for server-side
		//OnGuardStateChanged(NewGuardState);
	}
}

void AFPSAIGuard::OnRep_GuardState()
{
	OnGuardStateChanged(GuardState);
}

//void AFPSAIGuard::MoveToNextPoint()
//{
//	if (CurrentPatrol == nullptr || CurrentPatrol == SecondPatrolPoint)
//	{
//		CurrentPatrol = FirstPatrolPoint;
//	}
//	else
//	{
//		CurrentPatrol = SecondPatrolPoint;
//	}
//
//	AAIController* AC = Cast<AAIController>(GetController());
//	if (AC)
//	{
//		AC->MoveToActor(CurrentPatrol);
//	}
//	//UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), CurrentPatrol);
//}
//
//