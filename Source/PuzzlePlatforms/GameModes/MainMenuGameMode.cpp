// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"
#include "Blueprint/UserWidget.h"
#include "PuzzlePlatforms/UMG/MainMenuWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();
	SetupWidgets();
	AddMainMenuToScreen();
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;

	
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetWorld()->GetFirstPlayerController(), MainMenuWidget);
	
}

bool AMainMenuGameMode::SetupWidgets()
{
	bool Success = true;
	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld()->GetFirstPlayerController(), MainMenuWidgetClass);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s did not find refrence to blueprint class"), *GetName())
		Success = false;
	}

	return Success;
	
}

bool AMainMenuGameMode::AddMainMenuToScreen()
{
	if (MainMenuWidget)
	{
		MainMenuWidget->AddToViewport();
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s failed to create main menu"), *GetName())
		return false;
	}
}
