// Fill out your copyright notice in the Description page of Project Settings.


#include "TestVehicle.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "UDPManager.h"


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

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUDPManager::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0)
	{
		UDPManagerRef = Cast<AUDPManager>(FoundActors[0]);
		UE_LOG(LogTemp, Log, TEXT("UDPManager found."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UDPManager NOT found."));
	}

	//set first direction
	ChangeDirection();

	//Change direction in few seconds
	GetWorld()->GetTimerManager().SetTimer(DirectionChangeTimer, this, &ATestVehicle::ChangeDirection, DirectionChangeInterval, true);
}

// Called every frame
void ATestVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FVector Location = GetActorLocation();
    FRotator Rotation = GetActorRotation();

	if (UDPManagerRef)
	{
		UDPManagerRef->SendVehicleData(Location, Rotation);
	}

	if (MeshComponent && CurrentDirection.Size() > 0)
	{
		MeshComponent->AddForce(CurrentDirection * MovementForce);
	}

	if (UDPManagerRef)
	{
		UDPManagerRef->SendVehicleData(GetActorLocation(), GetActorRotation());
	}
}

void ATestVehicle::ChangeDirection()
{
	float X = FMath::FRandRange(-1.0f, 1.0f);
	float Y = FMath::FRandRange(-1.0f, 1.0f);

	CurrentDirection = FVector(X, Y, 0.0f).GetSafeNormal();
}
