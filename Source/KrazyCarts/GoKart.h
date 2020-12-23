// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GoKartMovementComponent.h"
#include "GoKart.generated.h"




USTRUCT()
struct FGoKartState
{
	GENERATED_BODY()

		UPROPERTY()
		FGoKartMove LatMove;

	UPROPERTY()
		FVector Velocity;

	UPROPERTY()
		FTransform Transform;
};


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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void ClearAcknowledgedMoves(FGoKartMove LastMove);

	void MoveForward(float Val);

	void MoveRight(float Val);

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_SendMove(FGoKartMove Move);

	UPROPERTY(ReplicatedUsing = OnRep_ServerState)
		FGoKartState ServerState;

	UFUNCTION()
		void OnRep_ServerState();

	UPROPERTY(EditAnywhere)
		UGoKartMovementComponent* MovementComponent;

	TArray<FGoKartMove> UnacknowledgedMoves;

};
