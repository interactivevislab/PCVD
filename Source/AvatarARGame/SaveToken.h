// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveToken.generated.h"

/**
 * 
 */
UCLASS()
class AVATARARGAME_API USaveToken : public USaveGame
{
	GENERATED_BODY()
public:
	USaveToken();
	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString refreshToken;
		static FString SaveSlotName;
};
