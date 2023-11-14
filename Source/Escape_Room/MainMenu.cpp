// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "PlayerData.h"
#include "Engine.h"


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
        hostButton = Cast<UButton>(GetWidgetFromName(TEXT("HostButton")));
        joinButton = Cast<UButton>(GetWidgetFromName(TEXT("JoinButton")));
        nameTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("NameTextBox")));
        warningTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("WarningText")));
        if (warningTextBlock)
        {
            warningTextBlock->SetVisibility(ESlateVisibility::Hidden);
        }
        if (!nameTextBox)
            UE_LOG(LogTemp, Warning, TEXT("nameTextBox is null"));
        if (hostButton)
        {
            hostButton->OnClicked.AddDynamic(this, &UMainMenu::OnHostButtonClicked);
        }
        if (joinButton)
        {
            joinButton->OnClicked.AddDynamic(this, &UMainMenu::OnJoinButtonClicked);
        }

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

void UMainMenu::ShowMainMenu()
{
    mainMenuPanel->SetVisibility(ESlateVisibility::Visible);
    sessionPanel->SetVisibility(ESlateVisibility::Hidden);
    optionsPanel->SetVisibility(ESlateVisibility::Hidden);
}

void UMainMenu::ShowSessionMenu()
{
    mainMenuPanel->SetVisibility(ESlateVisibility::Hidden);
    sessionPanel->SetVisibility(ESlateVisibility::Visible);
    optionsPanel->SetVisibility(ESlateVisibility::Hidden);
}

void UMainMenu::ShowOptionsMenu()
{
    mainMenuPanel->SetVisibility(ESlateVisibility::Hidden);
    sessionPanel->SetVisibility(ESlateVisibility::Hidden);
    optionsPanel->SetVisibility(ESlateVisibility::Visible);
}

void UMainMenu::ShowWarningText()
{
    warningTextBlock->SetVisibility(ESlateVisibility::Visible);
    FTimerHandle HideTextBlockTimerHandle;
    GetWorld()->GetTimerManager().SetTimer(HideTextBlockTimerHandle, this, &UMainMenu::HideWarningText, 2.f, false);
}

void UMainMenu::HideWarningText()
{
    warningTextBlock->SetVisibility(ESlateVisibility::Hidden);
}

void UMainMenu::StartGame()
{
    UE_LOG(LogTemp, Warning, TEXT("StartGame"));
    GetOwningPlayer()->bShowMouseCursor = false;
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("Gameplay"));
}

void UMainMenu::OnStartButtonClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("OnStartButtonClicked"));
    ShowSessionMenu();
}

void UMainMenu::OnOptionsButtonClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("OnOptionsButtonClicked"));
    ShowOptionsMenu();
}

void UMainMenu::OnQuitButtonClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("OnQuitButtonClicked"));
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Closing the game..."));
        GEngine->GameViewport->ConsoleCommand("quit");
    }
}

void UMainMenu::OnOptionsBackButtonClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("OnOptionsBackButtonClicked"));
    mainMenuPanel->SetVisibility(ESlateVisibility::Visible);
    sessionPanel->SetVisibility(ESlateVisibility::Hidden);
    optionsPanel->SetVisibility(ESlateVisibility::Hidden);
}

void UMainMenu::OnHostButtonClicked()
{
    if (nameTextBox && nameTextBox->GetText().ToString().Len() > 5)
    {
        UPlayerData::GetInstance()->playerName = nameTextBox->GetText().ToString();  
        StartGame();
    }
    else
    {
        ShowWarningText();
    }
}

void UMainMenu::OnJoinButtonClicked()
{
    if (nameTextBox && nameTextBox->GetText().ToString().Len() > 5)
    {
        UPlayerData::GetInstance()->playerName = nameTextBox->GetText().ToString();  
        StartGame();
    }
    else
    {
        ShowWarningText();
    }
}
