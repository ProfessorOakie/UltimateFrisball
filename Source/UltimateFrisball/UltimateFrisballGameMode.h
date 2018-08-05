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
	virtual void BeginPlay() override;
private:
	void ResetOnScore();
	void ResetPlayerPositions();
	void ResetGame();
	void EndGame();
};




