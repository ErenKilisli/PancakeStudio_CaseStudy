// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "UDPManager.generated.h"

UCLASS()
class VEHICLESTREAMER_API AUDPManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUDPManager();

	UFUNCTION(BlueprintCallable, Category = "UDP")
	void SendVehicleData(const FVector& Location, const FRotator& Rotation);

	UFUNCTION(BlueprintCallable, Category = "UDP")
	void ReceiveData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Socket for UDP communication
	FSocket* UDPSocket;

	// Socket initialization
	bool InitializeUDPSocket(const FString& SocketName, const FString& IP, const int32 Port);

	TSharedPtr<FInternetAddr> RemoteAddr;
};
