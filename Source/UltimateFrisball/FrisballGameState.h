// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "FrisballGameState.generated.h"

/**
 * 
 */
UCLASS()
class ULTIMATEFRISBALL_API AFrisballGameState : public AGameState
{
	GENERATED_BODY()

protected:
	UPROPERTY(Replicated, BlueprintReadOnly)
	int32 team1Score;
	
	UPROPERTY(Replicated, BlueprintReadOnly)
	int32 team2Score;

	UPROPERTY(Replicated)
	float TimeLeft;
};
