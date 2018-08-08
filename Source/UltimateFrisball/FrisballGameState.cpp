// Fill out your copyright notice in the Description page of Project Settings.

#include "FrisballGameState.h"
#include "UnrealNetwork.h"
#include "UltimateFrisballPawn.h"
#include "EngineMinimal.h"
#include "EngineUtils.h"
#include "FrisballKickoffLocations.h"
#include "FrisballPlayerState.h"
#include "FrisbeePlayerActorComponent.h"
#include "SimpleNetworkTransformComponent.h"
#include "FrisballSelectTeam.h"

void AFrisballGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to everyone
	DOREPLIFETIME(AFrisballGameState, team1Score);
	DOREPLIFETIME(AFrisballGameState, team2Score);
	DOREPLIFETIME(AFrisballGameState, TimeLeft);
	DOREPLIFETIME(AFrisballGameState, m_CanScore);


}

void AFrisballGameState::TeamScore(const int8 teamThatScored)
{
	m_CanScore = false;

	if (teamThatScored == 1)
	{
		team1Score++;  
	}
	else if (teamThatScored == 2)
	{ 
		team2Score++;
	}

	if (Role < ROLE_Authority)
	{
		ServerTeamScore(teamThatScored);
	}

	ResetToKickoffLocations();
}

void AFrisballGameState::TestForGameStart()
{
	AssignedPlayers++;
	if (AssignedPlayers >= 2 && AssignedPlayers == PlayerArray.Num())
	{
		//assign start/reset locations
		AssignKickoffLocations();
		//Move to KickoffLocations
		ResetToKickoffLocations();
		//Start the game/kickoff
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Start The Game Boss"));
		for(TActorIterator<AFrisballSelectTeam> StartItr(GetWorld()); StartItr; ++StartItr)
		{
			Destroy(*StartItr);
		}
	}
	

}

void AFrisballGameState::AssignKickoffLocations()
{
	TQueue<AFrisballKickoffLocations*> Team1Locations;
	TQueue<AFrisballKickoffLocations*> Team2Locations;
	
	for (TActorIterator<AFrisballKickoffLocations> StartItr(GetWorld()); StartItr; ++StartItr)
	{
		AFrisballKickoffLocations* TempLocation = Cast<AFrisballKickoffLocations>(*StartItr);
		if (TempLocation)
		{
			if (TempLocation->m_Team1Location)
			{
				Team1Locations.Enqueue(*StartItr);
			}
			else
			{
				Team2Locations.Enqueue(*StartItr);
			}
		}
	}
	for (TActorIterator<AUltimateFrisballPawn> StartItr(GetWorld()); StartItr; ++StartItr)
	{
		AUltimateFrisballPawn* TempPlayer = Cast<AUltimateFrisballPawn>(*StartItr);
		if (TempPlayer)
		{
			if (TempPlayer->FrisbeeActorComponent->GetTeam()==1)
			{
				AFrisballKickoffLocations* TempLoc;
				Team1Locations.Peek(TempLoc);
				TempPlayer->FrisbeeActorComponent->KickoffLocation = TempLoc->GetActorLocation();
				Team1Locations.Pop();
			}
			else
			{
				AFrisballKickoffLocations* TempLoc;
				Team2Locations.Peek(TempLoc);
				TempPlayer->FrisbeeActorComponent->KickoffLocation = TempLoc->GetActorLocation();
				Team2Locations.Pop();
			}
		}
	}
}




bool AFrisballGameState::ServerTeamScore_Validate(const int8 teamThatScored)
{
	return true;
}
void AFrisballGameState::ResetToKickoffLocations()
{
	for (TActorIterator<AUltimateFrisballPawn> StartItr(GetWorld()); StartItr; ++StartItr)
	{
		(*StartItr)->SetActorLocation((*StartItr)->FrisbeeActorComponent->KickoffLocation, false, nullptr, ETeleportType::TeleportPhysics);
	}
	if (Role < ROLE_Authority)
	{
		ServerResetToKickoffLocations();
	}
}

void AFrisballGameState::ServerTeamScore_Implementation(const int8 teamThatScored)
{
	//call the function on the server
	TeamScore(teamThatScored);
}

void AFrisballGameState::ServerResetToKickoffLocations_Implementation()
{
	ResetToKickoffLocations();
}

bool AFrisballGameState::ServerResetToKickoffLocations_Validate()
{
	return true;
}