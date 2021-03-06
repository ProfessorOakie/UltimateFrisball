// Fill out your copyright notice in the Description page of Project Settings.

#include "FrisbeeActorComponent.h"
#include "FrisbeePlayerActorComponent.h"

// Sets default values for this component's properties
UFrisbeeActorComponent::UFrisbeeActorComponent() :
	m_lastTeamWithPossession(-1)
	, m_justThrown(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UFrisbeeActorComponent::Throw(FVector direction, float power)
{
	ReleaseFromOnTop();

	UPrimitiveComponent* component = Cast<UPrimitiveComponent>(GetOwner()->FindComponentByClass<UPrimitiveComponent>());
	if (component)
	{
		FVector force = direction * power;
		component->AddImpulse(force);
		m_justThrown = true;
	}
}

void UFrisbeeActorComponent::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this->GetOwner()) && (OtherComp != NULL))
	{
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit: %s"), *OtherActor->GetName()));
		
		UFrisbeePlayerActorComponent* component = Cast<UFrisbeePlayerActorComponent>(OtherActor->FindComponentByClass<UFrisbeePlayerActorComponent>());
		if (component)
		{
			Catch(component, OtherActor->GetRootComponent());
		}
		else if (m_justThrown)
		{
			m_justThrown = false;
			OnTurnover();
		}

	}


}

// Called every frame
void UFrisbeeActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}



// Called when the game starts
void UFrisbeeActorComponent::BeginPlay()
{
	Super::BeginPlay();

	m_justThrown = false;

	UPrimitiveComponent* component = Cast<UPrimitiveComponent>(GetOwner()->GetComponentByClass(UPrimitiveComponent::StaticClass()));
	if (component)
	{
		component->OnComponentHit.AddDynamic(this, &UFrisbeeActorComponent::OnHit);
	}
}

bool UFrisbeeActorComponent::CheckCatchConditions(const UFrisbeePlayerActorComponent * attemptingHolder) const
{
	return attemptingHolder->GetTeam() != m_lastTeamWithPossession;
}

void UFrisbeeActorComponent::Catch(UFrisbeePlayerActorComponent * newHolder, USceneComponent * holderSceneComponent)
{
	if (CheckCatchConditions(newHolder))
	{
		currentHolder = newHolder;
		m_lastTeamWithPossession = newHolder->GetTeam();

		PlaceOntopOfComponent(holderSceneComponent);

		newHolder->OnStartHoldFrisbee(this);
	}
}

void UFrisbeeActorComponent::PlaceOntopOfComponent(USceneComponent* componentWhomstShallReceiveTheDisc)
{
	check(componentWhomstShallReceiveTheDisc);
	
	UPrimitiveComponent* component = Cast<UPrimitiveComponent>(GetOwner()->GetComponentByClass(UPrimitiveComponent::StaticClass()));
	if (component)
	{
		component->SetSimulatePhysics(false);
	}
	
	FAttachmentTransformRules rules = FAttachmentTransformRules::KeepRelativeTransform;
	rules.bWeldSimulatedBodies = false;
	GetOwner()->GetRootComponent()->AttachToComponent(componentWhomstShallReceiveTheDisc, rules);
	
	GetOwner()->SetActorRelativeLocation(FVector(0, 0, m_verticalOffsetOnHold));
}

void UFrisbeeActorComponent::ReleaseFromOnTop()
{
	GetOwner()->GetRootComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	UPrimitiveComponent* component = Cast<UPrimitiveComponent>(GetOwner()->GetComponentByClass(UPrimitiveComponent::StaticClass()));
	if (component)
	{
		component->SetSimulatePhysics(true);
	}
}

void UFrisbeeActorComponent::OnTurnover()
{
	
}
