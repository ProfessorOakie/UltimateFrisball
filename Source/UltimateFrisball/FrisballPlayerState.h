// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FrisballPlayerState.generated.h"

class AFrisballKickoffLocations;
class AUltimateFrisballPawn;
UCLASS()
class ULTIMATEFRISBALL_API AFrisballPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated)
	bool m_TeamNumber1 = false;
	UPROPERTY(Replicated)
	bool m_TeamAssigned = false;
};
