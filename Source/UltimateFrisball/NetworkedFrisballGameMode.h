// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "NetworkedFrisballGameMode.generated.h"

/**
 * 
 */
class AFrisballPlayerStart;
UCLASS()
class ULTIMATEFRISBALL_API ANetworkedFrisballGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	ANetworkedFrisballGameMode();
	virtual void BeginPlay() override;
	AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	bool ShouldSpawnAtStartSpot(AController * Player) override { return false; };

private:
		void DelayStartMatch();
		uint8 numplayers = 0;
		TArray<AFrisballPlayerStart*> Locations;
		bool populated = false;
};
	
	

