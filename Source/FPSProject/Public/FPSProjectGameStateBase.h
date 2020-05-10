// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FPSProjectGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API AFPSProjectGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	/** Client-Side function: Each client creates widget to display game is over */
	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnMissionCompleted(APawn* InstigatorPawn, bool bMissionSuccess);
	void MulticastOnMissionCompleted_Implementation(APawn* InstigatorPawn, bool bMissionSuccess);
};
