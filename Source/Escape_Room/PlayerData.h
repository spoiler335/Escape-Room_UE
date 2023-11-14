// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerData.generated.h"

UCLASS()
class ESCAPE_ROOM_API UPlayerData : public UObject
{
	GENERATED_BODY()

private:
	static UPlayerData* MyInstance;
	UPlayerData();

public:
	static UPlayerData* GetInstance();

	FString playerName;
};
