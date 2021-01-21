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

#include "HardwareExtensionInterfaceCotask.h"

#include "HardwareExtensionInterfaceLog.h"

#include <ExceptionCheck.h>

UHardwareExtensionInterfaceCotask* UHardwareExtensionInterfaceCotask::CreateHardwareExtensionInterfaceCotask(const Antilatency::HardwareExtensionInterface::ICotask& native) {
    if (native == nullptr) {
		HARDWAREEXTENSIONINTERFACE_LOG(Warning, TEXT("Failed to create URadioMetricsCotask: native hardware extension interface cotask is nullptr"));
        return nullptr;
    }

    auto result = NewObject<UHardwareExtensionInterfaceCotask>();
	result->_native = native;
    return result;
}

Antilatency::InterfaceContract::ExceptionCode UHardwareExtensionInterfaceCotask::CreateInputPin(const EPins& pin, UInputPin*& result) const {
	result = {};

	if (!IsValid()) {
		return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
	}

	Antilatency::HardwareExtensionInterface::IInputPin nativeResult;
	auto exception = _native.createInputPin(static_cast<Antilatency::HardwareExtensionInterface::Interop::Pins>(pin), nativeResult);
	ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_native, exception);

	result = UInputPin::CreateInputPin(nativeResult, this);
	return exception;
}

Antilatency::InterfaceContract::ExceptionCode UHardwareExtensionInterfaceCotask::CreateOutputPin(const EPins& pin, const EPinState& initialState, UOutputPin*& result) const {
	result = {};

	if (!IsValid()) {
		return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
	}

	Antilatency::HardwareExtensionInterface::IOutputPin nativeResult;
	auto exception = _native.createOutputPin(static_cast<Antilatency::HardwareExtensionInterface::Interop::Pins>(pin), static_cast<Antilatency::HardwareExtensionInterface::Interop::PinState>(initialState), nativeResult);
	ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_native, exception);

	result = UOutputPin::CreateOutputPin(nativeResult, this);
	return exception;
}

Antilatency::InterfaceContract::ExceptionCode UHardwareExtensionInterfaceCotask::CreateAnalogPin(const EPins& pin, const uint32_t refreshIntervalMs, UAnalogPin*& result) const {
	result = {};

	if (!IsValid()) {
		return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
	}

	Antilatency::HardwareExtensionInterface::IAnalogPin nativeResult;
	auto exception = _native.createAnalogPin(static_cast<Antilatency::HardwareExtensionInterface::Interop::Pins>(pin), refreshIntervalMs, nativeResult);
	ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_native, exception);

	result = UAnalogPin::CreateAnalogPin(nativeResult, this);
	return exception;
}

Antilatency::InterfaceContract::ExceptionCode UHardwareExtensionInterfaceCotask::CreatePulseCounterPin(const EPins& pin, const uint32_t refreshIntervalMs, UPulseCounterPin*& result) const {
	result = {};

	if (!IsValid()) {
		return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
	}

	Antilatency::HardwareExtensionInterface::IPulseCounterPin nativeResult;
	auto exception = _native.createPulseCounterPin(static_cast<Antilatency::HardwareExtensionInterface::Interop::Pins>(pin), refreshIntervalMs, nativeResult);
	ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_native, exception);

	result = UPulseCounterPin::CreatePulseCounterPin(nativeResult, this);
	return exception;
}

Antilatency::InterfaceContract::ExceptionCode UHardwareExtensionInterfaceCotask::Run() const {
    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    auto exception = _native.run();
    ANTILATENCY_EXCEPTION_CHECK(_native, exception);

    return exception;
}

void UHardwareExtensionInterfaceCotask::Stop() {
    _native = nullptr;
}

Antilatency::InterfaceContract::ExceptionCode UHardwareExtensionInterfaceCotask::IsTaskFinished(bool& result) const {
	if (!IsValid()) {
		return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
	}

	Antilatency::InterfaceContract::LongBool nativeResult;
	auto exception = _native.isTaskFinished(nativeResult);
	ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_native, exception);

	result = nativeResult;
	return exception;
}

bool UHardwareExtensionInterfaceCotask::IsValid() const {
    if (_native == nullptr) {
		HARDWAREEXTENSIONINTERFACE_LOG(Warning, TEXT("Native radio metrics task is nullptr"));
        return false;
    }

    return true;
}