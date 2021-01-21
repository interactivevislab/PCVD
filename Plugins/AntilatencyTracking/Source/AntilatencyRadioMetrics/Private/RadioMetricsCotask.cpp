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

#include "RadioMetricsCotask.h"

#include "RadioMetricsLog.h"

#include <ExceptionCheck.h>

URadioMetricsCotask* URadioMetricsCotask::CreateRadioMetricsCotask(const Antilatency::RadioMetrics::ICotask& native) {
    if (native == nullptr) {
        RADIOMETRICS_LOG(Warning, TEXT("Failed to create URadioMetricsCotask: native radio metrics cotask is nullptr"));
        return nullptr;
    }

    auto result = NewObject<URadioMetricsCotask>();
    result->Init(native);
    return result;
}

void URadioMetricsCotask::Init(Antilatency::RadioMetrics::ICotask native) {
    _native = native;
}

Antilatency::InterfaceContract::ExceptionCode URadioMetricsCotask::GetMetrics(const FAdnNode& targetNode, FRadioMetrics& result) const {
	result = FRadioMetrics{};

	if (!IsValid()) {
		return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
	}

	Antilatency::RadioMetrics::Metrics nativeResult;
	auto exception = _native.getMetrics(targetNode.ToNative(), nativeResult);
	ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_native, exception);

	result = static_cast<FRadioMetrics>(nativeResult);
	return exception;
}

Antilatency::InterfaceContract::ExceptionCode URadioMetricsCotask::GetExtendedMetrics(const FAdnNode& targetNode, FExtendedMetrics& result) const {
	result = FExtendedMetrics{};

	if (!IsValid()) {
		return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
	}

	Antilatency::RadioMetrics::Interop::ExtendedMetrics nativeResult;
	auto exception = _native.getExtendedMetrics(targetNode.ToNative(), nativeResult);
	ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_native, exception);

	result = static_cast<FExtendedMetrics>(nativeResult);
	return exception;
}

Antilatency::InterfaceContract::ExceptionCode URadioMetricsCotask::IsTaskFinished(bool &result) const {
    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    Antilatency::InterfaceContract::LongBool nativeResult;
    auto exception = _native.isTaskFinished(nativeResult);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_native, exception);

    result = nativeResult;
    return exception;
}

void URadioMetricsCotask::Stop() {
    _native = nullptr;
}

bool URadioMetricsCotask::IsValid() const {
    if (_native == nullptr) {
        RADIOMETRICS_LOG(Warning, TEXT("Native radio metrics task is nullptr"));
        return false;
    }

    return true;
}