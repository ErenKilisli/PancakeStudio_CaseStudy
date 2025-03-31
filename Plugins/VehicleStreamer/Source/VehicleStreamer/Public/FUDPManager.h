// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

/**
 * 
 */
class VEHICLESTREAMER_API FUDPManager
{
public:
	FUDPManager(const FString& InIP, int32 InPort);
	~FUDPManager();

	bool SendMessage(const FString& Message);

private:
	FSocket* UDPSocket;
	TSharedPtr<FInternetAddr> RemoteAddr;
};
