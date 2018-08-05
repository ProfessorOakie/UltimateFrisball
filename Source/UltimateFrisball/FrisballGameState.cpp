// Fill out your copyright notice in the Description page of Project Settings.

#include "FrisballGameState.h"
#include "UnrealNetwork.h"

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
	// This function is only called on the server (where Role == ROLE_Authority), called over the network by clients.
	// We need to call SetSomeBool() to actually change the value of the bool now!
	// Inside that function, Role == ROLE_Authority, so it won't try to call ServerSetSomeBool() again.
	ServerTeamScore(teamThatScored);
}
