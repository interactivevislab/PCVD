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

#include "DeviceNetworkConstants.h"

static const FAdnNode nullNode = {};

static const FString hardwareVersionKey = { Antilatency::DeviceNetwork::Interop::Constants::HardwareVersionKey };
static const FString hardwareNameKey = { Antilatency::DeviceNetwork::Interop::Constants::HardwareNameKey };
static const FString firmwareVersionKey = { Antilatency::DeviceNetwork::Interop::Constants::FirmwareNameKey };
static const FString firmwareNameKey = { Antilatency::DeviceNetwork::Interop::Constants::FirmwareVersionKey };
static const FString hardwareSerialNumberKey = { Antilatency::DeviceNetwork::Interop::Constants::HardwareSerialNumberKey };
static const FString tagKey = { "Tag" };


FUsbDeviceType UDeviceNetworkConstantsLibrary::AntilatencyUsbDeviceType() {
    return FUsbDeviceType::AntilatencyUsbDeviceType();
}

FUsbDeviceType UDeviceNetworkConstantsLibrary::AntilatencyUsbDeviceTypeLegacy() {
    return FUsbDeviceType::AntilatencyUsbDeviceTypeLegacy();
}

FAdnNode UDeviceNetworkConstantsLibrary::NullNode() {
    return nullNode;
}

FString UDeviceNetworkConstantsLibrary::HardwareVersionKey() {
    return hardwareVersionKey;
}

FString UDeviceNetworkConstantsLibrary::HardwareNameKey() {
    return hardwareNameKey;
}

FString UDeviceNetworkConstantsLibrary::FirmwareVersionKey() {
    return firmwareVersionKey;
}

FString UDeviceNetworkConstantsLibrary::FirmwareNameKey() {
    return firmwareNameKey;
}

FString UDeviceNetworkConstantsLibrary::HardwareSerialNumberKey() {
    return hardwareSerialNumberKey;
}

FString UDeviceNetworkConstantsLibrary::TagKey() {
    return tagKey;
}