// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "TankAimingComponent.h"
#include "BattleTank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	Super::Tick(DeltaTime);
	FVector HitLocation;

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	// Aim toward the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// Move toward the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	//TODO Fix firing
	//ControlledTank->Fire(); // TODO Don't fire every frame
}
