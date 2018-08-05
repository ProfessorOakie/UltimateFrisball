// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "NetworkedFrisballGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ULTIMATEFRISBALL_API ANetworkedFrisballGameMode : public AGameMode
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;
private:
	void ResetOnScore();
	void ResetPlayerPositions();
	void ResetGame();
	void EndGame();
};
	
	
