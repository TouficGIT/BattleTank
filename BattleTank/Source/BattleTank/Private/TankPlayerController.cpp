// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "BattleTank.h"

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not posessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController posessing %s"), *(ControlledTank->GetName()));
	}

	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin play"));
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	UE_LOG(LogTemp, Warning, TEXT("Tick is working !"));
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank) { return; }
	// Get world location if linetrace through crosshair
	// If it hits the landscape
	 // Tell controlled tank to aim at this point
}