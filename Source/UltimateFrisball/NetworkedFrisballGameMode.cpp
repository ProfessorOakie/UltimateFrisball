// Fill out your copyright notice in the Description page of Project Settings.

#include "NetworkedFrisballGameMode.h"
#include "FrisballGameState.h"
#include "UltimateFrisballPawn.h"
#include "UltimateFrisballHud.h"
#include "FrisballPlayerState.h"
#include "UltimateFrisballPawn.h"
#include "FrisballPlayerStart.h"
#include "EngineUtils.h"
#include "UnrealNetwork.h"
#include "EngineMinimal.h"

ANetworkedFrisballGameMode::ANetworkedFrisballGameMode()
{
	DefaultPawnClass = AUltimateFrisballPawn::StaticClass();
	HUDClass = AUltimateFrisballHud::StaticClass();
	PlayerStateClass = AFrisballPlayerState::StaticClass();
	GameStateClass = AFrisballGameState::StaticClass();
	DefaultPawnClass = AUltimateFrisballPawn::StaticClass();
	
	bDelayedStart = true;
}
void ANetworkedFrisballGameMode::BeginPlay()
{
	
	Super::BeginPlay();
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &ANetworkedFrisballGameMode::DelayStartMatch, 2.0f, false);

	
}

AActor * ANetworkedFrisballGameMode::ChoosePlayerStart_Implementation(AController * Player)
{
	if (!populated)
	{
		for (TActorIterator<AFrisballPlayerStart> StartItr(GetWorld()); StartItr; ++StartItr)
		{
			Locations.Add(*StartItr);
		}
		populated = true;
	}

	if(Player)
	{
		AFrisballPlayerState* State = Cast<AFrisballPlayerState>(Player->PlayerState);
		if (State && Player->StartSpot != nullptr)
		{
				int index = FMath::RandRange(0, Locations.Num() - 1);
				AFrisballPlayerStart* temp = Locations[index];
				Player->StartSpot = temp;
				Locations.Remove(temp);
				return temp;
		}
	}
	return nullptr;
	
}



void ANetworkedFrisballGameMode::DelayStartMatch()
{
	StartMatch();
}
