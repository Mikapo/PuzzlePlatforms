// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Input/Reply.h"



void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	JoinButton->OnPressed.AddDynamic(this, &UMainMenuWidget::JoinButtonOnPressed);
	HostButton->OnPressed.AddDynamic(this, &UMainMenuWidget::HostButtonOnPressed);
	JoinServerButton->OnPressed.AddDynamic(this, &UMainMenuWidget::JoinServerButtonOnPressed);
	BackButton->OnPressed.AddDynamic(this, &UMainMenuWidget::BackButtonOnPressed);

	

}

void UMainMenuWidget::JoinButtonOnPressed()
{
	MainMenuSwitcher->SetActiveWidgetIndex(1);
}

void UMainMenuWidget::HostButtonOnPressed()
{
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());
	GetWorld()->ServerTravel(TEXT("/Game/MyStuff/Levels/MultiPlayer?listen"));
}

void UMainMenuWidget::JoinServerButtonOnPressed()
{
	const FString IP = IpTextBox->GetText().ToString();
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetWorld()->GetFirstPlayerController());

	GetWorld()->GetFirstPlayerController()->ClientTravel(IP, ETravelType::TRAVEL_Absolute);
}

void UMainMenuWidget::BackButtonOnPressed()
{
	MainMenuSwitcher->SetActiveWidgetIndex(0);
}

FReply UMainMenuWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey().ToString() == "Escape")
	{
		MainMenuSwitcher->SetActiveWidgetIndex(0);
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}
