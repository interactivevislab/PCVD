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

#include "HardwareExtensionInterfaceFunctionLibrary.h"

void UHardwareExtensionInterfaceFunctionLibrary::GetHardwareExtensionInterfaceLibrary(UHardwareExtensionInterfaceLibrary *&result, EHardwareExtensionInterfaceExceptionResult &exception) {
    result = UHardwareExtensionInterfaceLibrary::GetLibrary();
    exception = static_cast<EHardwareExtensionInterfaceExceptionResult>(result != nullptr);
}

void UHardwareExtensionInterfaceFunctionLibrary::StartHardwareExtensionInterfaceTask(const UHardwareExtensionInterfaceLibrary *library, const UDeviceNetwork *network, const FAdnNode &node, UHardwareExtensionInterfaceCotask *&result, EHardwareExtensionInterfaceExceptionResult &exception) {
    if (library == nullptr) {
        exception = EHardwareExtensionInterfaceExceptionResult::Fail;
        return;
    }

    auto callResult = library->StartHardwareExtensionInterfaceTask(network, node, result);
    exception = static_cast<EHardwareExtensionInterfaceExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UHardwareExtensionInterfaceFunctionLibrary::IsSupported(const UHardwareExtensionInterfaceLibrary *library, const UDeviceNetwork *network, const FAdnNode &node, bool &result, EHardwareExtensionInterfaceExceptionResult &exception) {
    result = false;
    if (library == nullptr || network == nullptr) {
        exception = EHardwareExtensionInterfaceExceptionResult::Fail;
        return;
    }

    auto callResult = library->IsSupported(network, node, result);
    exception = static_cast<EHardwareExtensionInterfaceExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UHardwareExtensionInterfaceFunctionLibrary::FindSupportedNodes(const UHardwareExtensionInterfaceLibrary *library, const UDeviceNetwork *network, TArray<FAdnNode> &result, EHardwareExtensionInterfaceExceptionResult &exception) {
    result.Empty();

    if (library == nullptr || network == nullptr) {
        exception = EHardwareExtensionInterfaceExceptionResult::Fail;
        return;
    }

    auto callResult = library->FindSupportedNodes(network, result);
    exception = static_cast<EHardwareExtensionInterfaceExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

bool UHardwareExtensionInterfaceFunctionLibrary::IsLibraryValid(const UHardwareExtensionInterfaceLibrary *library) {
    if (library == nullptr) {
        return false;
    }

    return library->IsValid();
}

void UHardwareExtensionInterfaceFunctionLibrary::IsTaskFinished(const UHardwareExtensionInterfaceCotask* cotask, bool& result, EHardwareExtensionInterfaceExceptionResult& exception) {
    if (cotask == nullptr) {
        exception = EHardwareExtensionInterfaceExceptionResult::Fail;
        return;
    }

    auto callResult = cotask->IsTaskFinished(result);
    exception = static_cast<EHardwareExtensionInterfaceExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UHardwareExtensionInterfaceFunctionLibrary::Stop(UHardwareExtensionInterfaceCotask* cotask) {
    if (cotask == nullptr) {
        return;
    }

	cotask->Stop();
}

bool UHardwareExtensionInterfaceFunctionLibrary::IsHardwareExtensionInterfaceTaskValid(const UHardwareExtensionInterfaceCotask* cotask) {
    if (cotask == nullptr) {
        return false;
    }
    
    return cotask->IsValid();
}

void UHardwareExtensionInterfaceFunctionLibrary::CreateInputPin(const UHardwareExtensionInterfaceCotask* cotask, const EPins& pin, UInputPin*& result, EHardwareExtensionInterfaceExceptionResult& exception) {
	if (cotask == nullptr) {
		exception = EHardwareExtensionInterfaceExceptionResult::Fail;
		return;
	}

	auto callResult = cotask->CreateInputPin(pin, result);
	exception = static_cast<EHardwareExtensionInterfaceExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UHardwareExtensionInterfaceFunctionLibrary::CreateOutputPin(const UHardwareExtensionInterfaceCotask* cotask, const EPins& pin, const EPinState& initialState, UOutputPin*& result, EHardwareExtensionInterfaceExceptionResult& exception) {
	if (cotask == nullptr) {
		exception = EHardwareExtensionInterfaceExceptionResult::Fail;
		return;
	}

	auto callResult = cotask->CreateOutputPin(pin, initialState, result);
	exception = static_cast<EHardwareExtensionInterfaceExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UHardwareExtensionInterfaceFunctionLibrary::CreateAnalogPin(const UHardwareExtensionInterfaceCotask* cotask, const EPins& pin, const uint8 refreshIntervalMs, UAnalogPin*& result, EHardwareExtensionInterfaceExceptionResult& exception) {
	if (cotask == nullptr) {
		exception = EHardwareExtensionInterfaceExceptionResult::Fail;
		return;
	}

	auto callResult = cotask->CreateAnalogPin(pin, static_cast<uint32_t>(refreshIntervalMs), result);
	exception = static_cast<EHardwareExtensionInterfaceExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UHardwareExtensionInterfaceFunctionLibrary::CreatePulseCounterPin(const UHardwareExtensionInterfaceCotask* cotask, const EPins& pin, const uint8 refreshIntervalMs, UPulseCounterPin*& result, EHardwareExtensionInterfaceExceptionResult& exception) {
	if (cotask == nullptr) {
		exception = EHardwareExtensionInterfaceExceptionResult::Fail;
		return;
	}

	auto callResult = cotask->CreatePulseCounterPin(pin, static_cast<uint32_t>(refreshIntervalMs), result);
	exception = static_cast<EHardwareExtensionInterfaceExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UHardwareExtensionInterfaceFunctionLibrary::Run(const UHardwareExtensionInterfaceCotask* cotask, EHardwareExtensionInterfaceExceptionResult& exception) {
	if (cotask == nullptr) {
		exception = EHardwareExtensionInterfaceExceptionResult::Fail;
		return;
	}

	auto callResult = cotask->Run();
	exception = static_cast<EHardwareExtensionInterfaceExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}



void UHardwareExtensionInterfaceFunctionLibrary::GetInputPinState(const UInputPin* pin, EPinState& result, EHardwareExtensionInterfaceExceptionResult& exception) {
	if (pin == nullptr) {
		exception = EHardwareExtensionInterfaceExceptionResult::Fail;
		return;
	}

	auto callResult = pin->GetState(result);
	exception = static_cast<EHardwareExtensionInterfaceExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

bool UHardwareExtensionInterfaceFunctionLibrary::IsInputPinValid(const UInputPin* pin) {
	if (pin == nullptr) {
		return false;
	}

	return pin->IsValid();
}



void UHardwareExtensionInterfaceFunctionLibrary::GetOutputPinState(const UOutputPin* pin, EPinState& result, EHardwareExtensionInterfaceExceptionResult& exception) {
	if (pin == nullptr) {
		exception = EHardwareExtensionInterfaceExceptionResult::Fail;
		return;
	}

	auto callResult = pin->GetState(result);
	exception = static_cast<EHardwareExtensionInterfaceExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UHardwareExtensionInterfaceFunctionLibrary::SetOutputPinState(const UOutputPin* pin, const EPinState& state, EHardwareExtensionInterfaceExceptionResult& exception) {
	if (pin == nullptr) {
		exception = EHardwareExtensionInterfaceExceptionResult::Fail;
		return;
	}

	auto callResult = pin->SetState(state);
	exception = static_cast<EHardwareExtensionInterfaceExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

bool UHardwareExtensionInterfaceFunctionLibrary::IsOutputPinValid(const UOutputPin* pin) {
	if (pin == nullptr) {
		return false;
	}

	return pin->IsValid();
}




void UHardwareExtensionInterfaceFunctionLibrary::GetAnalogPinValue(const UAnalogPin* pin, float& result, EHardwareExtensionInterfaceExceptionResult& exception) {
	if (pin == nullptr) {
		exception = EHardwareExtensionInterfaceExceptionResult::Fail;
		return;
	}

	auto callResult = pin->GetValue(result);
	exception = static_cast<EHardwareExtensionInterfaceExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

bool UHardwareExtensionInterfaceFunctionLibrary::IsAnalogPinValid(const UAnalogPin* pin) {
	if (pin == nullptr) {
		return false;
	}

	return pin->IsValid();
}




void UHardwareExtensionInterfaceFunctionLibrary::GetPulseCounterPinValue(const UPulseCounterPin* pin, uint8& result, EHardwareExtensionInterfaceExceptionResult& exception) {
	if (pin == nullptr) {
		exception = EHardwareExtensionInterfaceExceptionResult::Fail;
		return;
	}

	uint16_t temp;
	auto callResult = pin->GetValue(temp);
	result = static_cast<uint8>(temp);
	exception = static_cast<EHardwareExtensionInterfaceExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

bool UHardwareExtensionInterfaceFunctionLibrary::IsPulseCounterPinValid(const UPulseCounterPin* pin) {
	if (pin == nullptr) {
		return false;
	}

	return pin->IsValid();
}