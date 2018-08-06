// Fill out your copyright notice in the Description page of Project Settings.

#include "FrisbeeEndzone.h"
#include "Components/BoxComponent.h"
#include "UltimateFrisballPawn.h"
#include "FrisbeePlayerActorComponent.h"
#include "EngineMinimal.h"
#include "UltimateFrisballGameMode.h"
#include "FrisballGameState.h"
#include "Components/SphereComponent.h"
// Sets default values
AFrisbeeEndzone::AFrisbeeEndzone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EndzoneOverlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap Component"));
	EndzoneOverlapComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	RootComponent = EndzoneOverlapComponent;
	EndzoneExplosionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Explosion Component"));
	EndzoneExplosionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	EndzoneExplosionComponent->SetupAttachment(RootComponent);

	bReplicates = true;
}

// Called when the game starts or when spawned
void AFrisbeeEndzone::BeginPlay()
{
	Super::BeginPlay();

}

void AFrisbeeEndzone::Explode()
{
	TArray<UPrimitiveComponent*> OverlappingComponents;
	EndzoneOverlapComponent->GetOverlappingComponents(OverlappingComponents);
	for (int32 i = 0; i < OverlappingComponents.Num(); i++)
	{
		if (OverlappingComponents[i] && OverlappingComponents[i]->IsSimulatingPhysics())
		{
			OverlappingComponents[i]->AddRadialImpulse(GetActorLocation(), EndzoneExplosionComponent->GetUnscaledSphereRadius(), 8000.0f, RIF_Linear, true);
		}
	}

	if (Role < ROLE_Authority)
	{
		Server_Explode();
	}
}

void AFrisbeeEndzone::Server_Explode_Implementation()
{
	Explode();
}

bool  AFrisbeeEndzone::Server_Explode_Validate()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
	return true;
}

// Called every frame
void AFrisbeeEndzone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TArray<AActor*> OverlappingActors;
	EndzoneOverlapComponent->GetOverlappingActors(OverlappingActors);
	for (int32 i = 0; i < OverlappingActors.Num(); i++)
	{
		AUltimateFrisballPawn* TempPawn = Cast<AUltimateFrisballPawn>(OverlappingActors[i]);
		if (TempPawn)
		{			
			UFrisbeePlayerActorComponent* TempPlayerComponent = TempPawn->FrisbeeActorComponent;
			if (TempPlayerComponent)
			{
				AFrisballGameState* GameState = Cast<AFrisballGameState>(GetWorld()->GetGameState());
				if (TempPlayerComponent->GetTeam() == TeamThatCanScore && TempPlayerComponent->IsHoldingFrisbee() && GameState->m_CanScore)
				{
					GameState->TeamScore(TeamThatCanScore);
					Explode();
				}
			}
		}
	}

}


