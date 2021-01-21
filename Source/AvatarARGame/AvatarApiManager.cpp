// Fill out your copyright notice in the Description page of Project Settings.



#include "AvatarApiManager.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Interfaces/IHttpRequest.h"
#include "HttpModule.h"

#pragma warning(disable:4706)

TSharedRef<IHttpRequest> UAvatarApiManager::ConstructRequestWithStringBody(FString body, FString url)
{
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetVerb("POST");
	HttpRequest->SetHeader("Content-Type", "application/x-www-form-urlencoded");
	HttpRequest->SetURL(url);
	HttpRequest->SetContentAsString(body);
	return HttpRequest;
}



void UAvatarApiManager::GetPower(const FAvatarAPIPowerResponse& Callback)
{
	Callback.Execute(666);
}

//Mihail Garaev Credential
//311335
//2uHtwyRp


void UAvatarApiManager::GetUserInfoFromAvatarAPI(const FAvatarAPIGetUserInfoResponse& Callback)
{
	CallBackUsserInfo = Callback;
	TSharedRef<IHttpRequest> GetUserInfoRequest = FHttpModule::Get().CreateRequest();
	GetUserInfoRequest->SetVerb("GET");
	GetUserInfoRequest->SetHeader("Authorization", "Bearer "+ UserAccessToken);
	GetUserInfoRequest->SetHeader("Content-Type", "application/json");
	GetUserInfoRequest->SetURL("https://test1.avatar.onti.actcognitive.org/user/users/me");
	GetUserInfoRequest->OnProcessRequestComplete().BindUObject(this, &UAvatarApiManager::GetUserInfoCallback);
	GetUserInfoRequest->ProcessRequest(); 
	
}

void UAvatarApiManager::ChangeUserIcon(UTexture2D* icon)
{
	icon->AddToRoot();
	curentAuthUser.userIcon = icon;

}

void UAvatarApiManager::ChangeStaticMeshForUser(USkeletalMesh* mesh)
{
	mesh->AddToRoot();
	curentAuthUser.userMesh = mesh;
	UE_LOG(LogTemp, Log, TEXT("set mesh error:%s"), *mesh->GetName());
}

void UAvatarApiManager::SetUserInfo_Dev(FUserInfo userInfo)
{
	curentAuthUser = userInfo;
}

void UAvatarApiManager::GetUserInfoCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	FString responseString = Response->GetContentAsString();
	int code = Response->GetResponseCode();
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(responseString);

	FJsonSerializer::Deserialize(JsonReader, JsonObject);
	

	TArray<TSharedPtr<FJsonValue>> arr = JsonObject->GetArrayField("attributes");
	for (int i = 0; i < arr.Num(); i++)
	{
		TSharedPtr<FJsonObject> bufObject = arr[i]->AsObject();
		TSharedPtr<FJsonValue> nameField = bufObject->TryGetField("name");
		if (nameField != nullptr)
		{
			FString name = nameField->AsString();

			if (name == "firstName")
			{
				curentAuthUser.firstName = bufObject->GetStringField("value");
			}
			if (name == "isu_id")
			{
				curentAuthUser.isu_id = bufObject->GetNumberField("value");
			}
			if (name == "lastName")
			{
				curentAuthUser.lastName = bufObject->GetStringField("value");
			}
			if (name == "game_power")
			{
				curentAuthUser.game_power = bufObject->GetNumberField("value");
			}

		}
	}
	CallBackUsserInfo.Execute(curentAuthUser);
}




FUserInfo UAvatarApiManager::GetUserInfo()
{
	if (curentAuthUser.userMesh != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("get mesh:%s"), *curentAuthUser.userMesh->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("mesh=====nulllllll"));

	}
	return curentAuthUser;
}

void UAvatarApiManager::AuthFromUserCredential(FString userName, FString pass, const FAvatarAPIAuthResponse& Callback)
{
	CallBackAuth = Callback;
	
	TSharedRef<IHttpRequest> AuthRequest = ConstructRequestWithStringBody(
		"grant_type=password&client_id=digital-avatar&client_secret=0e51068f-7355-4f25-a633-e23a0fe5f79e&username=" + userName + "&password=" + pass,
		"https://sso.itmo.ru/realms/digital-university/protocol/openid-connect/token");
	AuthRequest->OnProcessRequestComplete().BindUObject(this, &UAvatarApiManager::AuthCompleted);
	AuthRequest->ProcessRequest();
}


void UAvatarApiManager::AuthCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

	int32 a = Response->GetResponseCode();
	FString responseString = Response->GetContentAsString();

	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(responseString);

	FJsonSerializer::Deserialize(JsonReader, JsonObject);


	//Try get token Field
	TSharedPtr<FJsonValue> accessToken = JsonObject->TryGetField("access_token");
	TSharedPtr<FJsonValue> refreshToken = JsonObject->TryGetField("refresh_token");

	//IF json dont contains token field
	if (accessToken == nullptr)
	{
		//Try get error desc
		TSharedPtr<FJsonValue> error = JsonObject->TryGetField("error_description");
		if (error == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("unknown authorization error"));
		}

		FString errorDescription = error->AsString();
		CallBackAuth.Execute(false, "", "", errorDescription);
		
		UE_LOG(LogTemp, Error, TEXT("authorization error:%s"), &errorDescription);
		return;
	}

	//get tokens value
	FString refreshTokenString = refreshToken->AsString();
	FString accessTokenString = accessToken->AsString();

	SetUsersToken(accessTokenString, refreshTokenString);

	//Save refresh token
	SaveRefreshToken(refreshTokenString);

	CallBackAuth.Execute(true, refreshTokenString, accessTokenString, "");
	UE_LOG(LogTemp, Log, TEXT("authorization success=> token:%s"), &accessTokenString);


}


