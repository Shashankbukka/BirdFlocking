// Fill out your copyright notice in the Description page of Project Settings.

#include "FlockMaintainer.h"
#include "Engine/World.h"
#include "Boid.h"

// Sets default values
AFlockMaintainer::AFlockMaintainer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFlockMaintainer::BeginPlay()
{
	Super::BeginPlay();
	world = GetWorld();

	FVector tempSpawnPos;
	for (int i = 0; i < noOfBoids; i++)
	{
		//Randomize the spawn locations
		tempSpawnPos.X = FMath::FRandRange(startBoundary.X, endBoundary.X);
		tempSpawnPos.Y = FMath::FRandRange(startBoundary.Y, endBoundary.Y);
		tempSpawnPos.Z = FMath::FRandRange(startBoundary.Z, endBoundary.Z);

		ABoid* boid = world->SpawnActor<ABoid>(ABoid::StaticClass(), tempSpawnPos, FRotator(0.0f));
		boids.Add(boid);
	}
	UE_LOG(LogTemp, Warning, TEXT("Maintainer CONSTRUCTOR %d"), boids.Num());
	
}

// Called every frame
void AFlockMaintainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	centerOfMass = getCenterOfMass();
	averageVelocity = getAverageVelocity();

	for (int i = 0; i < boids.Num(); i++)
	{
		boids[i]->velocity = (boids[i]->velocity
			+ (AFlockMaintainer::avoidance(boids[i]) * avoidanceWeight).GetClampedToMaxSize(maxAvoidanceWeight)
			+ (AFlockMaintainer::alignment(boids[i]) * alignmentWeight).GetClampedToMaxSize(maxAlignmentWeight)
			+ (AFlockMaintainer::cohesion(boids[i]) * cohesionWeight).GetClampedToMaxSize(maxCohesionWeight)
			+ (AFlockMaintainer::boundaryHandler(boids[i])* boundWeight).GetClampedToMaxSize(maxBoundWeight)
			);
	}
}

FVector AFlockMaintainer::getCenterOfMass()
{
	FVector result(0.0f, 0.0f, 0.0f);
	for (int32 i = 0; i < boids.Num(); i++)
	{
		result += boids[i]->GetActorLocation();
	}
	return result / (boids.Num());
}

FVector AFlockMaintainer::getAverageVelocity()
{
	FVector result(0.0f, 0.0f, 0.0f);
	for (int32 i = 0; i < boids.Num(); i++)
	{
		result += boids[i]->velocity;
	}
	return result / (boids.Num());
}

FVector AFlockMaintainer::cohesion(ABoid * boid)
{
	return (centerOfMass - boid->GetActorLocation());
}

FVector AFlockMaintainer::alignment(ABoid * boid)
{
	return (averageVelocity - boid->velocity);
}

FVector AFlockMaintainer::avoidance(ABoid * boid)
{
	FVector result(0.0f, 0.0f, 0.0f);

	for (int32 i = 0; i < boids.Num(); ++i)
	{
		if (boids[i] != boid)
		{
			float d = (boids[i]->GetActorLocation() - boid->GetActorLocation()).Size();
			if (d < boidAvoidanceRange)
			{
				result -= (boids[i]->GetActorLocation() - boid->GetActorLocation());
			}
		}
	}

	return result;
}

FVector AFlockMaintainer::boundaryHandler(ABoid * boid)
{
	FVector output = FVector(0.0f, 0.0f, 0.0f);

	if (boid->GetActorLocation().X < startBoundary.X) {
		output.X = boundaryAvoidanceRange;
	}
	else if (boid->GetActorLocation().X < endBoundary.X) {
		output.X = -boundaryAvoidanceRange;
	}

	if (boid->GetActorLocation().Y < startBoundary.Y) {
		output.Y = boundaryAvoidanceRange;
	}
	else if (boid->GetActorLocation().Y < endBoundary.Y) {
		output.Y = -boundaryAvoidanceRange;
	}

	if (boid->GetActorLocation().Z < startBoundary.Z) {
		output.Z = boundaryAvoidanceRange;
	}
	else if (boid->GetActorLocation().Z < endBoundary.Z) {
		output.Z = -boundaryAvoidanceRange;
	}

	return output;
}

