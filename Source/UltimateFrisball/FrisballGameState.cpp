// Fill out your copyright notice in the Description page of Project Settings.

#include "FrisballGameState.h"
#include "UnrealNetwork.h"
#include "UltimateFrisballPawn.h"

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
}

bool AFrisballGameState::ServerTeamScore_Validate(const int8 teamThatScored)
{
	return true;
}

void AFrisballGameState::ServerTeamScore_Implementation(const int8 teamThatScored)
{
	//call the function on the server
	TeamScore(teamThatScored);
}

void AFrisballGameState::PopulateTeams()
{
	for (int32 i = 0; i < PlayerArray.Num(); i++)
	{
		/*AUltimateFrisballPawn* TempFrisballPawn = Cast<AUltimateFrisballPawn>(PlayerArray[i]);
		if (TempFrisballPawn)
		{
		
		}
		*/
	}
}

