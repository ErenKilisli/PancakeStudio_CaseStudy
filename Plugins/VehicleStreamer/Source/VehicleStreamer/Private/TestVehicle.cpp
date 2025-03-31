// Fill out your copyright notice in the Description page of Project Settings.


#include "TestVehicle.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ATestVehicle::ATestVehicle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMesh.Succeeded())
    {
        MeshComponent->SetStaticMesh(CubeMesh.Object);
    }

    MeshComponent->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void ATestVehicle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FVector Location = GetActorLocation();
    FRotator Rotation = GetActorRotation();

    UE_LOG(LogTemp, Warning, TEXT("Location: %s | Rotation: %s"), *Location.ToString(), *Rotation.ToString());
}

