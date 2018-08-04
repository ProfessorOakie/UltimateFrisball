// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "UltimateFrisballGameMode.h"
#include "UltimateFrisballPawn.h"
#include "UltimateFrisballHud.h"

AUltimateFrisballGameMode::AUltimateFrisballGameMode()
{
	DefaultPawnClass = AUltimateFrisballPawn::StaticClass();
	HUDClass = AUltimateFrisballHud::StaticClass();
}

void AUltimateFrisballGameMode::Score(int8 team)
{
	if (team == 1)
	{
		m_team1Score++;
	}
	else if (team == 2)
	{
		m_team2Score++;
	}
	else
	{
		//error here
	}

	ResetOnScore();
}

void AUltimateFrisballGameMode::ResetOnScore()
{
	//this->Reset();
}
