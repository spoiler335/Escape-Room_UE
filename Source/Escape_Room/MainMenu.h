// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
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

	void SetupMainMenu();
	void SetupSessionMenu();
	void SetupOptionsMenu();

	// Main Menu Elements
	UButton *startButton;
	UButton *optionsButton;
	UButton *quitButton;

	// Options Menu Elements
	UButton *backButton;

	// Session Menu Elements

	UCanvasPanel *mainMenuPanel;
	UCanvasPanel *sessionPanel;
	UCanvasPanel *optionsPanel;
};
