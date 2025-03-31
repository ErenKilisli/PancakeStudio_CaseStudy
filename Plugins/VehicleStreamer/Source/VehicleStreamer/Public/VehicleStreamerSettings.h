// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VehicleStreamerSettings.generated.h"

/**
 * 
 */
UCLASS(config = Game, defaultconfig)
class VEHICLESTREAMER_API UVehicleStreamerSettings : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(config, EditAnywhere, Category = "UDP Config")
	FString UDPServerIP = "127.0.0.1";

	UPROPERTY(config, EditAnywhere, Category = "UDP Config")
	int32 UDPServerPort = 8888;
};