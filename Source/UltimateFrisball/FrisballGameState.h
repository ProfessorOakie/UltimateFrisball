// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "FrisballGameState.generated.h"

/**
 * 
 */
class AUltimateFrisballPawn;
UCLASS()
class ULTIMATEFRISBALL_API AFrisballGameState : public AGameState
{
	GENERATED_BODY()

public:
	void SetTimer(const float CurrentTime);

	void TeamScore(const int8 teamThatScored);
	UFUNCTION(reliable, server, WithValidation)
	void ServerTeamScore(const int8 teamThatScored);

	void PopulateTeams();

	UPROPERTY(Replicated)
	bool m_CanScore;

protected:
	UPROPERTY(Replicated, BlueprintReadOnly)
	int32 team1Score;
	
	UPROPERTY(Replicated, BlueprintReadOnly)
	int32 team2Score;

	UPROPERTY(Replicated, BlueprintReadOnly)
	float TimeLeft;

	bool m_IsPlaying = true;

	TArray<AUltimateFrisballPawn*> Team1Players;
	TArray<AUltimateFrisballPawn*> Team2Players;

	
};
