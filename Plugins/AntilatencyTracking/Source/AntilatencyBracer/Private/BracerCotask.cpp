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

#include "BracerCotask.h"

#include "BracerLog.h"

#include <ExceptionCheck.h>

UBracerCotask* UBracerCotask::CreateBracerCotask(const Antilatency::Bracer::ICotask& native) {
    if (native == nullptr) {
        BRACER_LOG(Warning, TEXT("Failed to create UBracerCotask: native bracer cotask is nullptr"));
        return nullptr;
    }

    auto result = NewObject<UBracerCotask>();
    result->Init(native);
    return result;
}

void UBracerCotask::Init(Antilatency::Bracer::ICotask native) {
    _native = native;
}

Antilatency::InterfaceContract::ExceptionCode UBracerCotask::GetBatteryLevel(float& result) const {
	result = 0.0f;

	if (!IsValid()) {
		return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
	}

	auto exception = _native.getBatteryLevel(result);
	ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_native, exception);

	return exception;
}

Antilatency::InterfaceContract::ExceptionCode UBracerCotask::GetTouchChannelsCount(int32& result) const {
	result = 0;

	if (!IsValid()) {
		return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
	}

	uint32_t nativeValue;
	auto exception = _native.getTouchChannelsCount(nativeValue);
	ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_native, exception);

	result = static_cast<int32>(nativeValue);
	return exception;
}

Antilatency::InterfaceContract::ExceptionCode UBracerCotask::GetTouchNativeValue(const int32 channel, int32& result) const {
	result = 0;

	if (!IsValid()) {
		return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
	}

	uint32_t nativeValue;
	auto exception = _native.getTouchNativeValue(static_cast<uint32_t>(channel), nativeValue);
	ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_native, exception);

	result = static_cast<int32>(nativeValue);
	return exception;
}

Antilatency::InterfaceContract::ExceptionCode UBracerCotask::GetTouch(const int32 channel, float& result) const {
    result = 0;

    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    float nativeValue;
    auto exception = _native.getTouch(static_cast<uint32_t>(channel), nativeValue);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_native, exception);
    
    result = nativeValue;
    return exception;
}

Antilatency::InterfaceContract::ExceptionCode UBracerCotask::ExecuteVibrationSequence(const TArray<FVibration> vibrationSequence) const {
    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

	std::vector<Antilatency::Bracer::Vibration> native;
	native.reserve(static_cast<size_t>(vibrationSequence.Num()));

	for (auto v : vibrationSequence) {
		Antilatency::Bracer::Vibration vibration;
		
		vibration.duration = v.Duration;
		vibration.intensity = v.Intensity;

		native.push_back(vibration);
	}

    auto exception = _native.executeVibrationSequence(native);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_native, exception);

    return exception;
}

Antilatency::InterfaceContract::ExceptionCode UBracerCotask::IsTaskFinished(bool &result) const {
    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    Antilatency::InterfaceContract::LongBool nativeResult;
    auto exception = _native.isTaskFinished(nativeResult);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_native, exception);

    result = nativeResult;
    return exception;
}

void UBracerCotask::Stop() {
    _native = nullptr;
}

bool UBracerCotask::IsValid() const {
    if (_native == nullptr) {
        BRACER_LOG(Warning, TEXT("Native bracer task is nullptr"));
        return false;
    }

    return true;
}