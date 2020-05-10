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

	// Patrol point1.
	UPROPERTY(EditInstanceOnly, Category = "AI")
	AActor* FirstPatrolPoint;

	// Patrol point2.
	UPROPERTY(EditInstanceOnly, Category = "AI")
	AActor* SecondPatrolPoint;

	// It's used to make AI look where it was looking at
	FRotator OriginalRotation;

	// Timer for resetting AI's rotation
	FTimerHandle RotationTimer;

	// This represetns guard state
	UPROPERTY(ReplicatedUsing = OnRep_GuardState)
	EAIGuardState GuardState;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray < FLifetimeProperty >& OutLifetimeProps) const override;

	// Called when the AI heard noise after 3 seconds
	UFUNCTION()
	void ResetOriginalRotation();

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	// Display the widget that what AI's state is.
	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnGuardStateChanged(EAIGuardState NewGuardState);

	// Called on client side when GuardState is changed 
	UFUNCTION()
	void OnRep_GuardState();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Setter for guard state
	void SetGuardState(EAIGuardState NewGuardState);
};
