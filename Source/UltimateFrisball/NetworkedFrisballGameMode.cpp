// Fill out your copyright notice in the Description page of Project Settings.

#include "NetworkedFrisballGameMode.h"
#include "FrisballGameState.h"

void ANetworkedFrisballGameMode::BeginPlay()
{
	Super::BeginPlay();
	Cast<AFrisballGameState>(GameState)->m_CanScore = true;
}