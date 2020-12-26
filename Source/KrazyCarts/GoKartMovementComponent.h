// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoKartMovementComponent.generated.h"

USTRUCT()
struct FGoKartMove
{
	GENERATED_BODY()

		UPROPERTY()
		float Throttle;

	UPROPERTY()
		float SteeringThrow;

	UPROPERTY()
		float DeltaTime;

	UPROPERTY()
		float Time;

	bool IsValid() const
	{
		return FMath::Abs(Throttle) <= 1 && FMath::Abs(SteeringThrow) <= 1;
	}
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class KRAZYCARTS_API UGoKartMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGoKartMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SimulateMove(const FGoKartMove& Move);

	FVector GetVelocity();

	void SetVelocity(const FVector& Val);

	void SetThrottle(float Val) { Throttle = Val; }

	void SetSteeringThrow(float Val) { SteeringThrow = Val; }

	FGoKartMove GetLastMove() { return LastMove; }

private:

	FGoKartMove CreateMove(float DeltaTime); 

	void UpdateLocationFromVelocity(float DeltaTime);

	const FVector GetAirResistance();

	const FVector GetRollingResistance();

	void ApplyRotation(float DeltaTime, float Throw);

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

	UPROPERTY(EditAnywhere)
		float MinimumTurningRadius = 10;

	float Throttle;

	float SteeringThrow;

	FVector Velocity;

	FGoKartMove LastMove;

};
