// Fill out your copyright notice in the Description page of Project Settings.

#include "SimpleNetworkTransformComponent.h"
#include "UnrealNetwork.h"


// Sets default values for this component's properties
USimpleNetworkTransformComponent::USimpleNetworkTransformComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicated(true);
	// ...
}


// Called when the game starts
void USimpleNetworkTransformComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	check(GetOwner());
	movingComponent = GetOwner()->GetRootComponent();

	GetVariables();
}


// Called every frame
void USimpleNetworkTransformComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetVariables();
}

void USimpleNetworkTransformComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Tell the engine to call the OnRep_WorldPos each time variable changes
	DOREPLIFETIME(USimpleNetworkTransformComponent, WorldPos);
	DOREPLIFETIME(USimpleNetworkTransformComponent, Rotation);

}

void USimpleNetworkTransformComponent::OnRep_WorldPos()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("SimpleNetworkTransform: Replicated WorldPos")));

	if (movingComponent)
	{
		movingComponent->SetWorldLocation(WorldPos, true, nullptr, ETeleportType::TeleportPhysics);
	}
}

void USimpleNetworkTransformComponent::OnRep_Rotation()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("SimpleNetworkTransform: Replicated Rotation")));

	if (movingComponent)
	{
		movingComponent->SetWorldRotation(Rotation, true, nullptr, ETeleportType::TeleportPhysics);
	}
}



void USimpleNetworkTransformComponent::GetVariables()
{
	if (movingComponent)
	{
		WorldPos = movingComponent->GetComponentLocation();
		Rotation = movingComponent->GetComponentRotation();
	}
}