// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerData.h"

UPlayerData* UPlayerData::MyInstance = nullptr;

UPlayerData* UPlayerData::GetInstance()
{
    // Create the instance if it doesn't exist
    if (MyInstance == nullptr)
    {
        MyInstance = NewObject<UPlayerData>();
        MyInstance->AddToRoot(); // Optional: Add to root to prevent automatic garbage collection
    }

    return MyInstance;
}

UPlayerData::UPlayerData()
{
    playerName = "Player";
}