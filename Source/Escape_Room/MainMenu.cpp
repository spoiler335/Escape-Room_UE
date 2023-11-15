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
    MyGameUserSettings = GEngine->GameUserSettings;
    SupportedResolutions.Add(FIntPoint(1920, 1080));
    SupportedResolutions.Add(FIntPoint(1600, 900));
    SupportedResolutions.Add(FIntPoint(1280, 720));
    SupportedResolutions.Add(FIntPoint(1024, 768));
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
        applyButton = Cast<UButton>(GetWidgetFromName(TEXT("ApplyButton")));
        windowNext = Cast<UButton>(GetWidgetFromName(TEXT("WindowNext")));
        windowPrev = Cast<UButton>(GetWidgetFromName(TEXT("WindowPrev")));
        resolutionNext = Cast<UButton>(GetWidgetFromName(TEXT("ResolutionNext")));
        resolutionPrev = Cast<UButton>(GetWidgetFromName(TEXT("ResolutionPrev")));
        vsyncToggle = Cast<UButton>(GetWidgetFromName(TEXT("VSyncToggle")));
        windowText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ScreenSizeText")));
        resolutionText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ResolutionText")));
        if (backButton)
        {
            backButton->OnClicked.AddDynamic(this, &UMainMenu::OnOptionsBackButtonClicked);
        }
        if (applyButton)
        {
            applyButton->OnClicked.AddDynamic(this, &UMainMenu::ApplySettings);
        }
        if (windowNext)
        {
            windowNext->OnClicked.AddDynamic(this, &UMainMenu::UpdateWindowMode);
        }
        if (windowPrev)
        {
            windowPrev->OnClicked.AddDynamic(this, &UMainMenu::UpdateWindowMode);
        }
        if (resolutionNext)
        {
            resolutionNext->OnClicked.AddDynamic(this, &UMainMenu::UpdateResolution);
        }
        if (resolutionPrev)
        {
            resolutionPrev->OnClicked.AddDynamic(this, &UMainMenu::UpdateResolution);
        }
        if (vsyncToggle)
        {
            if (MyGameUserSettings->IsVSyncEnabled())
            {
                vsyncToggle->SetBackgroundColor(FLinearColor::Green);
            }
            else
            {
                vsyncToggle->SetBackgroundColor(FLinearColor::Red);
            }
            vsyncToggle->OnClicked.AddDynamic(this, &UMainMenu::UpdateVSync);
        }
        if (windowText)
        {
            FString windowMode = (MyGameUserSettings->GetFullscreenMode() == EWindowMode::Windowed) ? "Windowed" : "Fullscreen";
            windowText->SetText(FText::FromString(windowMode));
        }
        if(resolutionText)
        {
            FString resolution = FString::FromInt(MyGameUserSettings->GetScreenResolution().X) + "X" + FString::FromInt(MyGameUserSettings->GetScreenResolution().Y);
            resolutionText->SetText(FText::FromString(resolution));
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

void UMainMenu::HostGame()
{
    UE_LOG(LogTemp, Warning, TEXT("StartGame"));
    GetOwningPlayer()->bShowMouseCursor = false;
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("Gameplay"), true, "listen");
}

void UMainMenu::JoinGame()
{
    UE_LOG(LogTemp, Warning, TEXT("JoinGame"));
    GetOwningPlayer()->bShowMouseCursor = false;
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("127.0.0.1"));
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
        HostGame();
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
        JoinGame();
    }
    else
    {
        ShowWarningText();
    }
}

void UMainMenu::UpdateWindowMode()
{
    if (MyGameUserSettings)
    {

        if (MyGameUserSettings->GetFullscreenMode() == EWindowMode::Fullscreen)
        {
            MyGameUserSettings->SetFullscreenMode(EWindowMode::Windowed);
            windowText->SetText(FText::FromString("Windowed"));
        }
        else
        {
            MyGameUserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
            windowText->SetText(FText::FromString("Fullscreen"));
        }
    }
}

void UMainMenu::UpdateResolution()
{
    if (MyGameUserSettings)
    {
        // Get the current screen resolution and remove it from the array
        FIntPoint CurrentResolution = MyGameUserSettings->GetScreenResolution();
        SupportedResolutions.Remove(CurrentResolution);

        // Get the next resolution in the array
        FIntPoint NextResolution = SupportedResolutions[0];
        resolutionText->SetText(FText::FromString(FString::FromInt(NextResolution.X) + "X" + FString::FromInt(NextResolution.Y)));

        // Set the next resolution
        MyGameUserSettings->SetScreenResolution(NextResolution);
        SupportedResolutions.Add(CurrentResolution);
    }
}

void UMainMenu::UpdateVSync()
{
    if (MyGameUserSettings)
    {
        if (MyGameUserSettings->IsVSyncEnabled())
        {
            MyGameUserSettings->SetVSyncEnabled(false);
            vsyncToggle->SetBackgroundColor(FLinearColor::Red);
        }
        else
        {
            MyGameUserSettings->SetVSyncEnabled(true);
            vsyncToggle->SetBackgroundColor(FLinearColor::Green);
        }
    }
}

void UMainMenu::ApplySettings()
{
    if (MyGameUserSettings)
    {
        MyGameUserSettings->ApplySettings(false);
    }
}