// Fill out your copyright notice in the Description page of Project Settings.


#include "UDPManager.h"
#include "Common/UdpSocketBuilder.h"
#include "VehicleStreamerSettings.h"


// Sets default values
AUDPManager::AUDPManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUDPManager::BeginPlay()
{
	Super::BeginPlay();

    const auto* Settings = GetDefault<UVehicleStreamerSettings>();
    FString IP = Settings->UDPServerIP;
    int32 Port = Settings->UDPServerPort;

    // Initialize the UDP socket here or when you need to send/receive data
    if (!InitializeUDPSocket(TEXT("UDP_Socket"), IP, Port))
    {
        UE_LOG(LogTemp, Error, TEXT("UDPManager: Ayarlardan IP/Port alınamadı"));
    }
}

// Called every frame
void AUDPManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AUDPManager::InitializeUDPSocket(const FString& SocketName, const FString& IP, const int32 Port)
{
    // Remote adress adjust
    RemoteAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    bool bIsValid;
    RemoteAddr->SetIp(*IP, bIsValid);
    RemoteAddr->SetPort(Port);

    if (!bIsValid)
    {
        UE_LOG(LogTemp, Error, TEXT("AUDPManager: IP INVALID!"));
        return false;
    }

    UDPSocket = FUdpSocketBuilder(*SocketName)
        .AsReusable()
        .WithBroadcast()
        .WithSendBufferSize(2 * 1024 * 1024);

    if (!UDPSocket)
    {
        UE_LOG(LogTemp, Error, TEXT("AUDPManager: Socket can't made"));
        return false;
    }

    return true;
}


void AUDPManager::SendVehicleData(const FVector& Location, const FRotator& Rotation)
{
    if (UDPSocket && RemoteAddr.IsValid())
    {
        FString DataToSend = FString::Printf(TEXT("Location: %f, %f, %f; Rotation: %f, %f, %f"),
            Location.X, Location.Y, Location.Z,
            Rotation.Pitch, Rotation.Yaw, Rotation.Roll);

        FTCHARToUTF8 Converter(*DataToSend);
        int32 BytesSent = 0;

        bool Success = UDPSocket->SendTo(
            (uint8*)Converter.Get(),
            Converter.Length(),
            BytesSent,
            *RemoteAddr
        );

        if (Success)
        {
            UE_LOG(LogTemp, Log, TEXT("UDPManager: Data send → %s"), *DataToSend);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("UDPManager: Send Failed"));
        }
    }
}


void AUDPManager::ReceiveData()
{
}