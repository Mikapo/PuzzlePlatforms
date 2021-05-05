// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformsGameInstance.h"

UPlatformsGameInstance::UPlatformsGameInstance(const FObjectInitializer& ObjectIn)
{
	UE_LOG(LogTemp, Warning, TEXT("Constructor Test"))
}

void UPlatformsGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("Init Test"))
}

void UPlatformsGameInstance::Host()
{
	if (!GEngine) return;
	GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Green, TEXT("Hosting"));
}

void UPlatformsGameInstance::Join(const FString& IP)
{
	GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Green, FString::Printf(TEXT("Joining on server: %s"), *IP));
}
