// Copyright 2020, ALT LLC. All Rights Reserved.
// This file is part of Antilatency SDK.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://www.antilatency.com/eula
// You may not use this file except in compliance with the License.
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "IAntilatencyStorageClientModule.h"
#include "Modules/ModuleManager.h"
#include <Interfaces/IPluginManager.h>
#include "Misc/Paths.h"

/*
#if PLATFORM_ANDROID

#include <dlfcn.h>
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"

#endif*/

#include "StorageClientLog.h"
#include <Antilatency.InterfaceContract.UELibraryLoader.h>

class FAntilatencyStorageClientModule : public IAntilatencyStorageClientModule {
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual bool SupportsDynamicReloading() override { return true; }
};

IMPLEMENT_MODULE(FAntilatencyStorageClientModule, AntilatencyStorageClient)


void FAntilatencyStorageClientModule::StartupModule() {
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
}


void FAntilatencyStorageClientModule::ShutdownModule() {
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

FString IAntilatencyStorageClientModule::GetPluginName() {
	return TEXT("AntilatencyTracking");
}

FString IAntilatencyStorageClientModule::GetPluginDirectory() {
	return IPluginManager::Get().FindPlugin("AntilatencyTracking")->GetBaseDir();
	//return FPaths::Combine(FPaths::ProjectPluginsDir(), GetPluginName());
}

FString IAntilatencyStorageClientModule::GetPluginBinariesDirectory() {
	//return FPaths::Combine(GetPluginDirectory(), TEXT("Binaries"));
	auto pluginDir = GetPluginDirectory();
	auto libDir = FPaths::Combine(*pluginDir, TEXT("ThirdParty"), TEXT("Antilatency"), TEXT("Bin"));

	FString result;
	//TODO: Add linux, mac, etc.
#if PLATFORM_WINDOWS
	#if PLATFORM_64BITS
		result =  FPaths::Combine(*libDir, TEXT("Win64"));
	#else
		result = FPaths::Combine(*libDir, TEXT("Win32"));
	#endif
#else
	result = TEXT("");
#endif
	return result;
}

void IAntilatencyStorageClientModule::PreUnloadCallback() {
    STORAGECLIENT_LOG(Log, TEXT("IAntilatencyStorageClientModule: PreUnloadCallback"));
    if (_storageClientLibrary != nullptr) {
        _storageClientLibrary = Antilatency::StorageClient::ILibrary{};
    }
}

Antilatency::StorageClient::ILibrary IAntilatencyStorageClientModule::GetNativeLibrary() {
    if (_storageClientLibrary == nullptr) {
        _storageClientLibrary = LoadAntilatencyLibrary<Antilatency::StorageClient::ILibrary>(FString("AntilatencyStorageClient"), IAntilatencyStorageClientModule::GetPluginBinariesDirectory());
    }

    if (_storageClientLibrary == nullptr) {
        STORAGECLIENT_LOG(Error, TEXT("Failed to get Antilatecy Storage Client ILibrary"));
    }

    return _storageClientLibrary;
}