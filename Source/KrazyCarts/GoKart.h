// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GoKart.generated.h"

UCLASS()
class KRAZYCARTS_API AGoKart : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGoKart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ApplyRotation(float DeltaTime);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	
	void UpdateLocationFromVelocity(float DeltaTime);

	void MoveForward(float Val);

	void MoveRight(float Val);

	const FVector GetAirResistance();

	const FVector GetRollingResistance();

	FVector Velocity;

	//The mass of the car (kg).
	UPROPERTY(EditAnywhere)
		float Mass = 1000.f;

	//The force applied to the car when the throttle is fully down.
	UPROPERTY(EditAnywhere)
		float MaxDrivingForce = 9800.f;

	UPROPERTY(EditAnywhere)
		float DragCoefficient = 16.f;

	UPROPERTY(EditAnywhere)
		float RollingResistanceCoefficient = 0.015;

	UPROPERTY(EditAnywhere)
		float MaxDrivingSpeed = 10000.f;

	//The number of degrees rotated per seconds at full controll throw (degree/s).
	UPROPERTY(EditAnywhere)
		float MaxDegressPerSeconds = 90;

	float Throttle;

	float SteeringThrow;

};
