// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FrisbeeActorComponent.generated.h"

class UFrisbeePlayerActorComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ULTIMATEFRISBALL_API UFrisbeeActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFrisbeeActorComponent();

	UFUNCTION(Server)
	void Throw(FVector direction, float power);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	
	bool CheckCatchConditions();
	void Catch(UFrisbeePlayerActorComponent * newHolder, USceneComponent * holderPrimitiveComponent);
	
	void PlaceOntopOfComponent(USceneComponent* componentWhomstShallReceiveTheDisc);
	void ReleaseFromOnTop();
	
private:

	UFrisbeePlayerActorComponent * currentHolder;

	UPROPERTY(EditAnywhere)
	float m_verticalOffsetOnHold;

};
