// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GameFramework/Character.h>
#include "Boid.h"
#include "FlockMaintainer.generated.h"

UCLASS()
class BOIDSIMULATION_API AFlockMaintainer : public AActor
{
	GENERATED_BODY()
private:
	UWorld* world;

	//Holds the center of mass for the flock
	FVector centerOfMass;
	//Holds the average velocity of the flock
	FVector averageVelocity;
	//Array of the boids in the flock
	TArray<ABoid*> boids;

	ACharacter* flockMaintainer;

	UPROPERTY(EditAnywhere)
		int32	noOfBoids;
	//Boundary start Location
	UPROPERTY(EditAnywhere)
		FVector startBoundary;
	//Boundary End Location
	UPROPERTY(EditAnywhere)
		FVector endBoundary;
	//Avoidance distance that each boid maintains from one another
	UPROPERTY(EditAnywhere)
		float boidAvoidanceRange;
	//Avoidance distance from the boundary
	UPROPERTY(EditAnywhere)
		float boundaryAvoidanceRange;
	//speed handler for the boid velocity
	UPROPERTY(EditAnywhere)
		float speedMultiplier;
	//Weight for the cohesion property
	UPROPERTY(EditAnywhere)
		float cohesionWeight;
	//Clamp for cohesion weight
	UPROPERTY(EditAnywhere)
		float maxCohesionWeight;
	//Weight for the avoidance property
	UPROPERTY(EditAnywhere)
		float avoidanceWeight;
	//Clamp for the avoidance property
	UPROPERTY(EditAnywhere)
		float maxAvoidanceWeight;
	//Weight for the alignment property
	UPROPERTY(EditAnywhere)
		float alignmentWeight;
	//Clamp for alignment property
	UPROPERTY(EditAnywhere)
		float maxAlignmentWeight;
	//weight for the bounds
	UPROPERTY(EditAnywhere)
		float boundWeight;
	//Clamp for the bound weight
	UPROPERTY(EditAnywhere)
		float maxBoundWeight;


	
public:	
	// Sets default values for this actor's properties
	AFlockMaintainer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Returns the center of Mass of the flock
	FVector getCenterOfMass();
	//Returns the average velocity of the flock
	FVector getAverageVelocity();
	//Computes cohesion for the flock
	FVector cohesion();
	//Computes alignment for the flock
	FVector alignment();
	//Computes avoidance for the flock
	FVector avoidance();

};
