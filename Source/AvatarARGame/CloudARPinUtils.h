// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FindSessionsCallbackProxy.h"

#include "CloudARPinUtils.generated.h"

/**
 * 
 */
UCLASS()
class AVATARARGAME_API UCloudARPinUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "UCloudARPinSampleUtils")
	static FString GetLocalHostIPAddress();

	UFUNCTION(BlueprintPure, Category = "UCloudARPinSampleUtils")
	static FString GetSessionId(const FBlueprintSessionResult& Result);

	UFUNCTION(BlueprintPure, Category = "UCloudARPinSampleUtils", meta = (WorldContext = "WorldContextObject"))
	static FString GetHostSessionId(UObject* WorldContextObject);
	
};
