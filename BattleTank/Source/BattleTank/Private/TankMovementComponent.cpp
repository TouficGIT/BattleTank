// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "Engine/World.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMovementForward(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//auto Time = GetWorld()->GetTimeSeconds();;
	//auto Name = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s : Vectoring to %f"), *Name, *MoveVelocityString);

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMovementForward(ForwardThrow);

	auto TurnThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(TurnThrow);
}