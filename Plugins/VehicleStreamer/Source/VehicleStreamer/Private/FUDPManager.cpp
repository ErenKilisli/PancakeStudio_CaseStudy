// Fill out your copyright notice in the Description page of Project Settings.


#include "FUDPManager.h"
#include "Common/UdpSocketBuilder.h"
#include "HAL/PlatformProcess.h"

FUDPManager::FUDPManager(const FString& InIP, int32 InPort)
{
    // IP ve port bilgilerini yapýlandýr
    RemoteAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    bool bIsValid;
    RemoteAddr->SetIp(*InIP, bIsValid);
    RemoteAddr->SetPort(InPort);

    if (!bIsValid)
    {
        UE_LOG(LogTemp, Error, TEXT("FUDPManager: IP adresi geçersiz!"));
        return;
    }

    // UDP Socket oluþtur
    UDPSocket = FUdpSocketBuilder(TEXT("UDP Sender Socket"))
        .AsReusable()
        .WithBroadcast()
        .WithSendBufferSize(2 * 1024 * 1024);  // 2MB buffer

    if (UDPSocket)
    {
        UE_LOG(LogTemp, Log, TEXT("FUDPManager: UDP soket baþarýyla oluþturuldu."));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("FUDPManager: UDP soket oluþturulamadý!"));
    }
}

FUDPManager::~FUDPManager()
{
    if (UDPSocket)
    {
        UDPSocket->Close();
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(UDPSocket);
        UDPSocket = nullptr;
    }

    UE_LOG(LogTemp, Log, TEXT("FUDPManager: Socket kapatýldý."));
}

bool FUDPManager::SendMessage(const FString& Message)
{
    if (!UDPSocket || !RemoteAddr.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("FUDPManager: Socket veya adres geçersiz."));
        return false;
    }

    // FString ? UTF-8 byte array'e çevir
    FTCHARToUTF8 Converter(*Message);
    int32 BytesSent = 0;

    bool bSuccess = UDPSocket->SendTo(
        (uint8*)Converter.Get(), Converter.Length(), BytesSent, *RemoteAddr
    );

    if (bSuccess)
    {
        UE_LOG(LogTemp, Log, TEXT("FUDPManager: Veri gönderildi ? %s"), *Message);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("FUDPManager: Veri gönderilemedi."));
    }

    return bSuccess;
}