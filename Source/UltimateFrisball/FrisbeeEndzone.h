// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FrisbeeEndzone.generated.h"

class UBoxComponent;
class USphereComponent;
UCLASS()
class ULTIMATEFRISBALL_API AFrisbeeEndzone : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFrisbeeEndzone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* EndzoneOverlapComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* EndzoneExplosionComponent;

	void Explode();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Teams")
		int8 TeamThatCanScore;



};
