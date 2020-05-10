// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSProjectPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API AFPSProjectPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	/** Create game-over widget and add it to view-port */
	UFUNCTION(BlueprintImplementableEvent, Category = "PlayerController")
	void OnMissionComplemeted(APawn* InstigatorPawn, bool bMissionSuccess);
};
