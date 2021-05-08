// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"


/**
 * 
 */
class UButton;
class UEditableTextBox;
class UWidgetSwitcher;


UCLASS()
class PUZZLEPLATFORMS_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

protected:

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinServerButton;

	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* IpTextBox;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MainMenuSwitcher;


	
	
	

private:

	UFUNCTION()
	void JoinButtonOnPressed();

	UFUNCTION()
	void HostButtonOnPressed();

	UFUNCTION()
	void JoinServerButtonOnPressed();

	UFUNCTION()
	void BackButtonOnPressed();

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	
};
