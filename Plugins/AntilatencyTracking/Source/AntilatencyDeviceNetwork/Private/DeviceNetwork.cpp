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

#include "DeviceNetwork.h"

#include <cstring>
#include <sstream>
#include <iomanip>

#include "AdnLog.h"
#include "InterfaceIdUtils.h"
#include <ExceptionCheck.h>

UDeviceNetwork* UDeviceNetwork::CreateDeviceNetwork(const Antilatency::DeviceNetwork::INetwork& native) {
    if (native == nullptr) {
        ADN_LOG(Warning, TEXT("Native network is nullptr"));
        return nullptr;
    }

    auto result = NewObject<UDeviceNetwork>();
    result->Init(native);
    return result;
}

void UDeviceNetwork::Init(Antilatency::DeviceNetwork::INetwork network) {
    _network = network;
}

Antilatency::DeviceNetwork::INetwork UDeviceNetwork::GetNative() const {
    return _network;
}

Antilatency::InterfaceContract::ExceptionCode UDeviceNetwork::GetUpdateId(int32& result) const {
    result = 0;

    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    uint32_t updateId;

    auto exception = _network.getUpdateId(updateId);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_network, exception);

    result = updateId;
    return exception;
}

Antilatency::InterfaceContract::ExceptionCode UDeviceNetwork::GetDevicesTypes(TArray<FUsbDeviceType>& result) const {
    result.Empty();

    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    std::vector<Antilatency::DeviceNetwork::UsbDeviceType> deviceTypesNative;
    auto exception = _network.getDeviceTypes(deviceTypesNative);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_network, exception);

    result.Empty();

    for (size_t i = 0; i < deviceTypesNative.size(); ++i) {
        result.Add({ deviceTypesNative[i] });
    }

    return exception;
}

Antilatency::InterfaceContract::ExceptionCode UDeviceNetwork::GetNodes(TArray<FAdnNode>& result) const {
    result.Empty();

    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    std::vector<Antilatency::DeviceNetwork::NodeHandle> nodes;
    auto exception = _network.getNodes(nodes);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_network, exception);

    for (size_t i = 0; i < nodes.size(); ++i) {
        result.Add(FAdnNode(nodes[i]));
    }

    return exception;
}

Antilatency::InterfaceContract::ExceptionCode UDeviceNetwork::NodeGetStatus(const FAdnNode& node, ENodeStatus& result) const {
    result = ENodeStatus::Invalid;

    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    Antilatency::DeviceNetwork::NodeStatus status;
    auto exception = _network.nodeGetStatus(node.ToNative(), status);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_network, exception);

    result = static_cast<ENodeStatus>(status);
    return exception;
}


Antilatency::InterfaceContract::ExceptionCode UDeviceNetwork::NodeIsTaskSupported(const FAdnNode& node, const FGuid& interfaceId, bool& result) const {
    result = false;

    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    auto nativeId = FGuidToInterfaceID(interfaceId);

    Antilatency::InterfaceContract::LongBool tmp;
    auto exception = _network.nodeIsTaskSupported(node.ToNative(), nativeId, tmp);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_network, exception);

    result = tmp;
    return exception;
}

Antilatency::InterfaceContract::ExceptionCode UDeviceNetwork::NodeGetParent(const FAdnNode& node, FAdnNode& result) const {
    result = FAdnNode();

    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    Antilatency::DeviceNetwork::NodeHandle parent;
    auto exception = _network.nodeGetParent(node.ToNative(), parent);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_network, exception);

    result = FAdnNode(parent);
    return exception;
}

Antilatency::InterfaceContract::ExceptionCode UDeviceNetwork::NodeGetPhysicalPath(const FAdnNode& node, FString& result) const {
    result.Empty();

    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    std::string path;
    auto exception = _network.nodeGetPhysicalPath(node.ToNative(), path);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_network, exception);

    result = { path.c_str() };
    return exception;
}

Antilatency::InterfaceContract::ExceptionCode UDeviceNetwork::NodeGetStringProperty(const FAdnNode& node, const FString& key, FString& result) const {
    result.Empty();

    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    std::string propValue;
    auto exception = _network.nodeGetStringProperty(node.ToNative(), TCHAR_TO_UTF8(*key), propValue);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_network, exception);

    result = { propValue.c_str() };
    return exception;
}

Antilatency::InterfaceContract::ExceptionCode UDeviceNetwork::NodeSetStringProperty(const FAdnNode& node, const FString& key, const FString& value) const {
    if (!IsValid()) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    Antilatency::DeviceNetwork::IPropertyCotask propTask;
    auto exception = _network.nodeStartPropertyTask(node.ToNative(), propTask);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_network, exception);

    Antilatency::InterfaceContract::LongBool tmp;
    exception = propTask.setStringProperty(TCHAR_TO_UTF8(*key), TCHAR_TO_UTF8(*value));
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_network, exception);

    return exception;
}

bool UDeviceNetwork::IsValid() const {
    if (_network == nullptr) {
        ADN_LOG(Warning, TEXT("Native network is nullptr"));
        return false;
    }

    return true;
}