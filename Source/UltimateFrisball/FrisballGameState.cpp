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

}

