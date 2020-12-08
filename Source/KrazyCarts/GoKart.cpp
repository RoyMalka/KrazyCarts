// Fill out your copyright notice in the Description page of Project Settings.


#include "GoKart.h"
#include "Engine/World.h"

// Sets default values
AGoKart::AGoKart()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGoKart::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGoKart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector AirResistance = GetAirResistance();
	FVector RollingResistance = GetRollingResistance();

	FVector Force = (GetActorForwardVector() * MaxDrivingForce * Throttle);
	Force += AirResistance;
	Force += RollingResistance;

	FVector Acceleration = Force / Mass;

	Velocity = Velocity + Acceleration * DeltaTime;



	ApplyRotation(DeltaTime);

	UpdateLocationFromVelocity(DeltaTime);
}

const FVector AGoKart::GetAirResistance()
{
	float Speed = Velocity.Size();

	return -(Velocity.GetSafeNormal() * Velocity.SizeSquared() * DragCoefficient);
}

const FVector AGoKart::GetRollingResistance()
{
	float AccelerationDueToGravity = -GetWorld()->GetGravityZ() / 100;
	float NoramlForce = Mass * AccelerationDueToGravity;

	return -(Velocity.GetSafeNormal() * RollingResistanceCoefficient * NoramlForce);
}

void AGoKart::ApplyRotation(float DeltaTime)
{
	float RotationAngle = MaxDegressPerSeconds * DeltaTime * SteeringThrow;

	FQuat RotationDelta(GetActorUpVector(), FMath::DegreesToRadians(RotationAngle));

	AddActorWorldRotation(RotationDelta);

	Velocity = RotationDelta.RotateVector(Velocity);
}

void AGoKart::UpdateLocationFromVelocity(float DeltaTime)
{
	FVector Translation = Velocity * 100 * DeltaTime;

	FHitResult HitResult;
	AddActorWorldOffset(Translation, true, &HitResult);

	if (HitResult.IsValidBlockingHit())
	{
		Velocity = FVector::ZeroVector;
	}
}

// Called to bind functionality to input
void AGoKart::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGoKart::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGoKart::MoveRight);

}

void AGoKart::MoveForward(float Val)
{
	Throttle = Val;
}

void AGoKart::MoveRight(float Val)
{
	SteeringThrow = Val;
}

