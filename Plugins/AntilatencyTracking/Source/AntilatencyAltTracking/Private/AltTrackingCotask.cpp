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

#include "AltTrackingCotask.h"

#include "AltTrackingLog.h"

#include <InterfaceIdUtils.h>
#include <ExceptionCheck.h>

UAltTrackingCotask* UAltTrackingCotask::CreateAltTrackingCotask(const Antilatency::Alt::Tracking::ITrackingCotask& native) {
    if (native == nullptr) {
        ALTTRACKING_LOG(Warning, TEXT("Failed to create UAltTrackingCotask: native tracking cotask is nullptr"));
        return nullptr;
    }
    auto result = NewObject<UAltTrackingCotask>();
    result->Init(native);
    return result;
}

void UAltTrackingCotask::Init(Antilatency::Alt::Tracking::ITrackingCotask native) {
    _native = native;
}

Antilatency::InterfaceContract::ExceptionCode UAltTrackingCotask::GetState(FTrackingState& result) const {
    result = {};

    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    Antilatency::Alt::Tracking::State nativeState;
    auto exception = _native.getState(Antilatency::Alt::Tracking::Constants::DefaultAngularVelocityAvgTime, nativeState);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_native, exception);

	//ALTTRACKING_LOG(Log, TEXT("Alt raw: {%f, %f, %f, %f}"), nativeState.pose.rotation.x, nativeState.pose.rotation.y, nativeState.pose.rotation.z, nativeState.pose.rotation.w);

    result = { nativeState };
	//TODO:
	if (result.Pose.Position.ContainsNaN()) {
		result.Pose.Position = FVector::ZeroVector;
	}
	if (result.Pose.Rotation.ContainsNaN()) {
		result.Pose.Rotation = FRotator::ZeroRotator;
	}
    return exception;
}

Antilatency::InterfaceContract::ExceptionCode UAltTrackingCotask::GetExtrapolatedState(const FAltPose& placement, const float deltaTime, FTrackingState& result) const {
    result = {};

    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    Antilatency::Alt::Tracking::State nativeState;
    auto exception = _native.getExtrapolatedState(placement.ToNative(), deltaTime, nativeState);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_native, exception);

    result = { nativeState };
	//TODO:
	if (result.Pose.Position.ContainsNaN()) {
		result.Pose.Position = FVector::ZeroVector;
	}
	if (result.Pose.Rotation.ContainsNaN()) {
		result.Pose.Rotation = FRotator::ZeroRotator;
	}
    return exception;
}

Antilatency::InterfaceContract::ExceptionCode UAltTrackingCotask::IsTaskFinished(bool& result) const {
    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    Antilatency::InterfaceContract::LongBool nativeResult;
    auto exception = _native.isTaskFinished(nativeResult);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_native, exception);

    result = nativeResult;
    return exception;
}

void UAltTrackingCotask::Stop() {
    _native = nullptr;
}

bool UAltTrackingCotask::IsValid() const {
    if (_native == nullptr) {
        ALTTRACKING_LOG(Warning, TEXT("Native tracking cotask is nullptr"));
        return false;
    }

    return true;
}