// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSProjectGameMode.generated.h"

UCLASS(minimalapi)
class AFPSProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	/** Player's view target will be this if game is somehow over */
	UPROPERTY(EditDefaultsOnly, Category = "Spectator")
	TSubclassOf<AActor> ViewTargetClass;

public:
	AFPSProjectGameMode();

	/** Finish the current game */
	void CompleteMission(APawn* InstigatorPawn, bool bIsMissionSuccess);
};



