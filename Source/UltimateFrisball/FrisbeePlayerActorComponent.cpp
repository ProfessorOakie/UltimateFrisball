// Fill out your copyright notice in the Description page of Project Settings.

#include "FrisbeePlayerActorComponent.h"


// Sets default values for this component's properties
UFrisbeePlayerActorComponent::UFrisbeePlayerActorComponent()
	: m_holdingFrisbee(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFrisbeePlayerActorComponent::BeginPlay()
{
	Super::BeginPlay();

	AUltimateFrisballPawn* pawn = Cast<AUltimateFrisballPawn>(GetOwner());
	if (pawn)
	{
		m_pawn = pawn;
	}
	
}


// Called every frame
void UFrisbeePlayerActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFrisbeePlayerActorComponent::OnStartHoldFrisbee()
{
	m_holdingFrisbee = true;

	if (m_pawn)
	{
		m_pawn->OnHandbrakePressed();
	}

}

void UFrisbeePlayerActorComponent::OnStopHoldFrisbee()
{
	m_holdingFrisbee = false;


	if (m_pawn)
	{
		m_pawn->OnHandbrakeReleased();
	}
}

