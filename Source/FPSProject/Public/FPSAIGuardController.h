// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FPSAIGuardController.generated.h"

/**
 * 
 * 사용하지 말 것.
 * 망작.
 */
UCLASS()
class FPSPROJECT_API AFPSAIGuardController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY()
	AActor* CurrentTarget;

public:
	UPROPERTY()
	AActor* TargetActor1;

	UPROPERTY()
	AActor* TargetActor2;

	void GoToNextTargetPoint();

protected:
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

};
