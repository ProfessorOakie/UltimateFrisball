// Fill out your copyright notice in the Description page of Project Settings.

#include "FrisbeeEndzone.h"
#include "Components/BoxComponent.h"
#include "UltimateFrisballPawn.h"
#include "FrisbeePlayerActorComponent.h"
#include "EngineMinimal.h"
#include "UltimateFrisballGameMode.h"
// Sets default values
AFrisbeeEndzone::AFrisbeeEndzone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EndzoneOverlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap Component"));
	EndzoneOverlapComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

// Called when the game starts or when spawned
void AFrisbeeEndzone::BeginPlay()
{
	Super::BeginPlay();

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
				AUltimateFrisballGameMode* gameMode = Cast<AUltimateFrisballGameMode>(GetWorld()->GetAuthGameMode());
				if (TempPlayerComponent->GetTeam() == TeamThatCanScore && TempPlayerComponent->IsHoldingFrisbee() && gameMode->m_CanScore)
				{

				}
			}
		}
	}

}


