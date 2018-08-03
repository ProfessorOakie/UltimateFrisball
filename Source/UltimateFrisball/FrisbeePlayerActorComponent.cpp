// Fill out your copyright notice in the Description page of Project Settings.

#include "FrisbeePlayerActorComponent.h"
#include "FrisbeeActorComponent.h"


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

void UFrisbeePlayerActorComponent::OnStartHoldFrisbee(UFrisbeeActorComponent* heldFrisbee)
{
	m_holdingFrisbee = true;
	m_heldFrisbee = heldFrisbee;

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

void UFrisbeePlayerActorComponent::OnThrow()
{
	//TODO actually be able to aim (from param maybe?)
	FVector throwingDirection = GetOwner()->GetRootComponent()->GetForwardVector();

	m_heldFrisbee->Throw(throwingDirection, m_throwingPower);
}

const bool UFrisbeePlayerActorComponent::IsHoldingFrisbee()
{
	return m_holdingFrisbee;
}

void UFrisbeePlayerActorComponent::AssignTeam(const int8 team)
{
	TeamNumber = team;
}

const int8 UFrisbeePlayerActorComponent::GetTeam()
{
	return TeamNumber;
}

