// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UltimateFrisballPawn.h"
#include "FrisbeePlayerActorComponent.generated.h"

class UFrisbeeActorComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ULTIMATEFRISBALL_API UFrisbeePlayerActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFrisbeePlayerActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OnStartHoldFrisbee(UFrisbeeActorComponent* heldFrisbee);
	void OnStopHoldFrisbee();

	void OnThrow();

private: 

	bool m_holdingFrisbee;
	UFrisbeeActorComponent* m_heldFrisbee;

	AUltimateFrisballPawn* m_pawn;

	UPROPERTY(EditAnywhere, Category=Frisbee)
	float m_throwingPower;

	
};
