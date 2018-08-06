// Fill out your copyright notice in the Description page of Project Settings.

#include "FrisbeePlayerActorComponent.h"
#include "FrisbeeActorComponent.h"
#include "UnrealNetwork.h"


// Sets default values for this component's properties
UFrisbeePlayerActorComponent::UFrisbeePlayerActorComponent()
	: m_heldFrisbee(nullptr)
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
	m_heldFrisbee = heldFrisbee;

	if (m_pawn)
	{
		m_pawn->OnHandbrakePressed();
	}
}

void UFrisbeePlayerActorComponent::OnStopHoldFrisbee()
{
	m_heldFrisbee = nullptr;

	if (m_pawn)
	{
		m_pawn->OnHandbrakeReleased();
	}
}

void UFrisbeePlayerActorComponent::Server_OnThrow_Implementation()
{
	if (m_heldFrisbee)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("UFrisbeePlayerActorComponent: Server_OnThrow_Implementation")));


		//TODO actually be able to aim (from param maybe?)
		FVector throwingDirection = GetOwner()->GetRootComponent()->GetForwardVector();

		m_heldFrisbee->Throw(throwingDirection, m_throwingPower);
	}
}

bool UFrisbeePlayerActorComponent::Server_OnThrow_Validate()
{
	return true;
}

bool UFrisbeePlayerActorComponent::IsHoldingFrisbee() const
{
	return m_heldFrisbee != nullptr;
}

void UFrisbeePlayerActorComponent::AssignTeam(const int8 team)
{
	TeamNumber = team;
}

int8 UFrisbeePlayerActorComponent::GetTeam() const
{
	return TeamNumber;
}

