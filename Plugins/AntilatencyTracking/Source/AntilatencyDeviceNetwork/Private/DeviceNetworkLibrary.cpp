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

#include "DeviceNetworkLibrary.h"
#include "IAntilatencyDeviceNetworkModule.h"

#include "AdnLog.h"

#include <ExceptionCheck.h>

UDeviceNetworkLibrary* UDeviceNetworkLibrary::GetLibrary() {
    auto module = IAntilatencyDeviceNetworkModule::Get();
    auto library = module.GetNativeLibrary();

    if (library == nullptr) {
        return nullptr;
    }

    auto result = NewObject<UDeviceNetworkLibrary>();
    result->Init(library);
    return result;
}

void UDeviceNetworkLibrary::Init(Antilatency::DeviceNetwork::ILibrary library) {
    _library = library;
}

Antilatency::InterfaceContract::ExceptionCode UDeviceNetworkLibrary::CreateNetwork(const TArray<FUsbDeviceType>& usbDeviceTypes, UDeviceNetwork*& result) const {

    std::vector<Antilatency::DeviceNetwork::UsbDeviceType> deviceTypes;
    deviceTypes.reserve(usbDeviceTypes.Num());

    for (int32 i = 0; i < usbDeviceTypes.Num(); ++i) {
        deviceTypes.push_back(usbDeviceTypes[i].ToNative());
    }

    Antilatency::DeviceNetwork::INetwork network;
    auto exception = _library.createNetwork(deviceTypes, network);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_library, exception);

    if (network == nullptr) {
        return Antilatency::InterfaceContract::ExceptionCode::ErrorPointer;
    }

    result = UDeviceNetwork::CreateDeviceNetwork(network);
    return exception;
}

Antilatency::InterfaceContract::ExceptionCode UDeviceNetworkLibrary::GetVersion(FString& result) const {
    std::string str;
    auto exception = _library.getVersion(str);
    ANTILATENCY_EXCEPTION_CHECK_RETURN_ON_FAIL(_library, exception);

    result = { str.c_str() };
    return exception;
}

Antilatency::InterfaceContract::ExceptionCode UDeviceNetworkLibrary::SetLogLevel(const EDeviceNetworkLogLevel& level) const {
    auto exception = _library.setLogLevel(Antilatency::DeviceNetwork::LogLevel(static_cast<int32_t>(level)));
    ANTILATENCY_EXCEPTION_CHECK(_library, exception);
    return exception;
}

bool UDeviceNetworkLibrary::IsValid() const {
    if (_library == nullptr) {
        ADN_LOG(Warning, TEXT("Antilatency Device Network library is nullptr."));
        return false;
    }

    return true;
}

