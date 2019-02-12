// Fill out your copyright notice in the Description page of Project Settings.

#include "Boid.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Materials/Material.h"
#include "Components/StaticMeshComponent.h"
#include <Kismet/KismetMathLibrary.h>


// Sets default values
ABoid::ABoid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshForBoid"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> boidMesh(TEXT("StaticMesh'/Game/Boid.Boid'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> boidMaterial(TEXT("Material'/Game/BoidMaterial.BoidMaterial'"));

	mesh->SetStaticMesh(boidMesh.Object);
	mesh->SetMaterial(0,boidMaterial.Object);

	RootComponent = mesh;
}

// Called when the game starts or when spawned
void ABoid::BeginPlay()
{
	Super::BeginPlay();
	//TODO Maybe give some initial random velocity
}

// Called every frame
void ABoid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetActorLocation() + velocity * DeltaTime);
	SetActorRotation((UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetActorLocation() + velocity)).Add(250.0f, 0.0f, 0.0f));
}

