// Fill out your copyright notice in the Description page of Project Settings.

#include "FrisbeePlayerActorComponent.h"
#include "FrisbeeActorComponent.h"
#include "UnrealNetwork.h"
#include "SimpleNetworkTransformComponent.h"
#include "FrisballGameState.h"
#include "UnrealNetwork.h"
#include "EngineMinimal.h"

void UFrisbeePlayerActorComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	DOREPLIFETIME(UFrisbeePlayerActorComponent, m_heldFrisbee);
	DOREPLIFETIME(UFrisbeePlayerActorComponent, TeamNumber);
	DOREPLIFETIME(UFrisbeePlayerActorComponent, Team2Material);
}

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
	if (GetTeam() == 2)
	{
		UpdateMaterial(Team2Material);
	}
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
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("UFrisbeePlayerActorComponent: Server_OnThrow_Implementation")));

		//TODO actually be able to aim (from param maybe?)
		FVector throwingDirection = GetOwner()->GetRootComponent()->GetForwardVector();

		m_heldFrisbee->Throw(throwingDirection, m_throwingPower);
		AFrisballGameState* GameState = Cast<AFrisballGameState>(GetWorld()->GetGameState());
		OnStopHoldFrisbee();
		if (GameState)
		{
			//kickoff!
			if (GameState->m_IsKickoff)
			{
				GameState->OnKickoff();
			}
		}
	}
}

bool UFrisbeePlayerActorComponent::Server_OnThrow_Validate()
{
	return true;
}

void UFrisbeePlayerActorComponent::Server_OnResetCar_Implementation()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("UFrisbeePlayerActorComponent: Server_OnResetCar_Implementation")));

	GetOwner()->GetRootComponent()->SetWorldRotation(FRotator::ZeroRotator, false, nullptr, ETeleportType::ResetPhysics);

	USimpleNetworkTransformComponent* component = GetOwner()->FindComponentByClass<USimpleNetworkTransformComponent>();
	if (component)
	{
		component->OverrideRotation(FRotator::ZeroRotator);
	}
}

bool UFrisbeePlayerActorComponent::Server_OnResetCar_Validate()
{
	return true;
}

void UFrisbeePlayerActorComponent::Server_OnJump_Implementation()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("UFrisbeePlayerActorComponent: Server_OnJump_Implementation")));

	UPrimitiveComponent* component = Cast<UPrimitiveComponent>(GetOwner()->FindComponentByClass<UPrimitiveComponent>());
	if (component)
	{
		FVector force = FVector::UpVector * m_jumpingPower;
		component->AddImpulse(force);
	}
}

bool UFrisbeePlayerActorComponent::Server_OnJump_Validate()
{
	return true;
}

void UFrisbeePlayerActorComponent::Server_RotateRight_Implementation(float Val)
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("UFrisbeePlayerActorComponent: Server_RotateRight_Implementation")));

	UPrimitiveComponent* component = Cast<UPrimitiveComponent>(GetOwner()->FindComponentByClass<UPrimitiveComponent>());
	if (component)
	{
		FVector force = FVector::UpVector * m_rotateRightPower * Val;
		component->AddAngularImpulseInRadians(force);
	}
}

bool UFrisbeePlayerActorComponent::Server_RotateRight_Validate(float Val)
{
	return true;
}

void UFrisbeePlayerActorComponent::Server_RotateForward_Implementation(float Val)
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("UFrisbeePlayerActorComponent: Server_RotateForward_Implementation")));

	UPrimitiveComponent* component = Cast<UPrimitiveComponent>(GetOwner()->FindComponentByClass<UPrimitiveComponent>());
	if (component)
	{
		FVector force = component->GetRightVector() * m_rotateForwardPower * Val;
		component->AddAngularImpulseInRadians(force);
	}
}

bool UFrisbeePlayerActorComponent::Server_RotateForward_Validate(float Val)
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

void UFrisbeePlayerActorComponent::UpdateMaterial(UMaterial * SecondMaterial)
{

	Team2Material = SecondMaterial;
	AUltimateFrisballPawn* TempOwner = Cast<AUltimateFrisballPawn>(GetOwner());
	TempOwner->GetMesh()->SetMaterial(0, Team2Material);
	TempOwner->GetMesh()->SetMaterial(1, Team2Material);
	TempOwner->GetMesh()->SetMaterial(2, Team2Material);
	if (GetOwner()->Role < ROLE_Authority)
	{
		ServerUpdateMaterial(SecondMaterial);
	}
}

void UFrisbeePlayerActorComponent::ServerUpdateMaterial_Implementation(UMaterial * SecondMaterial)
{
	UpdateMaterial(SecondMaterial);
}
bool UFrisbeePlayerActorComponent::ServerUpdateMaterial_Validate(UMaterial * SecondMaterial)
{
	return true;
}
void UFrisbeePlayerActorComponent::OnRep_ColorChange()
{
	AUltimateFrisballPawn* TempOwner = Cast<AUltimateFrisballPawn>(GetOwner());
	TempOwner->GetMesh()->SetMaterial(0, Team2Material);
	TempOwner->GetMesh()->SetMaterial(1, Team2Material);
	TempOwner->GetMesh()->SetMaterial(2, Team2Material);
}

