// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Delegates/DelegateCombinations.h"
#include "Subsystems/EngineSubsystem.h"
#include "Subsystems/SubsystemCollection.h"
#include "UObject/NoExportTypes.h"

#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpModule.h"
#include "SaveToken.h"
#include "Kismet/GameplayStatics.h"
/**
 * 
 */
#include "AvatarApiManager.generated.h"


USTRUCT(BlueprintType)
struct FUserInfo
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString firstName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString lastName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 isu_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 game_power;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh *userMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* userIcon;

};



DECLARE_DYNAMIC_DELEGATE_OneParam(FAvatarAPIPowerResponse, int32, Power);
DECLARE_DYNAMIC_DELEGATE_FourParams(FAvatarAPIAuthResponse, bool, Success,FString,refreshToken, FString,accessToken,FString, error );
DECLARE_DYNAMIC_DELEGATE_OneParam(FAvatarAPIVailidRefreshTokenResponse, bool, valid);
DECLARE_DYNAMIC_DELEGATE_OneParam(FAvatarAPIGetUserInfoResponse, FUserInfo, userInfo);


UCLASS(Blueprintable)
class AVATARARGAME_API UAvatarApiManager : public UObject
{
		GENERATED_BODY()
public:
	
	
		
		UFUNCTION(BlueprintCallable, Category = "AvatarAPI")
			FUserInfo GetUserInfo();
		UFUNCTION(BlueprintCallable, Category = "AvatarAPI")
			void AuthFromUserCredential(FString userName,FString pass,const FAvatarAPIAuthResponse& Callback);
		UFUNCTION(BlueprintCallable, Category = "AvatarAPI")
			void TryAuthFromRefreshToken(const FAvatarAPIAuthResponse& Callback);
		UFUNCTION(BlueprintCallable, Category = "AvatarAPI")
			void UserExit();
		UFUNCTION(BlueprintCallable, Category = "AvatarAPI")
			void GetUserInfoFromAvatarAPI(const FAvatarAPIGetUserInfoResponse& Callback);
		UFUNCTION(BlueprintCallable, Category = "AvatarAPI")
			void ChangeStaticMeshForUser(USkeletalMesh* mesh);		
		UFUNCTION(BlueprintCallable, Category = "AvatarAPI")
			void SetUserInfo_Dev(FUserInfo userInfo);
		UFUNCTION(BlueprintCallable, Category = "AvatarAPI")
			void ChangeUserIcon(UTexture2D* icon);

private:
	FString UserAccessToken;
	FString UserRefreshToken;

	//dont implement
	void GetPower(const FAvatarAPIPowerResponse& Callback);

	void SetUsersToken(FString _accessToken, FString _refreshToken);

	FString LoadedRefreshToken = "";
	
	FUserInfo curentAuthUser;
	USaveToken* saveTokenInstance;
	USaveToken* loadTokenInstance;
	//Save--Load--Delete refreshtoken
	void SaveRefreshToken(FString refreshToken);
	bool LoadRefreshToken();
	void DeleteRefreshToken();


	void CheckValidRefreshToken(FString refreshToken);
	void RefreshAccessToken();


	//Delegate
	FAvatarAPIGetUserInfoResponse CallBackUsserInfo;
	FAvatarAPIAuthResponse CallBackAuth;
	//CAllbacks
	void AuthCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void SaveRefreshTokenCallback(const FString& SlotName, const int32 UserIndex, bool bSuccess);
	void RefreshAccessTokenCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void GetUserInfoCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);


	void CheckValidRefreshTokenCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	TSharedRef<IHttpRequest> ConstructRequestWithStringBody(FString body, FString url);
};

