// Fill out your copyright notice in the Description page of Project Settings.


#include "GoKartMovementComponent.h"
#include "Engine/World.h"
#include "GameFramework/GameStateBase.h"

// Sets default values for this component's properties
UGoKartMovementComponent::UGoKartMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UGoKartMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGoKartMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FVector UGoKartMovementComponent::GetVelocity()
{
	return Velocity;
}

void UGoKartMovementComponent::SetVelocity(const FVector& Val)
{
	 Velocity = Val;
}

const FVector UGoKartMovementComponent::GetAirResistance()
{
	float Speed = Velocity.Size();

	return -(Velocity.GetSafeNormal() * Velocity.SizeSquared() * DragCoefficient);
}

const FVector UGoKartMovementComponent::GetRollingResistance()
{
	float AccelerationDueToGravity = -GetWorld()->GetGravityZ() / 100;
	float NoramlForce = Mass * AccelerationDueToGravity;

	return -(Velocity.GetSafeNormal() * RollingResistanceCoefficient * NoramlForce);
}

void UGoKartMovementComponent::ApplyRotation(float DeltaTime, float Throw)
{
	float RotationAngle = (FVector::DotProduct(GetOwner()->GetActorForwardVector(), Velocity) * DeltaTime) / MinimumTurningRadius * Throw; // MaxDegressPerSeconds * DeltaTime * SteeringThrow;

	FQuat RotationDelta(GetOwner()->GetActorUpVector(), RotationAngle);

	GetOwner()->AddActorWorldRotation(RotationDelta);

	Velocity = RotationDelta.RotateVector(Velocity);
}

void UGoKartMovementComponent::SimulateMove(const FGoKartMove& Move)
{
	float DeltaTime = Move.DeltaTime;
	FVector AirResistance = GetAirResistance();
	FVector RollingResistance = GetRollingResistance();

	FVector Force = (GetOwner()->GetActorForwardVector() * MaxDrivingForce * Move.Throttle);
	Force += AirResistance;
	Force += RollingResistance;

	FVector Acceleration = Force / Mass;

	Velocity = Velocity + Acceleration * DeltaTime;

	ApplyRotation(DeltaTime, Move.SteeringThrow);

	UpdateLocationFromVelocity(DeltaTime);

}

FGoKartMove UGoKartMovementComponent::CreateMove(float DeltaTime)
{
	FGoKartMove Move;
	Move.DeltaTime = DeltaTime;
	Move.SteeringThrow = SteeringThrow;
	Move.Throttle = Throttle;

	AGameStateBase* GameState = GetWorld()->GetGameState();
	Move.Time = GameState->GetServerWorldTimeSeconds();

	return Move;
}

void UGoKartMovementComponent::UpdateLocationFromVelocity(float DeltaTime)
{
	FVector Translation = Velocity * 100 * DeltaTime;

	FHitResult HitResult;
	GetOwner()->AddActorWorldOffset(Translation, true, &HitResult);

	if (HitResult.IsValidBlockingHit())
	{
		Velocity = FVector::ZeroVector;
	}
}



