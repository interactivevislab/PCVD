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

#include "AltTrackingFunctionLibrary.h"

void UAltTrackingFunctionLibrary::GetTrackingLibrary(UAltTrackingLibrary*& result, EAltTrackingExceptionResult& exception) {
    result = UAltTrackingLibrary::GetLibrary();
    exception = static_cast<EAltTrackingExceptionResult>(result != nullptr);
}

void UAltTrackingFunctionLibrary::CreatePlacement(const UAltTrackingLibrary* altTrackingLibrary, const FString& code, FAltPose& result, EAltTrackingExceptionResult& exception) {
    if (altTrackingLibrary == nullptr) {
        exception = EAltTrackingExceptionResult::Fail;
        return;
    }

    auto callResult = altTrackingLibrary->CreatePlacement(code, result);
    exception = static_cast<EAltTrackingExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UAltTrackingFunctionLibrary::CreateTracking(const UAltTrackingLibrary* altTrackingLibrary, const UDeviceNetwork* network, const FAdnNode& node, const UAltEnvironment* environment, UAltTrackingCotask*& result, EAltTrackingExceptionResult& exception) {
    if (altTrackingLibrary == nullptr) {
        exception = EAltTrackingExceptionResult::Fail;
        return;
    }

    auto callResult = altTrackingLibrary->CreateTracking(network, node, environment, result);
    exception = static_cast<EAltTrackingExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UAltTrackingFunctionLibrary::EncodePlacement(const UAltTrackingLibrary* altTrackingLibrary, const FAltPose& placement, FString& result, EAltTrackingExceptionResult& exception) {
    if (altTrackingLibrary == nullptr) {
        exception = EAltTrackingExceptionResult::Fail;
        return;
    }

    auto callResult = altTrackingLibrary->EncodePlacement(placement, result);
    exception = static_cast<EAltTrackingExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UAltTrackingFunctionLibrary::IsSupported(const UAltTrackingLibrary* altTrackingLibrary, const UDeviceNetwork* network, const FAdnNode& node, bool& result, EAltTrackingExceptionResult& exception) {
    result = false;
    if (altTrackingLibrary == nullptr || network == nullptr) {
        exception = EAltTrackingExceptionResult::Fail;
        return;
    }

    auto callResult = altTrackingLibrary->IsSupported(network, node, result);
    exception = static_cast<EAltTrackingExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UAltTrackingFunctionLibrary::FindSupportedNodes(const UAltTrackingLibrary* altTrackingLibrary, const UDeviceNetwork* network, TArray<FAdnNode>& result, EAltTrackingExceptionResult& exception) {
    result.Empty();

    if (altTrackingLibrary == nullptr || network == nullptr) {
        exception = EAltTrackingExceptionResult::Fail;
        return;
    }

    auto callResult = altTrackingLibrary->FindSupportedNodes(network, result);
    exception = static_cast<EAltTrackingExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

bool UAltTrackingFunctionLibrary::IsLibraryValid(const UAltTrackingLibrary* altTrackingLibrary) {
    if (altTrackingLibrary == nullptr) {
        return false;
    }

    return altTrackingLibrary->IsValid();
}

void UAltTrackingFunctionLibrary::GetState(const UAltTrackingCotask* trackingCotask, FTrackingState& result, EAltTrackingExceptionResult& exception) {
    if (trackingCotask == nullptr) {
        exception = EAltTrackingExceptionResult::Fail;
        return;
    }

    auto callResult = trackingCotask->GetState(result);
    exception = static_cast<EAltTrackingExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UAltTrackingFunctionLibrary::GetExtrapolatedState(const UAltTrackingCotask* trackingCotask, const FAltPose& placement, const float deltaTime, FTrackingState& result, EAltTrackingExceptionResult& exception) {
    if (trackingCotask == nullptr) {
        exception = EAltTrackingExceptionResult::Fail;
        return;
    }

    auto callResult = trackingCotask->GetExtrapolatedState(placement, deltaTime, result);
    exception = static_cast<EAltTrackingExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UAltTrackingFunctionLibrary::IsTaskFinished(const UAltTrackingCotask* trackingCotask, bool& result, EAltTrackingExceptionResult& exception) {
    if (trackingCotask == nullptr) {
        exception = EAltTrackingExceptionResult::Fail;
        return;
    }

    auto callResult = trackingCotask->IsTaskFinished(result);
    exception = static_cast<EAltTrackingExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}


void UAltTrackingFunctionLibrary::Stop(UAltTrackingCotask* trackingCotask) {
    if (trackingCotask == nullptr) {
        return;
    }

    trackingCotask->Stop();
}

bool UAltTrackingFunctionLibrary::IsTrackingTaskValid(const UAltTrackingCotask* trackingCotask) {
    if (trackingCotask == nullptr) {
        return false;
    }
    
    return trackingCotask->IsValid();
}



void UAltTrackingFunctionLibrary::CreateEnvironment(UAltEnvironment*& result, EAltTrackingExceptionResult& exception) {
    result = UAltEnvironment::CreateEnvironment();
    exception = static_cast<EAltTrackingExceptionResult>(result != nullptr);
}

void UAltTrackingFunctionLibrary::CreateEnvironmentUsingCode(const FString& code, UAltEnvironment*& result, EAltTrackingExceptionResult& exception) {
    result = UAltEnvironment::CreateEnvironmentUsingCode(code);
    exception = static_cast<EAltTrackingExceptionResult>(result != nullptr);
}

void UAltTrackingFunctionLibrary::CreateEnvironmentUsingName(const FString& name, UAltEnvironment*& result, EAltTrackingExceptionResult& exception) {
    result = UAltEnvironment::CreateEnvironmentUsingName(name);
    exception = static_cast<EAltTrackingExceptionResult>(result != nullptr);
}

void UAltTrackingFunctionLibrary::GetMarkers(const UAltEnvironment* environment, TArray<FVector>& result, EAltTrackingExceptionResult& exception) {
    if (environment == nullptr) {
        exception = EAltTrackingExceptionResult::Fail;
        return;
    }

    auto callResult = environment->GetMarkers(result);
    exception = static_cast<EAltTrackingExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UAltTrackingFunctionLibrary::IsMutable(const UAltEnvironment* environment, bool& result, EAltTrackingExceptionResult& exception) {
    if (environment == nullptr) {
        exception = EAltTrackingExceptionResult::Fail;
        return;
    }

    auto callResult = environment->IsMutable(result);
    exception = static_cast<EAltTrackingExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UAltTrackingFunctionLibrary::GetUpdateId(const UAltEnvironment* environment, int32& result, EAltTrackingExceptionResult& exception) {
    if (environment == nullptr) {
        exception = EAltTrackingExceptionResult::Fail;
        return;
    }

    auto callResult = environment->GetUpdateId(result);
    exception = static_cast<EAltTrackingExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

bool UAltTrackingFunctionLibrary::IsEnvironmentValid(const UAltEnvironment* environment) {
    if (environment == nullptr) {
        return false;
    }

    return environment->IsValid();
}