void UAvatarApiManager::TryAuthFromRefreshToken(const FAvatarAPIAuthResponse& Callback)
{
	CallBackAuth = Callback;
	if (LoadRefreshToken())
	{
		CheckValidRefreshToken(LoadedRefreshToken);
	}
	else
	{
		Callback.Execute(false, "", "","refresh token can't be loaded");
	}
}

void UAvatarApiManager::UserExit()
{
	UserAccessToken.Empty();
	UserRefreshToken.Empty();
	LoadedRefreshToken.Empty();
	DeleteRefreshToken();
}

void UAvatarApiManager::SetUsersToken(FString _accessToken, FString _refreshToken)
{
	UserAccessToken = _accessToken;
	UserRefreshToken = _refreshToken;
}


void UAvatarApiManager::SaveRefreshTokenCallback(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	if (bSuccess)
	{
		UE_LOG(LogTemp, Log, TEXT("Save refresh token success"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Error save refresh token"));
	}
}

void UAvatarApiManager::SaveRefreshToken(FString refreshToken)
{
	saveTokenInstance = Cast<USaveToken>(UGameplayStatics::CreateSaveGameObject(USaveToken::StaticClass()));
	saveTokenInstance->refreshToken = refreshToken;
	FAsyncSaveGameToSlotDelegate SavedDelegate;
	
	SavedDelegate.BindUObject(this, &UAvatarApiManager::SaveRefreshTokenCallback);

	// Start async save process.
	UGameplayStatics::AsyncSaveGameToSlot(saveTokenInstance, USaveToken::SaveSlotName, 0, SavedDelegate);

}



bool UAvatarApiManager::LoadRefreshToken()
{
	loadTokenInstance = Cast<USaveToken>(UGameplayStatics::CreateSaveGameObject(USaveToken::StaticClass()));
	loadTokenInstance = Cast<USaveToken>(UGameplayStatics::LoadGameFromSlot(USaveToken::SaveSlotName, 0));
	if (loadTokenInstance!=nullptr)
	{
		// The operation was successful, so LoadedGame now contains the data we saved earlier.
		LoadedRefreshToken = loadTokenInstance->refreshToken;
		UE_LOG(LogTemp, Log, TEXT("Load refresh token success"));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("refresh token can't be loaded"));
		return false;
	}
}

void UAvatarApiManager::DeleteRefreshToken()
{
	UGameplayStatics::DeleteGameInSlot(USaveToken::SaveSlotName, 0);
}



void UAvatarApiManager::RefreshAccessToken()
{
	if (LoadedRefreshToken.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Can't read refresh token"));
		return;
	}
	TSharedRef<IHttpRequest> RefreshRequest = ConstructRequestWithStringBody(
		"grant_type=refresh_token&client_id=digital-avatar&client_secret=0e51068f-7355-4f25-a633-e23a0fe5f79e&refresh_token=" + LoadedRefreshToken,
		"https://sso.itmo.ru/realms/digital-university/protocol/openid-connect/token");
	RefreshRequest->OnProcessRequestComplete().BindUObject(this, &UAvatarApiManager::RefreshAccessTokenCallback);
	RefreshRequest->ProcessRequest();

}

void UAvatarApiManager::RefreshAccessTokenCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

		FString responseString = Response->GetContentAsString();

		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(responseString);

		FJsonSerializer::Deserialize(JsonReader, JsonObject);

		//Try get token Field
		TSharedPtr<FJsonValue> refreshToken = JsonObject->TryGetField("refresh_token");
		TSharedPtr<FJsonValue> accessToken = JsonObject->TryGetField("access_token");
		if (accessToken == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("unknown error in response from refresh tokens"));			
			CallBackAuth.Execute(false, "", "", "unknown error in response from refresh tokens");
			return;
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("success  refresh tokens"));
			FString refreshTokenString = refreshToken->AsString();
			FString accessTokenString = accessToken->AsString();

			SetUsersToken(accessTokenString, refreshTokenString);

			CallBackAuth.Execute(true, refreshTokenString, accessTokenString, "");
			//save new refresh token
			SaveRefreshToken(refreshTokenString);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Error request refresh tokens"));
		CallBackAuth.Execute(false, "", "", "Error request refresh tokens");
		return;
	}


}



void UAvatarApiManager::CheckValidRefreshToken(FString refreshToken)
{

	TSharedRef<IHttpRequest> CheckValidRequest = ConstructRequestWithStringBody(
		"grant_type=password&client_id=digital-avatar&client_secret=0e51068f-7355-4f25-a633-e23a0fe5f79e&token=" + refreshToken,
		"https://sso.itmo.ru/realms/digital-university/protocol/openid-connect/token/introspect");
	CheckValidRequest->OnProcessRequestComplete().BindUObject(this, &UAvatarApiManager::CheckValidRefreshTokenCallback);
	CheckValidRequest->ProcessRequest();

}

void UAvatarApiManager::CheckValidRefreshTokenCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

	FString responseString = Response->GetContentAsString();

	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(responseString);

	FJsonSerializer::Deserialize(JsonReader, JsonObject);


	//Try get token Field
	TSharedPtr<FJsonValue> activeField = JsonObject->TryGetField("active");

	//IF json dont contains token field
	if (activeField == nullptr)
	{
		
		UE_LOG(LogTemp, Error, TEXT("unknown error from check valid refresh token"));
		return;
	}

	//get tokens value
	bool tokenActive = activeField->AsBool();
	if (activeField)
	{
		RefreshAccessToken();
	}
	else
	{
		CallBackAuth.Execute(false,"","","refresh token not active");
	}
}
