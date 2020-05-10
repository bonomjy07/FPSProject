// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

UENUM(BlueprintType)
enum class EAIGuardState : uint8
{
	Idle,
	Suspicious,
	Alert
};

UCLASS()
class FPSPROJECT_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(EditInstanceOnly, Category = "AI")
	bool bIsOnPatrol;

	UPROPERTY()
	AActor* CurrentPatrol;

	UPROPERTY(EditInstanceOnly, Category = "AI")
	AActor* FirstPatrolPoint;

	UPROPERTY(EditInstanceOnly, Category = "AI")
	AActor* SecondPatrolPoint;

	// It's used to make AI look where it was looking at
	FRotator OriginalRotation;

	// Timer for resetting AI's rotation
	FTimerHandle RotationTimer;

	// This represetns guard state
	EAIGuardState GuardState;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the AI heard noise after 3 seconds
	UFUNCTION()
	void ResetOriginalRotation();

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnGuardStateChanged(EAIGuardState NewGuardState);

	void MoveToNextPoint();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Setter for guard state
	void SetGuardState(EAIGuardState NewGuardState);
};
