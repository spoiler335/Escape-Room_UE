// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameUserSettings.h"
#include "MainMenu.generated.h"

/**
 *
 */
UCLASS()
class ESCAPE_ROOM_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnStartButtonClicked();
	UFUNCTION()
	void OnOptionsButtonClicked();
	UFUNCTION()
	void OnQuitButtonClicked();
	UFUNCTION()
	void OnOptionsBackButtonClicked();
	UFUNCTION()
	void OnHostButtonClicked();
	UFUNCTION()
	void OnJoinButtonClicked();

	void SetupMainMenu();
	void SetupSessionMenu();
	void SetupOptionsMenu();
	void ShowMainMenu();
	void ShowSessionMenu();
	void ShowOptionsMenu();
	void ShowWarningText();
	void HideWarningText();
	void UpdateWindowMode();
	void UpdateResolution();
	void UpdateVSync();
	void ApplySettings();

	void HostGame();
	void JoinGame();

	// Main Menu Elements
	UButton *startButton;
	UButton *optionsButton;
	UButton *quitButton;

	// Options Menu Elements
	UButton *backButton;
	UButton *applyButton;
	
	UButton *windowNext;
	UButton *windowPrev;
	UButton *resolutionNext;
	UButton *resolutionPrev;
	UButton *vsyncToggle;
	
	UTextBlock *windowText;
	UTextBlock *resolutionText;

	// Session Menu Elements
	UButton *hostButton;
	UButton *joinButton;
	UEditableTextBox *nameTextBox;
	UTextBlock *warningTextBlock;
	

	UCanvasPanel *mainMenuPanel;
	UCanvasPanel *sessionPanel;
	UCanvasPanel *optionsPanel;

	UGameUserSettings *MyGameUserSettings;

	TArray<FIntPoint> SupportedResolutions;

};
