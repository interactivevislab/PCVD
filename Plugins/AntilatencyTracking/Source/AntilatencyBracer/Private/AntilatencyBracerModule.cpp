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

#include "IAntilatencyBracerModule.h"
#include "Modules/ModuleManager.h"
#include <Interfaces/IPluginManager.h>
#include "Misc/Paths.h"

#include "BracerLog.h"

#include <Antilatency.InterfaceContract.UELibraryLoader.h>

class FAntilatencyBracerModule : public IAntilatencyBracerModule
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual bool SupportsDynamicReloading() override { return true; }
};

IMPLEMENT_MODULE(FAntilatencyBracerModule, AntilatencyBracer)

void FAntilatencyBracerModule::StartupModule()
{
	BRACER_LOG(Log, TEXT("IAntilatencyBracerModule: Start"));
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
}

void FAntilatencyBracerModule::ShutdownModule()
{
    BRACER_LOG(Log, TEXT("IAntilatencyBracerModule: Shutdown"));
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

FString IAntilatencyBracerModule::GetPluginName()
{
	return TEXT("AntilatencyTracking");
}

FString IAntilatencyBracerModule::GetPluginDirectory()
{
	return IPluginManager::Get().FindPlugin("AntilatencyTracking")->GetBaseDir();
	//return FPaths::Combine(FPaths::ProjectPluginsDir(), GetPluginName());
}

FString IAntilatencyBracerModule::GetPluginBinariesDirectory()
{
	auto pluginDir = GetPluginDirectory();
	auto libDir = FPaths::Combine(*pluginDir, TEXT("ThirdParty"), TEXT("Antilatency"), TEXT("Bin"));

	FString result;
#if PLATFORM_WINDOWS
#if PLATFORM_64BITS
    result = FPaths::Combine(*libDir, TEXT("Win64"));
#else
    result = FPaths::Combine(*libDir, TEXT("Win32"));
#endif
#else
	result = TEXT("");
#endif
	return result;
}

void IAntilatencyBracerModule::PreUnloadCallback()
{
    BRACER_LOG(Log, TEXT("IAntilatencyBracerModule: PreUnloadCallback"));
	if (_library != nullptr) {
        _library = Antilatency::Bracer::ILibrary{};
    }
}

Antilatency::Bracer::ILibrary IAntilatencyBracerModule::GetNativeLibrary()
{
	if (_library == nullptr) {
		_library = LoadAntilatencyLibrary<Antilatency::Bracer::ILibrary>(FString("AntilatencyBracer"), IAntilatencyBracerModule::GetPluginBinariesDirectory());
	}

    if (_library == nullptr) {
        BRACER_LOG(Error, TEXT("Failed to get Antilatecy Bracer ILibrary"));
    }

    return _library;
}