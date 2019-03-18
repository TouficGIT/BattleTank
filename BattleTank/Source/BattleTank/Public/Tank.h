// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Declarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:	
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly, category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, category = "Firing")
		float LaunchSpeed = 4000; // Sensible starting value of 1000 m/s

	UPROPERTY(EditDefaultsOnly, category = "Firing")
		float ReloadTimeInSecond = 3;

	// Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr; // TODO Remove

	double LastFireTime = 0;
};
