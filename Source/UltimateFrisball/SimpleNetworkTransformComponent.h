// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SimpleNetworkTransformComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ULTIMATEFRISBALL_API USimpleNetworkTransformComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USimpleNetworkTransformComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Marks the properties we wish to replicate */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


protected:
	/** The WorldPos of the character */
	UPROPERTY(VisibleAnywhere, Transient, ReplicatedUsing = OnRep_WorldPos, Category = Stats)
		FVector WorldPos;
	/** The WorldPos of the character */
	UPROPERTY(VisibleAnywhere, Transient, ReplicatedUsing = OnRep_Rotation, Category = Stats)
		FRotator Rotation;

private:
	/** Called when the WorldPos variable gets updated */
	UFUNCTION()
		void OnRep_WorldPos();
	/** Called when the Rotation variable gets updated */
	UFUNCTION()
		void OnRep_Rotation();

	void GetVariables();

	USceneComponent* movingComponent;

};
