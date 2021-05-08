// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
class UMainMenuWidget;
UCLASS()
class PUZZLEPLATFORMS_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
	UPROPERTY()
	UMainMenuWidget* MainMenuWidget = nullptr;

private:

	bool SetupWidgets();
	bool AddMainMenuToScreen();

};
