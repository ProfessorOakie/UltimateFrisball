// Fill out your copyright notice in the Description page of Project Settings.

#include "FrisbeeActorComponent.h"

// Sets default values for this component's properties
UFrisbeeActorComponent::UFrisbeeActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UFrisbeeActorComponent::Throw(FVector direction, float power)
{
	UPrimitiveComponent* component = Cast<UPrimitiveComponent>(GetOwner()->FindComponentByClass<UPrimitiveComponent>());
	if (component)
	{
		FVector force = direction * power;
		component->AddImpulse(force);
	}
}

void UFrisbeeActorComponent::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this->GetOwner()) && (OtherComp != NULL))
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit: %s"), *OtherActor->GetName()));
		
		UFrisbeePlayerActorComponent* component = Cast<UFrisbeePlayerActorComponent>(OtherActor->FindComponentByClass<UFrisbeePlayerActorComponent>());
		if (component)
		{
			Catch(component, OtherActor->GetRootComponent());
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

	UPrimitiveComponent* component = Cast<UPrimitiveComponent>(GetOwner()->GetComponentByClass(UPrimitiveComponent::StaticClass()));
	if (component)
	{
		component->OnComponentHit.AddDynamic(this, &UFrisbeeActorComponent::OnHit);
	}
}

bool UFrisbeeActorComponent::CheckCatchConditions()
{
	//TODO: check on the correct team
	return true;
}

void UFrisbeeActorComponent::Catch(UFrisbeePlayerActorComponent * newHolder, USceneComponent * holderSceneComponent)
{
	if (CheckCatchConditions())
	{
		currentHolder = newHolder;

		PlaceOntopOfComponent(holderSceneComponent);

		newHolder->OnStartHoldFrisbee();
	}
}

#pragma optimize("", off)

void UFrisbeeActorComponent::PlaceOntopOfActor(AActor* actorWhomstShallReceiveTheDisc)
{
	check(actorWhomstShallReceiveTheDisc);
	GetOwner()->AttachToActor(actorWhomstShallReceiveTheDisc, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	PlaceOntop();
}

void UFrisbeeActorComponent::PlaceOntopOfComponent(USceneComponent* componentWhomstShallReceiveTheDisc)
{
	check(componentWhomstShallReceiveTheDisc);
	GetOwner()->GetRootComponent()->AttachTo(componentWhomstShallReceiveTheDisc, NAME_None, EAttachLocation::KeepRelativeOffset, true);

	PlaceOntop();
}

void UFrisbeeActorComponent::PlaceOntop()
{
	GetOwner()->SetActorRelativeLocation(FVector(0, 0, m_verticalOffsetOnHold));
}

#pragma optimize("", on)