// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIGuardController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"

void AFPSAIGuardController::GoToNextTargetPoint()
{
	if (CurrentTarget == nullptr || CurrentTarget == TargetActor2)
	{
		CurrentTarget = TargetActor1;
	}
	else
	{ 
		CurrentTarget = TargetActor2;
	}

	if (CurrentTarget)
	{
		MoveToActor(CurrentTarget);
	}
}

void AFPSAIGuardController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	if (Result.IsSuccess())
	{
		GoToNextTargetPoint();
	}
}
