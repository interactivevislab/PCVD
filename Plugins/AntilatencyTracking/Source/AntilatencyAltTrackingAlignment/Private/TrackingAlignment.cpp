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

#include "TrackingAlignment.h"

#include "TrackingAlignmentLog.h"

#include <Antilatency.Math.h>

#include <ExceptionCheck.h>

void UTrackingAlignment::BeginDestroy() {
	TRACKINGALIGNMENT_LOG(Warning, TEXT("UTrackingAlignment: begin destroy"));
	UObject::BeginDestroy();
}

UTrackingAlignment* UTrackingAlignment::CreateTrackingAlignment(const Antilatency::TrackingAlignment::ITrackingAlignment& native) {
    if (native == nullptr) {
        TRACKINGALIGNMENT_LOG(Warning, TEXT("Failed to create UTrackingAlignment: native tracking cotask is nullptr"));
        return nullptr;
    }
    auto result = NewObject<UTrackingAlignment>();
    result->Init(native);
    return result;
}

void UTrackingAlignment::Init(Antilatency::TrackingAlignment::ITrackingAlignment native) {
    _native = native;
}

Antilatency::InterfaceContract::ExceptionCode UTrackingAlignment::Update(const FQuat& a, const FQuat& b, const float time, FTrackingAlignmentState& result) const {
	result = {};

    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

	Antilatency::Math::doubleQ aN = { double{a.Y}, double{a.Z}, double{a.X}, double{a.W} };
	Antilatency::Math::doubleQ bN = { double{b.Y}, double{b.Z}, double{b.X}, double{b.W} };

	Antilatency::TrackingAlignment::State nativeResult;
    auto exception = _native.update(aN, bN, time, nativeResult);
	ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_native, exception);

	result = { nativeResult };

	//TRACKINGALIGNMENT_LOG(Log, TEXT("{%f}    [%f, %f, %f, %f]    [%f, %f, %f, %f]    [%f, %f, %f, %f]    [%f, %f, %f, %f]    %f"), 
	//	time, 
	//	aN.x, aN.y, aN.z, aN.w, 
	//	bN.x, bN.y, bN.z, bN.w, 
	//	result.RotationARelativeToB.X, result.RotationARelativeToB.Y, result.RotationARelativeToB.Z, result.RotationARelativeToB.W,
	//	result.RotationBSpace.X, result.RotationBSpace.Y, result.RotationBSpace.Z, result.RotationBSpace.W, 
	//	result.TimeBAheadOfA);

    return exception;
}

bool UTrackingAlignment::IsValid() const {
    if (_native == nullptr) {
        TRACKINGALIGNMENT_LOG(Warning, TEXT("Native tracking alignment is nullptr"));
        return false;
    }

    return true;
}