// Fill out your copyright notice in the Description page of Project Settings.


#include "UDPManager.h"
#include "Common/UdpSocketBuilder.h"


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
	
	// Initialize the UDP socket here or when you need to send/receive data
	if (!InitializeUDPSocket(TEXT("TestUDPSocket"), TEXT("127.0.0.1"), 8888))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to initialize UDP socket"));
	}
}

// Called every frame
void AUDPManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AUDPManager::InitializeUDPSocket(const FString& SocketName, const FString& IP, const int32 Port)
{
    // Remote adresi ayarla
    RemoteAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    bool bIsValid;
    RemoteAddr->SetIp(*IP, bIsValid);
    RemoteAddr->SetPort(Port);

    if (!bIsValid)
    {
        UE_LOG(LogTemp, Error, TEXT("AUDPManager: IP geçersiz!"));
        return false;
    }

    UDPSocket = FUdpSocketBuilder(*SocketName)
        .AsReusable()
        .WithBroadcast()
        .WithSendBufferSize(2 * 1024 * 1024);

    if (!UDPSocket)
    {
        UE_LOG(LogTemp, Error, TEXT("AUDPManager: Socket oluşturulamadı"));
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
            UE_LOG(LogTemp, Log, TEXT("UDPManager: Veri gönderildi → %s"), *DataToSend);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("UDPManager: Gönderim başarısız"));
        }
    }
}


void AUDPManager::ReceiveData()
{
    // Receiving data implementation would go here if needed
}