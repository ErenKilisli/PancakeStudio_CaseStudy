// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UDPManager.h"
#include "TestVehicle.generated.h"


UCLASS(BlueprintType, Blueprintable)
class VEHICLESTREAMER_API ATestVehicle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestVehicle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

	AUDPManager* UDPManagerRef;

	//random movement
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementForce = 100000.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float DirectionChangeInterval = 2.0f;

	FTimerHandle DirectionChangeTimer;

	FVector CurrentDirection;

	void ChangeDirection();



};
