// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FPSProjectGameMode.h"
#include "FPSProjectHUD.h"
#include "FPSProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AFPSProjectGameMode::AFPSProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSProjectHUD::StaticClass();
}

void AFPSProjectGameMode::CompleteMission(APawn* InstigatorPawn, bool bIsMissionSuccess)
{
	if (InstigatorPawn)
	{
		// Disable the player's input
		InstigatorPawn->DisableInput(nullptr);

		// Change the player's view point target
		if (ViewTargetClass)
		{
			if (AActor* ViewTarget = UGameplayStatics::GetActorOfClass(this, ViewTargetClass))
			{
				if (APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController()))
				{
					PC->SetViewTargetWithBlend(ViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("View Target Class for new spector is not valid, Please update the class in BP_GameMode"));
		}
	}

	OnMissionCompleted(InstigatorPawn, bIsMissionSuccess);
}
