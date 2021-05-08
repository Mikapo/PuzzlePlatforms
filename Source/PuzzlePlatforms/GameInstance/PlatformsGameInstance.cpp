// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformsGameInstance.h"

UPlatformsGameInstance::UPlatformsGameInstance(const FObjectInitializer& ObjectIn)
{
	
}

void UPlatformsGameInstance::Init()
{
	Super::Init();

	
}

void UPlatformsGameInstance::Host()
{
	GetWorld()->ServerTravel(TEXT("/Game/MyStuff/Levels/MultiPlayer?listen"));
}

void UPlatformsGameInstance::Join(const FString& IP)
{
	GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Green, FString::Printf(TEXT("Joining on server: %s"), *IP));

	GetWorld()->GetFirstPlayerController()->ClientTravel(IP, ETravelType::TRAVEL_Absolute);
}
