// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FrisballSelectTeam.generated.h"


class UBoxComponent;
class UMaterial;

UCLASS()
class ULTIMATEFRISBALL_API AFrisballSelectTeam : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFrisballSelectTeam();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* OverlapComponent;
	UFUNCTION()
	void TriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(reliable, server, WithValidation)
	void ServerTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	bool m_JoinTeam1;
	UPROPERTY(EditAnywhere)
	UMaterial* SecondMaterial;

	uint8 AssignedPlayers = 0;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
