// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"

void UMainMenu::NativeConstruct()
{
    Super::NativeConstruct();
    GetOwningPlayer()->bShowMouseCursor = true;
    SetupMainMenu();
    SetupSessionMenu();
    SetupOptionsMenu();
}

void UMainMenu::SetupMainMenu()
{
    mainMenuPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("MainMenuCanvas")));
    if (mainMenuPanel)
    {
        mainMenuPanel->SetVisibility(ESlateVisibility::Visible);
        startButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
        optionsButton = Cast<UButton>(GetWidgetFromName(TEXT("OptionsButton")));
        quitButton = Cast<UButton>(GetWidgetFromName(TEXT("QuitButton")));
        if (startButton)
        {
            startButton->OnClicked.AddDynamic(this, &UMainMenu::OnStartButtonClicked);
        }
        if (optionsButton)
        {
            optionsButton->OnClicked.AddDynamic(this, &UMainMenu::OnOptionsButtonClicked);
        }
        if (quitButton)
        {
            quitButton->OnClicked.AddDynamic(this, &UMainMenu::OnQuitButtonClicked);
        }
    }
}

void UMainMenu::SetupSessionMenu()
{
    sessionPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("SessionCanvass")));
    if (sessionPanel)
    {
        sessionPanel->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UMainMenu::SetupOptionsMenu()
{
    optionsPanel = Cast<UCanvasPanel>(GetWidgetFromName(TEXT("OptionsCanavas")));
    if (optionsPanel)
    {
        backButton = Cast<UButton>(GetWidgetFromName(TEXT("BackButton")));
        if (backButton)
        {
            backButton->OnClicked.AddDynamic(this, &UMainMenu::OnOptionsBackButtonClicked);
        }
        optionsPanel->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UMainMenu::OnStartButtonClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("OnStartButtonClicked"));
    GetOwningPlayer()->bShowMouseCursor = false;
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("Gameplay"));
    // mainMenuPanel->SetVisibility(ESlateVisibility::Hidden);
    // sessionPanel->SetVisibility(ESlateVisibility::Visible);
    // optionsPanel->SetVisibility(ESlateVisibility::Hidden);
}

void UMainMenu::OnOptionsButtonClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("OnOptionsButtonClicked"));
    mainMenuPanel->SetVisibility(ESlateVisibility::Hidden);
    sessionPanel->SetVisibility(ESlateVisibility::Hidden);
    optionsPanel->SetVisibility(ESlateVisibility::Visible);
}

void UMainMenu::OnQuitButtonClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("OnQuitButtonClicked"));
}

void UMainMenu::OnOptionsBackButtonClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("OnOptionsBackButtonClicked"));
    mainMenuPanel->SetVisibility(ESlateVisibility::Visible);
    sessionPanel->SetVisibility(ESlateVisibility::Hidden);
    optionsPanel->SetVisibility(ESlateVisibility::Hidden);
}
