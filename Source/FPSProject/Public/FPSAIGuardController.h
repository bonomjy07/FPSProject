// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FPSAIGuardController.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API AFPSAIGuardController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY()
	AActor* CurrentTarget;

public:
	// Patrol point 1.
	UPROPERTY()
	AActor* TargetActor1;

	// Patrol point 2.
	UPROPERTY()
	AActor* TargetActor2;

	// Patrol area between point1 and point2
	void GoToNextTargetPoint();

protected:
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

};
