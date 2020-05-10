// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProjectGameStateBase.h"
#include "engine/World.h"
#include "FPSProjectPlayerController.h"
#include "Kismet/GameplayStatics.h"

void AFPSProjectGameStateBase::MulticastOnMissionCompleted_Implementation(APawn* InstigatorPawn, bool bMissionSuccess)
{
	UWorld* World = GetWorld();
	if (World)
	{
		for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
		{
			// Find locally controlled controller
			AFPSProjectPlayerController* PC = Cast<AFPSProjectPlayerController>(It->Get());
			if (PC && PC->IsLocalController())
			{
				// Display game-over widget
				PC->OnMissionComplemeted(InstigatorPawn, bMissionSuccess);

				// Disable player's input
				APawn* Pawn = PC->GetPawn();
				if (Pawn)
				{
					Pawn->DisableInput(PC);
				}
			}
		}
	}
}
