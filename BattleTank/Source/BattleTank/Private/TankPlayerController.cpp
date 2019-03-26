// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "BattleTank.h"

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController can't find aiming component at Begin Play"));
	}
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (AimingComponent) {

		FVector HitLocation; //OutParameter
		if (GetSightRayHitLocation(HitLocation))
		{
			AimingComponent->AimAt(HitLocation);
		}
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const 
{
	// set the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	// "De-project" the screen position of the crosshair to a world direction
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	FVector WorldDirection;
	if (GetLookDirection(ScreenLocation, WorldDirection))
	{
		// Line trace along that look direction, and see what we hit
		GetLookVectorHitDirection(WorldDirection,OutHitLocation);
	}

	return true;
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& WorldDirection) const
{
	FVector WorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		WorldLocation,
		WorldDirection
	);
}

bool ATankPlayerController::GetLookVectorHitDirection(FVector WorldDirection, FVector& OutHitLocation) const
{
	FHitResult Hit;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (WorldDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
			Hit,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
		)
	{
		OutHitLocation = Hit.Location;
		return true;
	}
	OutHitLocation = FVector(0);
	return false;
}