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

	void TeamScore(const int8 teamThatScored);
	UFUNCTION(reliable, server, WithValidation)
	void ServerTeamScore(const int8 teamThatScored);

	void OnKickoff();
	UFUNCTION(reliable, server, WithValidation)
	void ServerOnKickoff();

	void TestForGameStart();

	UPROPERTY(Replicated)
	bool m_IsKickoff = true;

protected:
	UPROPERTY(Replicated, BlueprintReadOnly)
	int32 team1Score;
	
	UPROPERTY(Replicated, BlueprintReadOnly)
	int32 team2Score;

	bool m_IsPlaying = true;


	uint8 AssignedPlayers = 0;
	void AssignKickoffLocations();
	UFUNCTION(reliable, server, WithValidation)
	void ServerAssignKickoffLocations();
	void ResetToKickoffLocations();
	UFUNCTION(reliable, server, WithValidation)
	void ServerResetToKickoffLocations();
};
