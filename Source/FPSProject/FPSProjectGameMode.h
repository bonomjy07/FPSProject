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
	UPROPERTY(EditDefaultsOnly, Category = "Spectator")
	TSubclassOf<AActor> ViewTargetClass;

public:
	AFPSProjectGameMode();

	void CompleteMission(APawn* InstigatorPawn, bool bIsMissionSuccess);

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void OnMissionCompleted(APawn* InstigatorPawn, bool bIsMissionSuccess);

};



