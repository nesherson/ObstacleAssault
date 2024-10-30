#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartPosition = GetActorLocation();
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	if (ShouldPlatformReturn())
	{
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartPosition += MoveDistance * MoveDirection;
		SetActorLocation(StartPosition);
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		FVector CurrentPosition = GetActorLocation();
		CurrentPosition += PlatformVelocity * DeltaTime;
		SetActorLocation(CurrentPosition);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}


bool AMovingPlatform::ShouldPlatformReturn() const
{
	float DistanceMoved = FVector::Dist(StartPosition, GetActorLocation());

	return DistanceMoved > MoveDistance;
}

