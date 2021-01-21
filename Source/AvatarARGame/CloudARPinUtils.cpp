// Fill out your copyright notice in the Description page of Project Settings.


#include "CloudARPinUtils.h"
#include "SocketSubsystem.h"
#include "IPAddress.h"
#include "OnlineSubsystemUtils.h"
#include "Engine.h"

FString UCloudARPinUtils::GetLocalHostIPAddress()
{
	bool bCanBindAll;
	TSharedRef<FInternetAddr> LocalIp = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalHostAddr(*GLog, bCanBindAll);
	if (LocalIp->IsValid())
	{
		return LocalIp->ToString(false);
	}
	return FString("");
}

FString UCloudARPinUtils::GetSessionId(const FBlueprintSessionResult& Result)
{
	return Result.OnlineResult.Session.OwningUserName.Right(5);
}

FString UCloudARPinUtils::GetHostSessionId(UObject* WorldContextObject)
{
	IOnlineSubsystem* OnlineSubsystem = Online::GetSubsystem(GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull));
	auto Sessions = OnlineSubsystem->GetSessionInterface();
	auto Session = Sessions->GetNamedSession(NAME_GameSession);
	if (Session != nullptr)
	{
		return Session->OwningUserName.Right(5);
	}

	return "";
}
