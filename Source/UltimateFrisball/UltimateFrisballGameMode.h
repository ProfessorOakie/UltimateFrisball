// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameModeBase.h"
#include "UltimateFrisballGameMode.generated.h"

UCLASS(minimalapi)
class AUltimateFrisballGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUltimateFrisballGameMode();

	bool m_CanScore;

	void Score(int8 team);

	uint32 m_team1Score;
	uint32 m_team2Score;
	
private:
	void ResetOnScore();
	void ResetPlayerPositions();
	void ResetGame();
	void EndGame();
};




