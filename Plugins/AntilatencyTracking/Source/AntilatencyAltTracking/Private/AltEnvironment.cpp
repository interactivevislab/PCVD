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

#include "AltEnvironment.h"

#include "AltTrackingLibrary.h"
#include "AltTrackingLog.h"

#include <ExceptionCheck.h>

UAltEnvironment* UAltEnvironment::CreateEnvironment() {
    return CreateEnvironmentUsingName("default");
}

UAltEnvironment* UAltEnvironment::CreateEnvironmentUsingCode(const FString& code) {
    FString defaultEnvironmentCode;
    auto exception = UAltEnvironment::GetEnvironmentCode(code, defaultEnvironmentCode);
    if (exception != Antilatency::InterfaceContract::ExceptionCode::Ok) {
        return nullptr;
    }

    auto trackingLibrary = UAltTrackingLibrary::GetLibrary();
    if (trackingLibrary == nullptr) {
        ALTTRACKING_LOG(Error, TEXT("Failed to get tracking library"));
        return nullptr;
    }

    Antilatency::Alt::Tracking::IEnvironment environment;
    exception = trackingLibrary->CreateNativeEnvironment(code, environment);
    if (exception != Antilatency::InterfaceContract::ExceptionCode::Ok) {
        return nullptr;
    }

    auto result = NewObject<UAltEnvironment>();
    result->_native = environment;

    return result;
}

UAltEnvironment* UAltEnvironment::CreateEnvironmentUsingName(const FString& name) {
    FString code;
    auto exception = UAltEnvironment::GetEnvironmentCode(name, code);
    return UAltEnvironment::CreateEnvironmentUsingCode(code);
}


Antilatency::Alt::Tracking::IEnvironment UAltEnvironment::GetNative() const {
    return _native;
}

Antilatency::InterfaceContract::ExceptionCode UAltEnvironment::GetMarkers(TArray<FVector>& result) const {
    result.Empty();

    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    std::vector<Antilatency::Math::float3> markers;
    auto exception = _native.getMarkers(markers);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_native, exception);

    for (auto marker : markers) {
        result.Add({ marker.z * 100.0f, marker.x * 100.0f, marker.y * 100.0f});
    }

    return exception;
}

Antilatency::InterfaceContract::ExceptionCode UAltEnvironment::IsMutable(bool& result) const {
    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    Antilatency::InterfaceContract::LongBool nativeResult;
    auto exception = _native.isMutable(nativeResult);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_native, exception);

    result = static_cast<bool>(nativeResult);
    return exception;
}

Antilatency::InterfaceContract::ExceptionCode UAltEnvironment::GetUpdateId(int32& result) const {
    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    auto mutableEnvironment = _native.queryInterface<Antilatency::Alt::Tracking::IEnvironmentMutable>();
    if (mutableEnvironment == nullptr) {
        ALTTRACKING_LOG(Warning, TEXT("Failed to get the IEnvironmentMutable for the current environment, seems like this environment is not mutable."));
        return Antilatency::InterfaceContract::ExceptionCode::NoInterface;
    }

    int32_t nativeUpdateId;
    auto exception = mutableEnvironment.getUpdateId(nativeUpdateId);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_native, exception);

    result = nativeUpdateId;
    return exception;
}

bool UAltEnvironment::IsValid() const {
    if (_native == nullptr) {
        ALTTRACKING_LOG(Warning, TEXT("IEnvironment is nullptr"));
        return false;
    }

    return true;
}

Antilatency::InterfaceContract::ExceptionCode UAltEnvironment::GetEnvironmentCode(const FString& name, FString& result) {
    result.Empty();

    if (name.IsEmpty()) {
        ALTTRACKING_LOG(Error, TEXT("Cannot get code for environment with empty name"));
        return Antilatency::InterfaceContract::ExceptionCode::InvalidArg;
    }

    auto storageLibrary = UStorageClientLibrary::GetLibrary();
    if (storageLibrary == nullptr) {
        ALTTRACKING_LOG(Error, TEXT("Failed to get storage library"));
        return Antilatency::InterfaceContract::ExceptionCode::UnknownFailure;
    }

    UStorage* storage;
    auto exception = storageLibrary->GetLocalStorage(storage);
    if (exception != Antilatency::InterfaceContract::ExceptionCode::Ok) {
        return Antilatency::InterfaceContract::ExceptionCode::UnknownFailure;
    }

    FString environmentCode;
    exception = storage->Read("environment", "default", environmentCode);
    if (exception != Antilatency::InterfaceContract::ExceptionCode::Ok) {
        return Antilatency::InterfaceContract::ExceptionCode::UnknownFailure;
    }

    result = environmentCode;
    return exception;
}