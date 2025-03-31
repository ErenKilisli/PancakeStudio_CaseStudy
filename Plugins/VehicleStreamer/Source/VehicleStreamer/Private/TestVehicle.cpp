// Fill out your copyright notice in the Description page of Project Settings.


#include "TestVehicle.h"

// Sets default values
ATestVehicle::ATestVehicle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

