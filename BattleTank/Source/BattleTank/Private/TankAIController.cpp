// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto AIControlledTank = GetControlledTank();
	if (!AIControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController not posessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController posessing %s"), *(AIControlledTank->GetName()));
	}

	UE_LOG(LogTemp, Warning, TEXT("AIController Begin play"));
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}