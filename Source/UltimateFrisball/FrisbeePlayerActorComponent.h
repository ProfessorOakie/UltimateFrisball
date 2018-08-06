// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UltimateFrisballPawn.h"
#include "FrisbeePlayerActorComponent.generated.h"

class UFrisbeeActorComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ULTIMATEFRISBALL_API UFrisbeePlayerActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFrisbeePlayerActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OnStartHoldFrisbee(UFrisbeeActorComponent* heldFrisbee);
	void OnStopHoldFrisbee();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_OnThrow();
	void Server_OnThrow_Implementation();
	bool Server_OnThrow_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_OnResetCar();
	void Server_OnResetCar_Implementation();
	bool Server_OnResetCar_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_OnJump();
	void Server_OnJump_Implementation();
	bool Server_OnJump_Validate();
	
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_RotateRight(float Val);
	void Server_RotateRight_Implementation(float Val);
	bool Server_RotateRight_Validate(float Val);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_RotateForward(float Val);
	void Server_RotateForward_Implementation(float Val);
	bool Server_RotateForward_Validate(float Val);



	bool IsHoldingFrisbee() const;
	void AssignTeam(int8 team);
	int8 GetTeam() const;

private:

	UFrisbeeActorComponent* m_heldFrisbee;

	AUltimateFrisballPawn* m_pawn;

	UPROPERTY(EditAnywhere, Category = "Frisbee")
		float m_throwingPower;

	UPROPERTY(EditAnywhere, Category = "Frisbee")
		float m_jumpingPower;

	UPROPERTY(EditAnywhere, Category = "Frisbee")
		float m_rotateRightPower;

	UPROPERTY(EditAnywhere, Category = "Frisbee")
		float m_rotateForwardPower;

	UPROPERTY(EditAnywhere, Category = "Teams")
		int8 TeamNumber;

};

