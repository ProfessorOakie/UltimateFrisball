// Fill out your copyright notice in the Description page of Project Settings.

#include "FrisballSelectTeam.h"
#include "Components/BoxComponent.h"
#include "FrisballPlayerState.h"
#include "UltimateFrisballPawn.h"
#include "FrisbeePlayerActorComponent.h"
#include "EngineMinimal.h"
#include "FrisballGameState.h"

// Sets default values
AFrisballSelectTeam::AFrisballSelectTeam()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OverlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Overlap Component"));
	RootComponent = OverlapComponent;
	OverlapComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &AFrisballSelectTeam::TriggerEnter);
	
}

// Called when the game starts or when spawned
void AFrisballSelectTeam::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFrisballSelectTeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AFrisballSelectTeam::TriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AUltimateFrisballPawn* TempPawn = Cast<AUltimateFrisballPawn>(OtherActor);
	if (TempPawn)
	{
		AFrisballPlayerState* state = Cast<AFrisballPlayerState>(TempPawn->PlayerState);
		if (state)
		{
			if (state->m_TeamAssigned)
			{
				return;
			}
			else
			{
				if (m_JoinTeam1)
				{
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("JoinedTeam1"));
					state->m_TeamNumber1 = true;
					TempPawn->FrisbeeActorComponent->AssignTeam(1);
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("JoinedTeam2"));
					state->m_TeamNumber1 = false;
					TempPawn->FrisbeeActorComponent->AssignTeam(2);
					TempPawn->GetMesh()->SetMaterial(0, SecondMaterial);
					TempPawn->GetMesh()->SetMaterial(1, SecondMaterial);
					TempPawn->GetMesh()->SetMaterial(2, SecondMaterial);
				}

				state->m_TeamAssigned = true;
				AFrisballGameState* GameState = Cast<AFrisballGameState>(GetWorld()->GetGameState());
				GameState->TestForGameStart();
				AssignedPlayers++;
				uint8 MaxPlayers;
				if (GameState->PlayerArray.Num() % 2 == 0)
				{
					MaxPlayers = GameState->PlayerArray.Num() / 2;
				}
				else
				{
					MaxPlayers = (GameState->PlayerArray.Num() / 2)+1;
				}
				if (AssignedPlayers == MaxPlayers)
				{
					OverlapComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
				}
			}
			
		}
	}
	if (Role < ROLE_Authority)
	{
		ServerTriggerEnter(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	}
	
}
void AFrisballSelectTeam::ServerTriggerEnter_Implementation(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	TriggerEnter(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
bool AFrisballSelectTeam::ServerTriggerEnter_Validate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	return true;
}