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

#include "AltTrackingLibrary.h"
#include "IAntilatencyAltTrackingModule.h"
#include "AltTrackingLog.h"
#include "InterfaceIdUtils.h"

#include "Math/UnrealMathUtility.h"

#include <ExceptionCheck.h>

UAltTrackingLibrary* UAltTrackingLibrary::GetLibrary() {
    auto module = IAntilatencyAltTrackingModule::Get();
    auto library = module.GetNativeLibrary();

    if (library == nullptr) {
        return nullptr;
    }

    auto result = NewObject<UAltTrackingLibrary>();
    result->Init(library);
    return result;
}

void UAltTrackingLibrary::Init(Antilatency::Alt::Tracking::ILibrary& library) {
    _library = library;
}

Antilatency::InterfaceContract::ExceptionCode UAltTrackingLibrary::CreateNativeEnvironment(const FString& code, Antilatency::Alt::Tracking::IEnvironment& result) const {
    result = {};

    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    auto exception = _library.createEnvironment(std::string(TCHAR_TO_UTF8(*code)), result);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_library, exception);
    
    return exception;
}


Antilatency::InterfaceContract::ExceptionCode UAltTrackingLibrary::CreatePlacement(const FString& code, FAltPose& result) const {
    result = {};

    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    Antilatency::Math::floatP3Q nativePlacement;
    auto exception = _library.createPlacement(std::string(TCHAR_TO_UTF8(*code)), nativePlacement);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_library, exception);

    result = FAltPose(nativePlacement);
    return exception;
}


Antilatency::InterfaceContract::ExceptionCode UAltTrackingLibrary::CreateTracking(const UDeviceNetwork* network, const FAdnNode& node, const UAltEnvironment* environment, UAltTrackingCotask*& result) const {
    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }
	auto constructor = GetCotaskConstructor();
    if (constructor == nullptr) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    Antilatency::Alt::Tracking::ITrackingCotask nativeCotask;
    auto exception = constructor.startTask(network->GetNative(), node.ToNative(), environment->GetNative(), nativeCotask);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_library, exception);
    if (nativeCotask == nullptr) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    result = UAltTrackingCotask::CreateAltTrackingCotask(nativeCotask);
    return exception;
}


Antilatency::InterfaceContract::ExceptionCode UAltTrackingLibrary::EncodePlacement(const FAltPose& placement, FString& result) const {
    result.Empty();

    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    std::string nativeValue;
    auto exception = _library.encodePlacement(placement.ToNative().position, {	FMath::DegreesToRadians(placement.Rotation.Pitch),
																				FMath::DegreesToRadians(placement.Rotation.Yaw),
																				FMath::DegreesToRadians(placement.Rotation.Roll)
																			}, nativeValue);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_library, exception);

    result = { nativeValue.c_str() };
    return exception;
}


bool UAltTrackingLibrary::IsValid() const {
    if (_library == nullptr) {
        ALTTRACKING_LOG(Warning, TEXT("Library is null"));
        return false;
    }
    return true;
}

Antilatency::InterfaceContract::ExceptionCode UAltTrackingLibrary::IsSupported(const UDeviceNetwork* network, const FAdnNode& node, bool& result) const {
    result = false;

    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    auto cotaskConstructor = GetCotaskConstructor();

    if (cotaskConstructor == nullptr) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    Antilatency::InterfaceContract::LongBool nativeResult;
    auto exception = cotaskConstructor.isSupported(network->GetNative(), node.ToNative(), nativeResult);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_library, exception);

    result = static_cast<bool>(nativeResult);

    return exception;
}

Antilatency::InterfaceContract::ExceptionCode UAltTrackingLibrary::FindSupportedNodes(const UDeviceNetwork* network, TArray<FAdnNode>& result) const {
    result.Empty();

    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    auto constructor = GetCotaskConstructor();
    if (constructor == nullptr) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    std::vector<Antilatency::DeviceNetwork::NodeHandle> nativeResult;
    auto exception = constructor.findSupportedNodes(network->GetNative(), nativeResult);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_library, exception);

    for (auto node : nativeResult) {
        result.Add(FAdnNode(node));
    }

    return exception;
}

Antilatency::Alt::Tracking::ITrackingCotaskConstructor UAltTrackingLibrary::GetCotaskConstructor() const {
    if (!IsValid()) {
        return nullptr;
    }
    Antilatency::Alt::Tracking::ITrackingCotaskConstructor result;
    auto exception = _library.createTrackingCotaskConstructor(result);
    ANTILATENCY_EXCEPTION_CHECK(_library, exception);

    return result;
}