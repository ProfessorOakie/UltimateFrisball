// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "FrisballPlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class ULTIMATEFRISBALL_API AFrisballPlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:

	bool m_Available =true;
};
