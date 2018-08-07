// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "FrisballKickoffLocations.generated.h"

/**
 * 
 */
UCLASS()
class ULTIMATEFRISBALL_API AFrisballKickoffLocations : public APlayerStart
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Teams")
	bool m_Team1Location;	
};
