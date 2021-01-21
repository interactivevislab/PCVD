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

#include "DeviceNetworkFunctionLibrary.h"

void UDeviceNetworkFunctionLibrary::GetDeviceNetworkLibrary(UDeviceNetworkLibrary*& result, EDeviceNetworkExceptionResult& exception) {
    result = UDeviceNetworkLibrary::GetLibrary();
    exception = static_cast<EDeviceNetworkExceptionResult>(result != nullptr);
}

void UDeviceNetworkFunctionLibrary::CreateNetwork(const UDeviceNetworkLibrary* deviceNetworkLibrary, const TArray<FUsbDeviceType>& usbDeviceTypes, UDeviceNetwork*& result, EDeviceNetworkExceptionResult& exception) {
    if (deviceNetworkLibrary == nullptr) {
        exception = EDeviceNetworkExceptionResult::Fail;
        return;
    }

    auto callResult = deviceNetworkLibrary->CreateNetwork(usbDeviceTypes, result);
    exception = static_cast<EDeviceNetworkExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UDeviceNetworkFunctionLibrary::GetVersion(const UDeviceNetworkLibrary* deviceNetworkLibrary, FString& result, EDeviceNetworkExceptionResult& exception) {
    if (deviceNetworkLibrary == nullptr) {
        exception = EDeviceNetworkExceptionResult::Fail;
        return;
    }

    auto callResult = deviceNetworkLibrary->GetVersion(result);
    exception = static_cast<EDeviceNetworkExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UDeviceNetworkFunctionLibrary::SetLogLevel(const UDeviceNetworkLibrary* deviceNetworkLibrary, const EDeviceNetworkLogLevel& level, EDeviceNetworkExceptionResult& exception) {
    if (deviceNetworkLibrary == nullptr) {
        exception = EDeviceNetworkExceptionResult::Fail;
        return;
    }

    auto callResult = deviceNetworkLibrary->SetLogLevel(level);
    exception = static_cast<EDeviceNetworkExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

bool UDeviceNetworkFunctionLibrary::IsLibraryValid(const UDeviceNetworkLibrary* deviceNetworkLibrary) {
    if (deviceNetworkLibrary == nullptr) {
        return false;
    }

    return deviceNetworkLibrary->IsValid();
}



void UDeviceNetworkFunctionLibrary::GetUpdateId(const UDeviceNetwork* network, int32& result, EDeviceNetworkExceptionResult& exception) {
    if (network == nullptr) {
        exception = EDeviceNetworkExceptionResult::Fail;
        return;
    }

    auto callResult = network->GetUpdateId(result);
    exception = static_cast<EDeviceNetworkExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UDeviceNetworkFunctionLibrary::GetDevicesTypes(const UDeviceNetwork* network, TArray<FUsbDeviceType>& result, EDeviceNetworkExceptionResult& exception) {
    if (network == nullptr) {
        exception = EDeviceNetworkExceptionResult::Fail;
        return;
    }

    auto callResult = network->GetDevicesTypes(result);
    exception = static_cast<EDeviceNetworkExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UDeviceNetworkFunctionLibrary::GetNodes(const UDeviceNetwork* network, TArray<FAdnNode>& result, EDeviceNetworkExceptionResult& exception) {
    if (network == nullptr) {
        exception = EDeviceNetworkExceptionResult::Fail;
        return;
    }

    auto callResult = network->GetNodes(result);
    exception = static_cast<EDeviceNetworkExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UDeviceNetworkFunctionLibrary::NodeGetStatus(const UDeviceNetwork* network, const FAdnNode& node, ENodeStatus& result, EDeviceNetworkExceptionResult& exception) {
    if (network == nullptr) {
        exception = EDeviceNetworkExceptionResult::Fail;
        return;
    }

    auto callResult = network->NodeGetStatus(node, result);
    exception = static_cast<EDeviceNetworkExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UDeviceNetworkFunctionLibrary::NodeIsTaskSupported(const UDeviceNetwork* network, const FAdnNode& node, const FGuid& interfaceId, bool& result, EDeviceNetworkExceptionResult& exception) {
    if (network == nullptr) {
        exception = EDeviceNetworkExceptionResult::Fail;
        return;
    }

    auto callResult = network->NodeIsTaskSupported(node, interfaceId, result);
    exception = static_cast<EDeviceNetworkExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UDeviceNetworkFunctionLibrary::NodeGetParent(const UDeviceNetwork* network, const FAdnNode& node, FAdnNode& result, EDeviceNetworkExceptionResult& exception) {
    if (network == nullptr) {
        exception = EDeviceNetworkExceptionResult::Fail;
        return;
    }

    auto callResult = network->NodeGetParent(node, result);
    exception = static_cast<EDeviceNetworkExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UDeviceNetworkFunctionLibrary::NodeGetPhysicalPath(const UDeviceNetwork* network, const FAdnNode& node, FString& result, EDeviceNetworkExceptionResult& exception) {
    if (network == nullptr) {
        exception = EDeviceNetworkExceptionResult::Fail;
        return;
    }

    auto callResult = network->NodeGetPhysicalPath(node, result);
    exception = static_cast<EDeviceNetworkExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UDeviceNetworkFunctionLibrary::NodeGetStringProperty(const UDeviceNetwork* network, const FAdnNode& node, const FString& key, FString& result, EDeviceNetworkExceptionResult& exception) {
    if (network == nullptr) {
        exception = EDeviceNetworkExceptionResult::Fail;
        return;
    }

    auto callResult = network->NodeGetStringProperty(node, key, result);
    exception = static_cast<EDeviceNetworkExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

void UDeviceNetworkFunctionLibrary::NodeSetStringProperty(const UDeviceNetwork* network, const FAdnNode& node, const FString& key, const FString& value, EDeviceNetworkExceptionResult& exception) {
    if (network == nullptr) {
        exception = EDeviceNetworkExceptionResult::Fail;
        return;
    }

    auto callResult = network->NodeSetStringProperty(node, key, value);
    exception = static_cast<EDeviceNetworkExceptionResult>(callResult == Antilatency::InterfaceContract::ExceptionCode::Ok);
}

bool UDeviceNetworkFunctionLibrary::IsNetworkValid(const UDeviceNetwork* network) {
    if (network == nullptr) {
        return false;
    }

    return network->IsValid();
}

bool UDeviceNetworkFunctionLibrary::EqualEqual_FAdnNodeFAdnNode(const FAdnNode& arg1, const FAdnNode& arg2) {
	return arg1 == arg2;
}

bool UDeviceNetworkFunctionLibrary::NotEqual_FAdnNodeFAdnNode(const FAdnNode& arg1, const FAdnNode& arg2) {
	return arg1 != arg2;
}